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
#include "io/StringValidator.h"

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
    if (!transform.hasAnim()) {
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
    printVisible(transform.mAnimVis, transform.mName);
    printTrans(transform.mAnimTrans, transform.mName);
    printRotate(transform.mAnimRotate, transform.mName);
    //-------------------------------------------------------------------------
    return true;
}

bool ObjWriteAnim::printAnimationEnd(AbstractWriter & writer, const Transform & transform) {
    if (!transform.hasAnim()) {
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

void ObjWriteAnim::printTrans(const AnimTransList & animTrans, const std::string & transformName) const {
    const std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "   " : " ";
    for (auto & a : animTrans) {
        if (!a.isAnimated()) {
            continue;
        }
        //--------------------------------
        if (a.mKeys.empty()) {
            XULError << "Transform: " << transformName
                    << " - doesn't contain any keys in translation";
            continue;
        }

        if (a.mKeys.size() == 1) {
            XULError << "Transform: " << transformName
                    << " - contains only one key in translation";
            continue;
        }

        if (a.mKeys.size() != 2) {
            if (a.mDrf.empty() || a.mDrf == "none") {
                XULError << "Transform: " << transformName
                        << " - doesn't have dataref for translation";
                continue;
            }
        }

        if (StringValidator::hasIllegalSymbols(a.mDrf)) {
            XULError << "Transform: " << transformName
                    << " - has illegal symbols in translation dataref: " << a.mDrf;
            continue;
        }
        //--------------------------------
        if (a.mKeys.size() == 2) {
            mWriter->writeLine(ATTR_TRANS,
                               sep, a.mKeys[0].mPosition.toString(PRECISION),
                               sep, a.mKeys[1].mPosition.toString(PRECISION),
                               sep, a.mKeys[0].mDrfValue,
                               " ", a.mKeys[1].mDrfValue,
                               sep, a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf));
            ++mStat->mAnimAttrCount;
            printLoop(a.mLoop);
        }
        else {
            mWriter->writeLine(ATTR_TRANS_BEGIN, sep, a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf));
            mWriter->spaceMore();

            for (auto & key : a.mKeys) {
                mWriter->writeLine(ATTR_TRANS_KEY, sep, key.mDrfValue, sep, key.mPosition.toString(PRECISION));
            }

            printLoop(a.mLoop);
            mWriter->spaceLess();
            mWriter->writeLine(ATTR_TRANS_END);
            ++mStat->mAnimAttrCount;
        }
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printRotate(const AnimRotateList & animRot, const std::string & transformName) const {
    const std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "   " : " ";
    for (auto & a : animRot) {
        if (!a.isAnimated()) {
            continue;
        }
        //--------------------------------
        if (a.mKeys.empty()) {
            XULError << "Transform: " << transformName
                    << " - doesn't contain any keys in rotation";
            continue;
        }
        if (a.mKeys.size() == 1) {
            XULError << "Transform: " << transformName
                    << " - contains only one key in rotation";
            continue;
        }
        if (a.mKeys.size() != 2) {
            if (a.mDrf.empty() || a.mDrf == "none") {
                XULError << "Transform: " << transformName
                        << " - doesn't have dataref for rotation";
                continue;
            }
        }
        if (StringValidator::hasIllegalSymbols(a.mDrf)) {
            XULError << "Transform: " << transformName
                    << " - has illegal symbols in rotation dataref: " << a.mDrf;
            continue;
        }
        //--------------------------------
        if (a.mKeys.size() == 2) {
            mWriter->writeLine(ATTR_ROTATE,
                               sep, a.mVector.normalized().toString(PRECISION),
                               sep, a.mKeys[0].mAngleDegrees,
                               " ", a.mKeys[1].mAngleDegrees,
                               sep, a.mKeys[0].mDrfValue,
                               " ", a.mKeys[1].mDrfValue,
                               sep, a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf));

            ++mStat->mAnimAttrCount;
            printLoop(a.mLoop);;
        }
        else {
            mWriter->writeLine(ATTR_ROTATE_BEGIN,
                               sep, a.mVector.normalized().toString(PRECISION),
                               sep, a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf));
            mWriter->spaceMore();

            for (auto & key : a.mKeys) {
                mWriter->writeLine(ATTR_ROTATE_KEY, sep, key.mDrfValue, sep, key.mAngleDegrees);
            }

            printLoop(a.mLoop);
            mWriter->spaceLess();
            mWriter->writeLine(ATTR_ROTATE_END);
            ++mStat->mAnimAttrCount;
        }
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printVisible(const AnimVisibility & animVis, const std::string & transformName) const {
    std::size_t counter = 0;
    for (auto & key : animVis.mKeys) {
        ++counter;
        //-----------------------
        if (key.mType == AnimVisibilityKey::UNDEFINED) {
            XULError << "Transform: " << transformName << " - visible key <" << counter
                    << "> has undefined state";
            continue;
        }

        if (key.mDrf.empty() || key.mDrf == "none") {
            XULError << "Transform: " << transformName << " - visible key <" << counter
                    << "> has undefined dataref";
            continue;
        }

        if (StringValidator::hasIllegalSymbols(key.mDrf)) {
            XULError << "Transform: " << transformName << " - visible key <" << counter
                    << "> has illegal symbols in its dataref: " << key.mDrf;
            continue;
        }
        //-----------------------
        const char * animName = key.mType == AnimVisibilityKey::SHOW ? ATTR_ANIM_SHOW : ATTR_ANIM_HIDE;
        mWriter->writeLine(animName, " ", key.mValue1, " ", key.mValue2, " ", mWriter->actualDataref(key.mDrf));
        ++mStat->mAnimAttrCount;
        printLoop(key.mLoopValue);
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
