#pragma once

/*
**  Copyright(C) 2018, StepToSky
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

#include <string>
#include "xpln/Export.h"
#include "xpln/enums/ECursor.h"
#include "xpln/enums/EManipulator.h"
#include "embeddable/AttrManipKeyFrame.h"
#include "embeddable/AttrAxisDetentRange.h"

namespace xobj {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details ATTR_manip_drag_rotate
 * \ingroup Manipulators
 */
class AttrManipDragRotate final {
public:

    //-------------------------------------------------------------------------
    /// @{

    typedef std::vector<AttrManipKeyFrame> Keys;
    typedef std::vector<AttrAxisDetentRange> DetentRanges;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    AttrManipDragRotate() = default;
    AttrManipDragRotate(const AttrManipDragRotate &) = default;
    AttrManipDragRotate(AttrManipDragRotate &&) = default;

    ~AttrManipDragRotate() = default;

    AttrManipDragRotate & operator=(const AttrManipDragRotate &) = default;
    AttrManipDragRotate & operator=(AttrManipDragRotate &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib bool operator==(const AttrManipDragRotate & other) const;
    bool operator!=(const AttrManipDragRotate & other) const { return !this->operator==(other); }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib static const EManipulator mType;
    ECursor mCursor;
    std::string mToolType;

    float mOriginX = 0.0f;
    float mOriginY = 0.0f;
    float mOriginZ = 0.0f;

    float mDirX = 0.0f;
    float mDirY = 0.0f;
    float mDirZ = 0.0f;

    float mAngle1 = 0.0f;
    float mAngle2 = 0.0f;

    float mLift = 0.0f;

    float mV1Min = 0.0f;
    float mV1Max = 1.0f;

    float mV2Min = 0.0f;
    float mV2Max = 1.0f;

    std::string mDataref1;
    std::string mDataref2;

    Keys mKeys;
    DetentRanges mAxisDetentRanges;

    /// @}
    //-------------------------------------------------------------------------

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
