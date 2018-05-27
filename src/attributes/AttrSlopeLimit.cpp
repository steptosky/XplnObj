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

#include "xpln/obj/attributes/AttrSlopeLimit.h"
#include "sts/utilities/Compare.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrSlopeLimit::AttrSlopeLimit(float minPitch, float maxPitch, float minRoll, float maxRoll)
    : mMinPitch(minPitch),
      mMaxPitch(maxPitch),
      mMinRoll(minRoll),
      mMaxRoll(maxRoll),
      mIsEnabled(true) { }

AttrSlopeLimit::AttrSlopeLimit()
    : mMinPitch(0.0f),
      mMaxPitch(0.0f),
      mMinRoll(0.0f),
      mMaxRoll(0.0f),
      mIsEnabled(false) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

AttrSlopeLimit::operator bool() const {
    return mIsEnabled;
}

void AttrSlopeLimit::setEnabled(bool state) {
    mIsEnabled = state;
}

bool AttrSlopeLimit::operator==(const AttrSlopeLimit & other) const {
    return (mIsEnabled == other.mIsEnabled &&
            sts::isEqual(mMinPitch, other.mMinPitch, 0.01f) &&
            sts::isEqual(mMaxPitch, other.mMaxPitch, 0.01f) &&
            sts::isEqual(mMinRoll, other.mMinRoll, 0.01f) &&
            sts::isEqual(mMaxRoll, other.mMaxRoll, 0.01f));
}

bool AttrSlopeLimit::operator!=(const AttrSlopeLimit & other) const {
    return !operator==(other);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrSlopeLimit::setMinPitch(float minPitch) {
    mMinPitch = minPitch;
    mIsEnabled = true;
}

void AttrSlopeLimit::setMaxPitch(float maxPitch) {
    mMaxPitch = maxPitch;
    mIsEnabled = true;
}

void AttrSlopeLimit::setMinRoll(float minRoll) {
    mMinRoll = minRoll;
    mIsEnabled = true;
}

void AttrSlopeLimit::setMaxRoll(float maxRoll) {
    mMaxRoll = maxRoll;
    mIsEnabled = true;
}

float AttrSlopeLimit::minPitch() const {
    return mMinPitch;
}

float AttrSlopeLimit::maxPitch() const {
    return mMaxPitch;
}

float AttrSlopeLimit::minRoll() const {
    return mMinRoll;
}

float AttrSlopeLimit::maxRoll() const {
    return mMaxRoll;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
