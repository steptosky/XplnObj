/*
**  Copyright(C) 2017, StepToSky
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1.Redistributions of source code must retain the above copyright notice, this
**    list of conditions and the following disclaimer.
**  2.Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and / or other materials provided with the distribution.
**  3.Neither the name of StepToSky nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
**  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**  Contacts: www.steptosky.com
*/

#include "ObjTransformation.h"
#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjMesh.h"
#include "io/ObjValidators.h"
#include <cassert>
#include "exceptions/defines.h"
#include "writer/ObjWriteAnim.h"
#include "converters/StringStream.h"

namespace xobj {

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjTransformation::correctExportTransform(ObjMain & inObjMain, const TMatrix & inTm, bool useLodTm) {
		correctTransform(inObjMain, inTm, true, useLodTm);
	}

	void ObjTransformation::correctImportTransform(ObjMain & inObjMain, const TMatrix & inTm) {
		correctTransform(inObjMain, inTm, false, false);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjTransformation::correctTransform(ObjMain & inObjMain, const TMatrix & inTm, bool exp, bool useLodTm) {
		size_t lodCount = inObjMain.lodCount();
		for (size_t i = 0; i < lodCount; ++i) {
			ObjLodGroup & lod = inObjMain.lod(i);
			Transform & transform = lod.transform();
			TMatrix tm = inTm;
			if (useLodTm) {
				tm = transform.pMatrix * tm;
				transform.pMatrix.setIdentity();
			}
			proccess(transform, tm, exp);
		}
	}

	void ObjTransformation::proccess(Transform & transform, const TMatrix & rootMatrix, bool exp) {
		//-------------------------------------------------------------------------
		// objects

		if (exp) {
			if (transform.objList().empty()) {
				mapsExpCoordinates(nullptr, transform, rootMatrix);
			}
			else {
				for (auto & curr : transform.objList()) {
					mapsExpCoordinates(curr, transform, rootMatrix);
				}
			}
		}
		else {
			if (transform.objList().empty()) {
				mapsImpCoordinates(nullptr, transform, rootMatrix);
			}
			else {
				for (auto & curr : transform.objList()) {
					mapsImpCoordinates(curr, transform, rootMatrix);
				}
			}
		}

		//-------------------------------------------------------------------------
		// children

		Transform::TransformIndex chCount = transform.childrenCount();
		for (Transform::TransformIndex i = 0; i < chCount; ++i) {
			proccess(*static_cast<Transform*>(transform.childAt(i)), rootMatrix, exp);
		}

		//-------------------------------------------------------------------------
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjTransformation::mapsExpCoordinates(ObjAbstract * inObj, Transform & objTransform, const TMatrix & rootMtx) {
		const Transform * transParent = ObjWriteAnim::animTransParent(static_cast<Transform*>(objTransform.parent()));
		const Transform * rotateParent = ObjWriteAnim::animRotateParent(static_cast<Transform*>(objTransform.parent()));
		//------------------------------------------------------------------------------------------
		// All animation is relative parent's axis, but transformation matrix of each Transform is in the world space.
		// For example: 
		//		if you make Y translation animation, it means that the object will be moved along Y of parent.
		//		if you make Y (0.0, 1.0, 0.0) rotation animation, it means that the object will be rotated around Y of parent.
		//------------------------------------------------------------------------------------------
		// In normal way in the obj file the objects can contain information about transformation
		// only if they have certain animation.
		// Coordinates of such objects must be mapped to animated transformation,
		// otherwise they must be mapped to global.
		//------------------------------------------------------------------------------------------
		// We have to check if the transformation has only rotation animation,
		// if it is true we have to add 2 identical keys with 0.0 value to animation translation.
		// They are needed for the algorithm which prints animation.
		// The algorithm will prints those keys only as the static position before rotation (i.e. center of rotation).
		// We must not add those keys if the transform contains animation translation!
		translationOfTransformToAnimTransKeys(objTransform);
		//------------------------------------------------------------------------------------------
		// Actually the following code can be optimized but I prefer keep it such a way,
		// it is easier to understanding for me. 
		// But pay attenation there are identical parts in this code (i.e. copy/paste).
		//------------------------------------------------------------------------------------------
		// TestTransformationAlgorithm_case0
		if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && !rotateParent) {
			if (inObj) {
				inObj->applyTransform(objTransform.pMatrix * rootMtx);
			}
		}
		//----------
		// TestTransformationAlgorithm_case1
		else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && !rotateParent) {
			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx) *
									(transParent->pMatrix * rootMtx).toTranslation().inversed());
			}
		}
		//----------
		// TestTransformationAlgorithm_case2
		else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && rotateParent) {
			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx) *
									(transParent->pMatrix * rootMtx).toTranslation().inversed());
			}
		}
		//------------------------------------------------------------------------------------------
		// TestTransformationAlgorithm_case3
		else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && !rotateParent) {
			// making translate vectors relative parent system coordinates and offset keys value. 
			// TODO (needs decompose to method) because has copy
			TMatrix tmTrans = objTransform.parentMatrix().toRotation();
			tmTrans *= objTransform.pMatrix.toTranslation();
			tmTrans *= rootMtx;
			mapAnimTransKeys(objTransform.pAnimTrans, tmTrans);

			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx).toRotation());
			}
		}
		//----------
		// TestTransformationAlgorithm_case4
		else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && !rotateParent) {
			// making translate vectors relative parent system coordinates and offset keys value.
			// TODO (needs decompose to method) because has copy
			TMatrix tmTrans = objTransform.parentMatrix().toRotation();
			tmTrans *= objTransform.pMatrix.toTranslation();
			tmTrans *= transParent->pMatrix.toTranslation().inversed();
			tmTrans *= rootMtx.toRotation();
			mapAnimTransKeys(objTransform.pAnimTrans, tmTrans);

			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx).toRotation());
			}
		}
		//----------
		// TestTransformationAlgorithm_case5
		else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && rotateParent) {
			// making translate vectors relative parent system coordinates and offset keys value. 
			// TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case4
			TMatrix tmTrans = objTransform.parentMatrix().toRotation();
			tmTrans *= objTransform.pMatrix.toTranslation();
			tmTrans *= transParent->pMatrix.toTranslation().inversed();
			tmTrans *= rootMtx.toRotation();
			mapAnimTransKeys(objTransform.pAnimTrans, tmTrans);

			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx).toRotation());
			}
		}
		//------------------------------------------------------------------------------------------
		// TestTransformationAlgorithm_case6
		else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && !rotateParent) {
			// making translate vectors relative parent system coordinates and offset keys value. 
			// TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case3
			TMatrix tmTrans = objTransform.parentMatrix().toRotation();
			tmTrans *= objTransform.pMatrix.toTranslation();
			tmTrans *= rootMtx;
			mapAnimTransKeys(objTransform.pAnimTrans, tmTrans);
			// making rotate vector relative parent system coordinates. 
			TMatrix tmRot = objTransform.parentMatrix().toRotation() * rootMtx.toRotation();
			mapAnimRotateKeys(objTransform.pAnimRotate, tmRot);

			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx).toRotation());
			}
		}
		//----------
		// TestTransformationAlgorithm_case7
		else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && !rotateParent) {
			// making translate vectors relative parent system coordinates and offset keys value. 
			// TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case4
			TMatrix tmTrans = objTransform.parentMatrix().toRotation();
			tmTrans *= objTransform.pMatrix.toTranslation();
			tmTrans *= transParent->pMatrix.toTranslation().inversed();
			tmTrans *= rootMtx.toRotation();
			mapAnimTransKeys(objTransform.pAnimTrans, tmTrans);
			// making rotate vector relative parent system coordinates. 
			// TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case6
			TMatrix tmRot = objTransform.parentMatrix().toRotation() * rootMtx.toRotation();
			mapAnimRotateKeys(objTransform.pAnimRotate, tmRot);

			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx).toRotation());
			}
		}
		//----------
		// TestTransformationAlgorithm_case8
		else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && rotateParent) {
			// making translate vectors relative parent system coordinates and offset keys value. 
			// TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case4
			TMatrix tmTrans = objTransform.parentMatrix().toRotation();
			tmTrans *= objTransform.pMatrix.toTranslation();
			tmTrans *= transParent->pMatrix.toTranslation().inversed();
			tmTrans *= rootMtx.toRotation();
			mapAnimTransKeys(objTransform.pAnimTrans, tmTrans);
			// making rotate vector relative parent system coordinates. 
			// TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case6
			TMatrix tmRot = objTransform.parentMatrix().toRotation() * rootMtx.toRotation();
			mapAnimRotateKeys(objTransform.pAnimRotate, tmRot);

			if (inObj) {
				inObj->applyTransform((objTransform.pMatrix * rootMtx).toRotation());
			}
		}
		//------------------------------------------------------------------------------------------
		else {
			StringStream str;
			str << "Unexpected transformation state, probably your hierarchy is incorrect: "
					<< objTransform.hasAnimRotate() << ":"
					<< objTransform.hasAnimTrans() << ":"
					<< (transParent != nullptr) << ":"
					<< (rotateParent != nullptr);
			throw std::logic_error(ExcTxt(str.str()));
		}
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjTransformation::translationOfTransformToAnimTransKeys(Transform & inOutTrans) {
		if (inOutTrans.hasAnimRotate() && !inOutTrans.hasAnimTrans()) {
			AnimTrans animTr;
			animTr.pKeys.emplace_back(AnimTrans::Key(Point3(), 0.0f));
			animTr.pKeys.emplace_back(AnimTrans::Key(Point3(), 0.0f));
			inOutTrans.pAnimTrans.emplace_back(animTr);
		}
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjTransformation::mapsImpCoordinates(ObjAbstract * /*inObj*/, Transform & objTransform, const TMatrix & /*rootMtx*/) {
		const Transform * transParent = ObjWriteAnim::animTransParent(static_cast<Transform*>(objTransform.parent()));
		const Transform * rotateParent = ObjWriteAnim::animRotateParent(static_cast<Transform*>(objTransform.parent()));

		//------------------------------------------------------------------------------------------
		AnimKeysToTransform(objTransform);
		//------------------------------------------------------------------------------------------
		// Actually the following code can be optimized but I prefer keep it such a way,
		// it is easier to understanding for me.
		// TODO needs implementation
		//------------------------------------------------------------------------------------------

		if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 1";
		}
		else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 2";
		}
		else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 3";
		}
		else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 4";
		}
		//------------------------------------------------------------------------------------------

		else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 5";
		}
		else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 6";
		}
		else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 7";
		}
		else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 8";
		}
		//------------------------------------------------------------------------------------------

		else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 9";
		}
		else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 10";
		}
		else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 11";
		}
		else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 12";
		}
		//------------------------------------------------------------------------------------------

		else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 13";
		}
		else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && !rotateParent) {
			// TODO implementation
			LInfo << " !!! 14";
		}
		else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 15";
		}
		else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && rotateParent) {
			// TODO implementation
			LInfo << " !!! 16";
		}
		//------------------------------------------------------------------------------------------

		else {
			throw std::logic_error(ExcTxt("Unknown transformation state"));
		}
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjTransformation::AnimKeysToTransform(Transform & inOutTrans) {
		for (AnimTransList::iterator animTr = inOutTrans.pAnimTrans.begin(); animTr != inOutTrans.pAnimTrans.end(); ++animTr) {
			if (animTr->pKeys.size() == 1) {
				Point3 currPos = inOutTrans.pMatrix.position();
				inOutTrans.pMatrix.setPosition(currPos + animTr->pKeys[0].pPosition);
				animTr = inOutTrans.pAnimTrans.erase(animTr);
				if (animTr == inOutTrans.pAnimTrans.end()) {
					break;
				}
			}
		}

		for (AnimRotateList::iterator animRot = inOutTrans.pAnimRotate.begin(); animRot != inOutTrans.pAnimRotate.end(); ++animRot) {
			if (animRot->pKeys.size() == 1) {
				TMatrix mtx;
				mtx.setRotate(animRot->pVector, animRot->pKeys[0].pAngleDegrees);
				inOutTrans.pMatrix *= mtx;
				animRot = inOutTrans.pAnimRotate.erase(animRot);
				if (animRot == inOutTrans.pAnimRotate.end()) {
					break;
				}
			}
		}
	}

	/**************************************************************************************************/
	//////////////////////////////////////////* Functions */////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjTransformation::mapAnimTransKeys(AnimTransList & anims, const TMatrix & tm) {
		for (auto & a : anims) {
			for (auto & k : a.pKeys) {
				tm.transformPoint(k.pPosition);
			}
		}
	}

	void ObjTransformation::mapAnimRotateKeys(AnimRotateList & anims, const TMatrix & tm) {
		for (auto & a : anims) {
			tm.transformPoint(a.pVector);
		}
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
