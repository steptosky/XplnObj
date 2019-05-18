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
#include "exceptions/defines.h"
#include "writer/ObjWriteAnim.h"
#include "converters/StringStream.h"
#include "algorithms/TransformAlg.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjTransformation::correctExportTransform(ObjMain & mainObj, const TMatrix & tm, bool useLodTm) {
    correctTransform(mainObj, tm, true, useLodTm);
}

void ObjTransformation::correctImportTransform(ObjMain & mainObj, const TMatrix & tm) {
    correctTransform(mainObj, tm, false, false);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjTransformation::correctTransform(ObjMain & mainObj, const TMatrix & tm, bool exp, bool useLodTm) {
    for (const auto & lod : mainObj.lods()) {
        Transform & transform = lod->transform();
        TMatrix tmCopy = tm;
        if (useLodTm) {
            tmCopy = transform.mMatrix * tmCopy;
            transform.mMatrix.setIdentity();
        }
        proccess(transform, tmCopy, exp);
    }
    proccess(mainObj.mDraped.transform(), tm, exp);
}

void ObjTransformation::proccess(Transform & transform, const TMatrix & rootMatrix, bool exp) {
    //-------------------------------------------------------------------------
    // objects

    if (exp) {
        if (!transform.hasObjects()) {
            mapsExpCoordinates(nullptr, transform, rootMatrix);
        }
        else {
            for (auto & curr : transform.objects()) {
                mapsExpCoordinates(curr.get(), transform, rootMatrix);
            }
        }
    }
    else {
        if (!transform.hasObjects()) {
            mapsImpCoordinates(nullptr, transform, rootMatrix);
        }
        else {
            for (auto & curr : transform.objects()) {
                mapsImpCoordinates(curr.get(), transform, rootMatrix);
            }
        }
    }

    //-------------------------------------------------------------------------
    // children

    for (auto & child : transform) {
        proccess(*child, rootMatrix, exp);
    }

    //-------------------------------------------------------------------------
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjTransformation::mapsExpCoordinates(ObjAbstract * obj, Transform & transform, const TMatrix & rootTm) {
    const Transform * transParent = TransformAlg::animatedTranslateParent(transform);
    const Transform * rotateParent = TransformAlg::animatedRotateParent(transform);
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
    translationOfTransformToAnimTransKeys(transform);
    //------------------------------------------------------------------------------------------
    // Actually the following code can be optimized but I prefer keep it such a way,
    // it is easier to understanding for me. 
    // But pay attention there are identical parts in this code (i.e. copy/paste).
    //------------------------------------------------------------------------------------------
    // TestTransformationAlgorithm_case0
    if (!transform.hasAnimRotate() && !transform.hasAnimTrans() && !transParent && !rotateParent) {
        if (obj) {
            obj->applyTransform(transform.mMatrix * rootTm, true);
        }
    }
        //----------
        // TestTransformationAlgorithm_case1
    else if (!transform.hasAnimRotate() && !transform.hasAnimTrans() && transParent && !rotateParent) {
        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm) * (transParent->mMatrix * rootTm).toTranslation().inversed(), true);
        }
    }
        //----------
        // TestTransformationAlgorithm_case2
    else if (!transform.hasAnimRotate() && !transform.hasAnimTrans() && transParent && rotateParent) {
        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm) * (transParent->mMatrix * rootTm).toTranslation().inversed(), true);
        }
    }
        //------------------------------------------------------------------------------------------
        // TestTransformationAlgorithm_case3
    else if (!transform.hasAnimRotate() && transform.hasAnimTrans() && !transParent && !rotateParent) {
        // making translate vectors relative parent system coordinates and offset keys value. 
        // TODO (needs decompose to method) because has copy
        TMatrix tmTrans = transform.parentMatrix().toRotation();
        tmTrans *= transform.mMatrix.toTranslation();
        tmTrans *= rootTm;
        TransformAlg::applyMatrixToAnimTranslate(transform.mAnimTrans, tmTrans);

        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm).toRotation(), true);
        }
    }
        //----------
        // TestTransformationAlgorithm_case4
    else if (!transform.hasAnimRotate() && transform.hasAnimTrans() && transParent && !rotateParent) {
        // making translate vectors relative parent system coordinates and offset keys value.
        // TODO (needs decompose to method) because has copy
        TMatrix tmTrans = transform.parentMatrix().toRotation();
        tmTrans *= transform.mMatrix.toTranslation();
        tmTrans *= transParent->mMatrix.toTranslation().inversed();
        tmTrans *= rootTm.toRotation();
        TransformAlg::applyMatrixToAnimTranslate(transform.mAnimTrans, tmTrans);

        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm).toRotation(), true);
        }
    }
        //----------
        // TestTransformationAlgorithm_case5
    else if (!transform.hasAnimRotate() && transform.hasAnimTrans() && transParent && rotateParent) {
        // making translate vectors relative parent system coordinates and offset keys value. 
        // TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case4
        TMatrix tmTrans = transform.parentMatrix().toRotation();
        tmTrans *= transform.mMatrix.toTranslation();
        tmTrans *= transParent->mMatrix.toTranslation().inversed();
        tmTrans *= rootTm.toRotation();
        TransformAlg::applyMatrixToAnimTranslate(transform.mAnimTrans, tmTrans);

        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm).toRotation(), true);
        }
    }
        //------------------------------------------------------------------------------------------
        // TestTransformationAlgorithm_case6
    else if (transform.hasAnimRotate() && transform.hasAnimTrans() && !transParent && !rotateParent) {
        // making translate vectors relative parent system coordinates and offset keys value. 
        // TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case3
        TMatrix tmTrans = transform.parentMatrix().toRotation();
        tmTrans *= transform.mMatrix.toTranslation();
        tmTrans *= rootTm;
        TransformAlg::applyMatrixToAnimTranslate(transform.mAnimTrans, tmTrans);
        // making rotate vector relative parent system coordinates. 
        const TMatrix tmRot = transform.parentMatrix().toRotation() * rootTm.toRotation();
        TransformAlg::applyMatrixToAnimRotate(transform.mAnimRotate, tmRot);

        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm).toRotation(), true);
        }
    }
        //----------
        // TestTransformationAlgorithm_case7
    else if (transform.hasAnimRotate() && transform.hasAnimTrans() && transParent && !rotateParent) {
        // making translate vectors relative parent system coordinates and offset keys value. 
        // TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case4
        TMatrix tmTrans = transform.parentMatrix().toRotation();
        tmTrans *= transform.mMatrix.toTranslation();
        tmTrans *= transParent->mMatrix.toTranslation().inversed();
        tmTrans *= rootTm.toRotation();
        TransformAlg::applyMatrixToAnimTranslate(transform.mAnimTrans, tmTrans);
        // making rotate vector relative parent system coordinates. 
        // TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case6
        const TMatrix tmRot = transform.parentMatrix().toRotation() * rootTm.toRotation();
        TransformAlg::applyMatrixToAnimRotate(transform.mAnimRotate, tmRot);

        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm).toRotation(), true);
        }
    }
        //----------
        // TestTransformationAlgorithm_case8
    else if (transform.hasAnimRotate() && transform.hasAnimTrans() && transParent && rotateParent) {
        // making translate vectors relative parent system coordinates and offset keys value. 
        // TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case4
        TMatrix tmTrans = transform.parentMatrix().toRotation();
        tmTrans *= transform.mMatrix.toTranslation();
        tmTrans *= transParent->mMatrix.toTranslation().inversed();
        tmTrans *= rootTm.toRotation();
        TransformAlg::applyMatrixToAnimTranslate(transform.mAnimTrans, tmTrans);
        // making rotate vector relative parent system coordinates. 
        // TODO (needs decompose to method) copy from the TestTransformationAlgorithm_case6
        const TMatrix tmRot = transform.parentMatrix().toRotation() * rootTm.toRotation();
        TransformAlg::applyMatrixToAnimRotate(transform.mAnimRotate, tmRot);

        if (obj) {
            obj->applyTransform((transform.mMatrix * rootTm).toRotation(), true);
        }
    }
        //------------------------------------------------------------------------------------------
    else {
        StringStream str;
        str << "Unexpected transformation state, probably your hierarchy is incorrect: "
                << transform.hasAnimRotate() << ":"
                << transform.hasAnimTrans() << ":"
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
        animTr.mKeys.emplace_back(AnimTrans::Key(Point3(), 0.0f));
        animTr.mKeys.emplace_back(AnimTrans::Key(Point3(), 0.0f));
        inOutTrans.mAnimTrans.emplace_back(animTr);
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjTransformation::
mapsImpCoordinates(ObjAbstract * /*obj*/, Transform & objTransform, const TMatrix & /*rootTm*/) {
    const Transform * transParent = TransformAlg::animatedTranslateParent(objTransform);
    const Transform * rotateParent = TransformAlg::animatedRotateParent(objTransform);
    //------------------------------------------------------------------------------------------
    TransformAlg::applyTranslateKeysToTransform(objTransform, objTransform.mAnimTrans);
    TransformAlg::applyRotateKeysToTransform(objTransform, objTransform.mAnimRotate);
    //------------------------------------------------------------------------------------------
    // Actually the following code can be optimized but I prefer keep it such a way,
    // it is easier to understanding for me.
    // TODO needs implementation
    //------------------------------------------------------------------------------------------

    if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 1";
    }
    else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 2";
    }
    else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 3";
    }
    else if (objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 4";
    }
        //------------------------------------------------------------------------------------------

    else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 5";
    }
    else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 6";
    }
    else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 7";
    }
    else if (!objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 8";
    }
        //------------------------------------------------------------------------------------------

    else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 9";
    }
    else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 10";
    }
    else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && !transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 11";
    }
    else if (!objTransform.hasAnimRotate() && objTransform.hasAnimTrans() && transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 12";
    }
        //------------------------------------------------------------------------------------------

    else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 13";
    }
    else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && !rotateParent) {
        // TODO implementation
        // LInfo << " !!! 14";
    }
    else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && !transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 15";
    }
    else if (objTransform.hasAnimRotate() && !objTransform.hasAnimTrans() && transParent && rotateParent) {
        // TODO implementation
        // LInfo << " !!! 16";
    }
        //------------------------------------------------------------------------------------------

    else {
        throw std::logic_error(ExcTxt("Unknown transformation state"));
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
