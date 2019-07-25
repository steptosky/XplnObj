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
#include "AbstractWriter.h"
#include "xpln/obj/ExportOptions.h"
#include "xpln/obj/IOStatistic.h"
#include "common/AttributeNames.h"
#include "xpln/common/Logger.h"

namespace xobj {

/********************************************************************************************************/
///////////////////////////////////////* Constructors/Destructor *////////////////////////////////////////
/********************************************************************************************************/

ObjWriteAnim::ObjWriteAnim(const ExportOptions * option, IOStatistic * stat) {
    assert(option);
    assert(stat);

    mWriter = nullptr;
    mStat = stat;
    mOptions = option;
}

ObjWriteAnim::~ObjWriteAnim() {
    mWriter = nullptr;
    mStat = nullptr;
    mOptions = nullptr;
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

bool ObjWriteAnim::printAnimationStart(AbstractWriter & writer, const Transform & transform) {
    if (!transform.isAnimated()) {
        return false;
    }
    if (transform.mObjects.empty() && !transform.hasChildren()) {
        return false;
    }
    mWriter = &writer;

    //-------------------------------------------------------------------------

    if (mOptions->isEnabled(XOBJ_EXP_MARK_TRANSFORM)) {
        mWriter->writeLine(ATTR_ANIM_BEGIN, " ## ", transform.mName);
    }
    else {
        mWriter->writeLine(ATTR_ANIM_BEGIN);
    }

    mWriter->spaceMore();
    //-------------------------------------------------------------------------
    printVisible(transform.mVisibility, transform.mName);
    printTrans(transform.mPosition, transform.mName);
    if (transform.mRotation.isAnimated()) {
        if (const auto axisSet = std::get_if<AxisSetRotation>(&transform.mRotation.mAnimation)) {
            for (const auto & a : axisSet->mAxes) {
                printRotateAxis(a, transform.mName);
            }
        }
        if (const auto linear = std::get_if<LinearRotation>(&transform.mRotation.mAnimation)) {
            const auto axes = linear->retrieveAxes();
            for (const auto & a : axes.mAxes) {
                printRotateAxis(a, transform.mName);
            }
        }
    }
    //-------------------------------------------------------------------------
    return true;
}

bool ObjWriteAnim::printAnimationEnd(AbstractWriter & writer, const Transform & transform) {
    if (!transform.isAnimated()) {
        return false;
    }
    mWriter = &writer;
    mWriter->spaceLess();

    if (mOptions->isEnabled(XOBJ_EXP_MARK_TRANSFORM)) {
        mWriter->writeLine(ATTR_ANIM_END, " ## ", transform.mName);
    }
    else {
        mWriter->writeLine(ATTR_ANIM_END);
    }
    return true;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printTrans(const PositionController & translation, const std::string & transformName) const {
    std::size_t counter = 0;
    for (auto & tr : translation.mAnimation) {
        ++counter;
        if (!tr.isAnimated()) {
            continue;
        }
        //--------------------------------
        if (tr.mKeys.size() > 1) {
            if (tr.mDataRef.isEmpty() || tr.mDataRef.isNone()) {
                XULError << "Transform: " << transformName
                        << " - doesn't have dataref for translation";
                continue;
            }
        }

        if (tr.mDataRef.isValidForDataRef()) {
            XULError << "Transform: " << transformName
                    << " - has illegal symbols in translation dataref: " << tr.mDataRef.mString;
            continue;
        }
        //--------------------------------
        const std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "    " : " ";
        //--------------------------------
        if (tr.mKeys.size() == 1) {
            mWriter->writeLine(ATTR_TRANS,
                               sep, tr.mKeys[0].position.toString(PRECISION),
                               sep, tr.mKeys[0].position.toString(PRECISION),
                               sep, tr.mKeys[0].value,
                               " ", tr.mKeys[0].value,
                               sep, "none");
            ++mStat->mAnimAttrCount;
        }
        else if (tr.mKeys.size() == 2) {
            mWriter->writeLine(ATTR_TRANS,
                               sep, tr.mKeys[0].position.toString(PRECISION),
                               sep, tr.mKeys[1].position.toString(PRECISION),
                               sep, tr.mKeys[0].value,
                               " ", tr.mKeys[1].value,
                               sep, tr.mDataRef.isEmpty() ? "none" : mWriter->actualDataref(tr.mDataRef));
            ++mStat->mAnimAttrCount;
            printLoop(tr.mLoop);
        }
        else {
            mWriter->writeLine(ATTR_TRANS_BEGIN, sep, tr.mDataRef.isEmpty() ? "none" : mWriter->actualDataref(tr.mDataRef));
            mWriter->spaceMore();

            for (auto & key : tr.mKeys) {
                mWriter->writeLine(ATTR_TRANS_KEY, sep, key.value, sep, key.position.toString(PRECISION));
            }

            printLoop(tr.mLoop);
            mWriter->spaceLess();
            mWriter->writeLine(ATTR_TRANS_END);
            ++mStat->mAnimAttrCount;
        }
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printRotateAxis(const RotationAxis & axis, const std::string & transformName) const {
    if (!axis.isAnimated()) {
        return;
    }
    //--------------------------------
    if (axis.mKeys.size() > 1) {
        if (axis.mDataRef.isEmpty() || axis.mDataRef.isNone()) {
            XULError << "Transform: " << transformName
                    << " - doesn't have dataref for rotation";
            return;
        }
    }
    if (axis.mDataRef.isValidForDataRef()) {
        XULError << "Transform: " << transformName
                << " - has illegal symbols in rotation dataref: " << axis.mDataRef.mString;
        return;
    }
    //--------------------------------
    const std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "    " : " ";
    //--------------------------------
    if (axis.mKeys.size() == 1) {
        mWriter->writeLine(ATTR_ROTATE,
                           sep, axis.mVector.normalized().toString(PRECISION),
                           sep, axis.mKeys[0].angleDeg.value(),
                           " ", axis.mKeys[0].angleDeg.value(),
                           sep, axis.mKeys[0].value,
                           " ", axis.mKeys[0].value,
                           sep, "none");
        ++mStat->mAnimAttrCount;
    }
    else if (axis.mKeys.size() == 2) {
        mWriter->writeLine(ATTR_ROTATE,
                           sep, axis.mVector.normalized().toString(PRECISION),
                           sep, axis.mKeys[0].angleDeg.value(),
                           " ", axis.mKeys[1].angleDeg.value(),
                           sep, axis.mKeys[0].value,
                           " ", axis.mKeys[1].value,
                           sep, axis.mDataRef.isEmpty() ? "none" : mWriter->actualDataref(axis.mDataRef));

        ++mStat->mAnimAttrCount;
        printLoop(axis.mLoop);;
    }
    else {
        mWriter->writeLine(ATTR_ROTATE_BEGIN,
                           sep, axis.mVector.normalized().toString(PRECISION),
                           sep, axis.mDataRef.isEmpty() ? "none" : mWriter->actualDataref(axis.mDataRef));
        mWriter->spaceMore();

        for (auto & key : axis.mKeys) {
            mWriter->writeLine(ATTR_ROTATE_KEY, sep, key.value, sep, key.angleDeg.value());
        }

        printLoop(axis.mLoop);
        mWriter->spaceLess();
        mWriter->writeLine(ATTR_ROTATE_END);
        ++mStat->mAnimAttrCount;
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printVisible(const VisibilityController & visibility, const std::string & transformName) const {
    std::size_t counter = 0;
    for (auto & key : visibility.mKeys) {
        ++counter;
        //-----------------------
        if (key.mType == VisibilityKey::UNDEFINED) {
            XULError << "Transform: " << transformName << " - visible key <" << counter
                    << "> has undefined state";
            continue;
        }

        if (key.mDataRef.isEmpty() || key.mDataRef.isNone()) {
            XULError << "Transform: " << transformName << " - visible key <" << counter
                    << "> has undefined dataref";
            continue;
        }

        if (key.mDataRef.isValidForDataRef()) {
            XULError << "Transform: " << transformName << " - visible key <" << counter
                    << "> has illegal symbols in its dataref: " << key.mDataRef.mString;
            continue;
        }
        //-----------------------
        const char * animName = key.mType == VisibilityKey::SHOW ? ATTR_ANIM_SHOW : ATTR_ANIM_HIDE;
        mWriter->writeLine(animName, " ", key.mValue1, " ", key.mValue2, " ", mWriter->actualDataref(key.mDataRef));
        ++mStat->mAnimAttrCount;
        printLoop(key.mLoop);
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printLoop(std::optional<float> val) const {
    if (val) {
        mWriter->writeLine(ANIM_KEYFRAME_LOOP, " ", val.value());
        ++mStat->mAnimAttrCount;
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
