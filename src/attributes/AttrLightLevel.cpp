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

#include "xpln/obj/attributes/AttrLightLevel.h"
#include "sts/utilities/Compare.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrLightLevel::AttrLightLevel(float val1, float val2, const std::string & dataRef)
    : mVal1(val1),
      mVal2(val2),
      mDataref(dataRef),
      mIsEnabled(true) { }

AttrLightLevel::AttrLightLevel()
    : mVal1(0.0f),
      mVal2(1.0f),
      mDataref("none"),
      mIsEnabled(false) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

AttrLightLevel::operator bool() const {
    return mIsEnabled;
}

void AttrLightLevel::setEnabled(bool state) {
    mIsEnabled = state;
}

bool AttrLightLevel::operator==(const AttrLightLevel & other) const {
    return (mIsEnabled == other.mIsEnabled &&
            mDataref == other.mDataref &&
            sts::isEqual(mVal1, other.mVal1, 0.01f) &&
            sts::isEqual(mVal2, other.mVal2, 0.01f));
}

bool AttrLightLevel::operator!=(const AttrLightLevel & other) const {
    return !operator==(other);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrLightLevel::setVal1(float val1) {
    mIsEnabled = true;
    mVal1 = val1;
}

void AttrLightLevel::setVal2(float val2) {
    mIsEnabled = true;
    mVal2 = val2;
}

void AttrLightLevel::setDataref(const std::string & dataRef) {
    mIsEnabled = true;
    mDataref = dataRef;
}

float AttrLightLevel::val1() const {
    return mVal1;
}

float AttrLightLevel::val2() const {
    return mVal2;
}

const std::string & AttrLightLevel::dataref() const {
    return mDataref;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
