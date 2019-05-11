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

#include "converters/StringStream.h"
#include "ObjWriteAnim.h"
#include "io/ObjValidators.h"
#include "common/AttributeNames.h"
#include "converters/ObjAnimString.h"

namespace xobj {

/********************************************************************************************************/
///////////////////////////////////////* Constructors/Destructor *////////////////////////////////////////
/********************************************************************************************************/

ObjWriteAnim::ObjWriteAnim(const ExportOptions * option, IOStatistic * outStat) {
    assert(option);
    assert(outStat);

    mWriter = nullptr;
    mStat = outStat;
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
    if (!transform.hasAnim())
        return false;

    if (!transform.hasObjects() && transform.childrenNum() == 0)
        return false;

    mWriter = &writer;

    //-------------------------------------------------------------------------

    if (mOptions->isEnabled(XOBJ_EXP_MARK_TRANSFORM)) {
        mWriter->writeLine(std::string(ATTR_ANIM_BEGIN).append(" ## ").append(transform.name()));
    }
    else {
        mWriter->writeLine(ATTR_ANIM_BEGIN);
    }

    mWriter->spaceMore();
    //-------------------------------------------------------------------------
    printVisible(transform.mAnimVis, transform);
    printTrans(transform.mAnimTrans, transform);
    printRotate(transform.mAnimRotate, transform);
    //-------------------------------------------------------------------------
    return true;
}

bool ObjWriteAnim::printAnimationEnd(AbstractWriter & writer, const Transform & transform) {
    if (!transform.hasAnim())
        return false;

    mWriter = &writer;
    mWriter->spaceLess();

    if (mOptions->isEnabled(XOBJ_EXP_MARK_TRANSFORM)) {
        mWriter->writeLine(std::string(ATTR_ANIM_END).append(" ## ").append(transform.name()));
    }
    else {
        mWriter->writeLine(ATTR_ANIM_END);
    }
    return true;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printTrans(const AnimTransList & animTrans, const Transform & transform) const {
    std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "   " : " ";
    for (auto & a : animTrans) {
        if (a.isAnimated() && checkParameters(a, std::string("Transform: ").append(transform.name()))) {
            if (a.mKeys.size() == 2) {
                StringStream stream;
                stream << ATTR_TRANS
                        << sep << a.mKeys[0].mPosition.toString(PRECISION)
                        << sep << a.mKeys[1].mPosition.toString(PRECISION)
                        << sep << a.mKeys[0].mDrfValue
                        << " " << a.mKeys[1].mDrfValue
                        << sep << (a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf).c_str());
                mWriter->writeLine(stream.str());
                if (a.mLoop) {
                    printLoop(*a.mLoop);
                }

                ++mStat->mAnimAttrCount;
            }
            else {
                StringStream stream;
                stream << ATTR_TRANS_BEGIN << sep << (a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf).c_str());
                mWriter->writeLine(stream.str());
                mWriter->spaceMore();

                for (auto & key : a.mKeys) {
                    printObj(key, *mWriter);
                }

                if (a.mLoop) {
                    printLoop(*a.mLoop);
                }

                mWriter->spaceLess();
                mWriter->writeLine(ATTR_TRANS_END);

                ++mStat->mAnimAttrCount;
            }
        }
    }
}

//-------------------------------------------------------------------------

void ObjWriteAnim::printRotate(const AnimRotateList & animRot, const Transform & transform) const {
    std::string sep = mOptions->isEnabled(XOBJ_EXP_DEBUG) ? "   " : " ";
    for (auto & a : animRot) {
        if (a.isAnimated() && checkParameters(a, std::string("Transform: ").append(transform.name()))) {
            if (a.mKeys.size() == 2) {
                StringStream stream;
                stream << ATTR_ROTATE
                        << sep << a.mVector.normalized().toString(PRECISION)
                        << sep << a.mKeys[0].mAngleDegrees
                        << " " << a.mKeys[1].mAngleDegrees
                        << sep << a.mKeys[0].mDrfValue
                        << " " << a.mKeys[1].mDrfValue
                        << sep << (a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf).c_str());
                mWriter->writeLine(stream.str());
                if (a.mLoop) {
                    printLoop(*a.mLoop);
                }

                ++mStat->mAnimAttrCount;
            }
            else {
                StringStream stream;
                stream << ATTR_ROTATE_BEGIN
                        << sep << a.mVector.normalized().toString(PRECISION)
                        << sep << (a.mDrf.empty() ? "none" : mWriter->actualDataref(a.mDrf).c_str());
                mWriter->writeLine(stream.str());
                mWriter->spaceMore();

                for (auto & key : a.mKeys) {
                    printObj(key, *mWriter);
                }

                if (a.mLoop) {
                    printLoop(*a.mLoop);
                }

                mWriter->spaceLess();
                mWriter->writeLine(ATTR_ROTATE_END);

                ++mStat->mAnimAttrCount;
            }
        }
    }

}

//-------------------------------------------------------------------------

void ObjWriteAnim::printVisible(const AnimVisibility & inAnim, const Transform & transform) const {
    if (inAnim.mKeys.empty())
        return;

    for (auto & curr : inAnim.mKeys) {
        if (checkParameters(curr, std::string("Transform: ").append(transform.name()))) {
            ++mStat->mAnimAttrCount;
            printObj(curr, *mWriter);
            if (curr.mLoopValue) {
                printLoop(*curr.mLoopValue);
            }
            ++mStat->mAnimAttrCount;
        }
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAnim::printLoop(const float val) const {
    StringStream stream;
    stream << ANIM_KEYFRAME_LOOP << " " << val;
    mWriter->writeLine(stream.str());
    ++mStat->mAnimAttrCount;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
