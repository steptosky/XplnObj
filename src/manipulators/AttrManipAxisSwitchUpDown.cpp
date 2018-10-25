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

#include "sts/utilities/Compare.h"
#include "converters/StringStream.h"
#include "xpln/obj/manipulators/AttrManipAxisSwitchUpDown.h"
#include "xpln/enums/EManipulator.h"
#include "io/writer/AbstractWriter.h"
#include "common/AttributeNames.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipAxisSwitchUpDown::AttrManipAxisSwitchUpDown()
    : AttrManipBase(EManipulator(EManipulator::axis_switch_ud)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipAxisSwitchUpDown::setClickDelta(const float val) {
    mClickDelta = val;
}

void AttrManipAxisSwitchUpDown::setHoldDelta(const float val) {
    mHoldDelta = val;
}

void AttrManipAxisSwitchUpDown::setMinimum(const float val) {
    mMin = val;
}

void AttrManipAxisSwitchUpDown::setMaximum(const float val) {
    mMax = val;
}

float AttrManipAxisSwitchUpDown::clickDelta() const {
    return mClickDelta;
}

float AttrManipAxisSwitchUpDown::holdDelta() const {
    return mHoldDelta;
}

float AttrManipAxisSwitchUpDown::minimum() const {
    return mMin;
}

float AttrManipAxisSwitchUpDown::maximum() const {
    return mMax;
}

void AttrManipAxisSwitchUpDown::setDataref(const std::string & val) {
    mDataref = val;
}

const std::string & AttrManipAxisSwitchUpDown::dataref() const {
    return mDataref;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipAxisSwitchUpDown::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipAxisSwitchUpDown*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mClickDelta, right->mClickDelta) &&
            sts::isEqual(mHoldDelta, right->mHoldDelta) &&
            sts::isEqual(mMin, right->mMin) &&
            sts::isEqual(mMax, right->mMax) &&
            sts::isEqual(mWheel, right->mWheel) &&
            sts::isEqual(mDataref, right->mDataref));
}

AttrManipBase * AttrManipAxisSwitchUpDown::clone() const {
    return new AttrManipAxisSwitchUpDown(*this);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrManipAxisSwitchUpDown::printObj(AbstractWriter & writer) const {
    StringStream outStr;
    outStr << ATTR_MANIP_AXIS_SWITCH_UP_DOWN;
    outStr << " " << cursor().toString();
    outStr << " " << minimum();
    outStr << " " << maximum();
    outStr << " " << clickDelta();
    outStr << " " << holdDelta();
    outStr << " " << writer.actualDataref(dataref());
    outStr << " " << toolTip();
    writer.printLine(outStr.str());
    return 1 + wheel().printObj(writer);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
