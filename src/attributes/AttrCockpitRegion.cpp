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

#include "xpln/obj/attributes/AttrCockpitRegion.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrCockpitRegion::AttrCockpitRegion(const std::int32_t left, const std::int32_t bottom,
                                     const std::int32_t right, const std::int32_t top)
    : mLeft(left),
      mBottom(bottom),
      mRight(right),
      mTop(top),
      mIsEnabled(true) { }

AttrCockpitRegion::AttrCockpitRegion()
    : mLeft(0),
      mBottom(0),
      mRight(0),
      mTop(0),
      mIsEnabled(false) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

AttrCockpitRegion::operator bool() const {
    return mIsEnabled;
}

void AttrCockpitRegion::setEnabled(const bool state) {
    mIsEnabled = state;
}

bool AttrCockpitRegion::operator==(const AttrCockpitRegion & other) const {
    return mIsEnabled == other.mIsEnabled &&
           mLeft == other.mLeft &&
           mBottom == other.mBottom &&
           mRight == other.mRight &&
           mTop == other.mTop;
}

bool AttrCockpitRegion::operator!=(const AttrCockpitRegion & other) const {
    return !operator==(other);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrCockpitRegion::setLeft(const int32_t left) {
    mLeft = left;
    mIsEnabled = true;
}

void AttrCockpitRegion::setBottom(const int32_t bottom) {
    mBottom = bottom;
    mIsEnabled = true;
}

void AttrCockpitRegion::setRight(const int32_t right) {
    mRight = right;
    mIsEnabled = true;
}

void AttrCockpitRegion::setTop(const int32_t top) {
    mTop = top;
    mIsEnabled = true;
}

int32_t AttrCockpitRegion::left() const {
    return mLeft;
}

int32_t AttrCockpitRegion::bottom() const {
    return mBottom;
}

int32_t AttrCockpitRegion::right() const {
    return mRight;
}

int32_t AttrCockpitRegion::top() const {
    return mTop;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
