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

#include "ObjWriteAnim.h"
#include "io/ObjValidators.h"
#include <cassert>
#include "common/AttributeNames.h"
#include "converters/StringStream.h"
#include "converters/ObjAnimString.h"

namespace xobj {

	/********************************************************************************************************/
	/////////////////////////////////////////////* Static area *//////////////////////////////////////////////
	/********************************************************************************************************/

	const Transform * ObjWriteAnim::animRotateParent(const Transform * inTransform) {
		if (inTransform == nullptr) {
			return nullptr;
		}
		if (inTransform->isRoot())
			return nullptr;

		if (inTransform->hasAnimRotate()) {
			return inTransform;
		}

		return animRotateParent(dynamic_cast<const Transform*>(inTransform->parent()));
	}

	const Transform * ObjWriteAnim::animTransParent(const Transform * inTransform) {
		if (inTransform == nullptr) {
			return nullptr;
		}
		if (inTransform->isRoot())
			return nullptr;

		if (inTransform->hasAnimTrans()) {
			return inTransform;
		}

		return animTransParent(dynamic_cast<const Transform*>(inTransform->parent()));
	}

	/********************************************************************************************************/
	///////////////////////////////////////* Constructors/Destructor *////////////////////////////////////////
	/********************************************************************************************************/

	ObjWriteAnim::ObjWriteAnim(const ExportOptions * inOption, IOStatistic * outStat) {
		assert(inOption);
		assert(outStat);

		mWriter = nullptr;
		mStat = outStat;
		mOptions = inOption;
	}

	ObjWriteAnim::~ObjWriteAnim() {
		mWriter = nullptr;
		mStat = nullptr;
		mOptions = nullptr;
	}

	/********************************************************************************************************/
	//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
	/********************************************************************************************************/

	bool ObjWriteAnim::printAnimationStart(AbstractWriter & writer, const Transform & inTransform) {
		if (!inTransform.hasAnim())
			return false;

		if (inTransform.objList().empty() && inTransform.childrenCount() == 0)
			return false;

		mWriter = &writer;

		//-------------------------------------------------------------------------

		if (mOptions->isEnabled(XOBJ_EXP_MARK_TRANSFORM)) {
			mWriter->printLine(std::string(ATTR_ANIM_BEGIN).append(" ## ").append(inTransform.name()));
		}
		else {
			mWriter->printLine(ATTR_ANIM_BEGIN);
		}

		mWriter->spaceMore();
		//-------------------------------------------------------------------------
		printVisible(inTransform.pAnimVis, inTransform);
		printTrans(inTransform.pAnimTrans, inTransform);
		printRotate(inTransform.pAnimRotate, inTransform);
		//-------------------------------------------------------------------------
		return true;
	}

	bool ObjWriteAnim::printAnimationEnd(AbstractWriter & writer, const Transform & inTransform) {
		if (!inTransform.hasAnim())
			return false;

		mWriter = &writer;
		mWriter->spaceLess();

		if (mOptions->isEnabled(XOBJ_EXP_MARK_TRANSFORM)) {
			mWriter->printLine(std::string(ATTR_ANIM_END).append(" ## ").append(inTransform.name()));
		}
		else {
			mWriter->printLine(ATTR_ANIM_END);
		}
		return true;
	}

	/**************************************************************************************************/
	//////////////////////////////////////////* Functions */////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjWriteAnim::printTrans(const AnimTransList & animTrans, const Transform & inTransform) const {
		std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "   " : " ";
		for (auto & a: animTrans) {
			if (a.isAnimated() && checkParameters(a, std::string("Transform: ").append(inTransform.name()))) {
				if (a.pKeys.size() == 2) {
					StringStream stream;
					stream << ATTR_TRANS
							<< sep << a.pKeys[0].pPosition.toString(PRECISION)
							<< sep << a.pKeys[1].pPosition.toString(PRECISION)
							<< sep << a.pKeys[0].pDrfValue
							<< " " << a.pKeys[1].pDrfValue
							<< sep << (a.pDrf.empty() ? "none" : a.pDrf.c_str());
					mWriter->printLine(stream.str());
					if (a.pHasLoop) {
						printLoop(a.pLoopValue);
					}

					++mStat->pAnimAttrCount;
				}
				else {
					StringStream stream;
					stream << ATTR_TRANS_BEGIN << sep << (a.pDrf.empty() ? "none" : a.pDrf.c_str());
					mWriter->printLine(stream.str());
					mWriter->spaceMore();

					for (auto & key : a.pKeys) {
						mWriter->printLine(toObjString(key));
					}

					if (a.pHasLoop) {
						printLoop(a.pLoopValue);
					}

					mWriter->spaceLess();
					mWriter->printLine(ATTR_TRANS_END);

					++mStat->pAnimAttrCount;
				}
			}
		}
	}

	//-------------------------------------------------------------------------

	void ObjWriteAnim::printRotate(const AnimRotateList & animRot, const Transform & inTransform) const {
		std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "   " : " ";
		for (auto & a : animRot) {
			if (a.isAnimated() && checkParameters(a, std::string("Transform: ").append(inTransform.name()))) {
				if (a.pKeys.size() == 2) {
					StringStream stream;
					stream << ATTR_ROTATE
							<< sep << a.pVector.normalized().toString(PRECISION)
							<< sep << a.pKeys[0].pAngleDegrees
							<< " " << a.pKeys[1].pAngleDegrees
							<< sep << a.pKeys[0].pDrfValue
							<< " " << a.pKeys[1].pDrfValue
							<< sep << (a.pDrf.empty() ? "none" : a.pDrf.c_str());
					mWriter->printLine(stream.str());
					if (a.pHasLoop) {
						printLoop(a.pLoopValue);
					}

					++mStat->pAnimAttrCount;
				}
				else {
					StringStream stream;
					stream << ATTR_ROTATE_BEGIN << sep << a.pVector.normalized().toString(PRECISION)
							<< sep << (a.pDrf.empty() ? "none" : a.pDrf.c_str());
					mWriter->printLine(stream.str());
					mWriter->spaceMore();

					for (auto & key : a.pKeys) {
						mWriter->printLine(toObjString(key));
					}

					if (a.pHasLoop) {
						printLoop(a.pLoopValue);
					}

					mWriter->spaceLess();
					mWriter->printLine(ATTR_ROTATE_END);

					++mStat->pAnimAttrCount;
				}
			}
		}

	}

	//-------------------------------------------------------------------------

	void ObjWriteAnim::printVisible(const AnimVisibility & inAnim, const Transform & inTransform) const {
		if (inAnim.pKeys.empty())
			return;

		for (auto & curr : inAnim.pKeys) {
			if (checkParameters(curr, std::string("Transform: ").append(inTransform.name()))) {
				++mStat->pAnimAttrCount;
				mWriter->printLine(toObjString(curr));
				if (curr.pHasLoop) {
					printLoop(curr.pLoopValue);
				}
				++mStat->pAnimAttrCount;
			}
		}
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjWriteAnim::printLoop(float inVal) const {
		StringStream stream;
		stream << ANIM_KEYFRAME_LOOP << " " << inVal;
		mWriter->printLine(stream.str());
		++mStat->pAnimAttrCount;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
