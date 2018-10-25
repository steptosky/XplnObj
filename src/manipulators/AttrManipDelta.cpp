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
#include "xpln/obj/manipulators/AttrManipDelta.h"
#include "xpln/enums/EManipulator.h"
#include "common/AttributeNames.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipDelta::AttrManipDelta()
    : AttrManipBase(EManipulator(EManipulator::delta)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipDelta::setDown(const float val) {
    mDown = val;
}

void AttrManipDelta::setHold(const float val) {
    mHold = val;
}

void AttrManipDelta::setMinimum(const float val) {
    mMin = val;
}

void AttrManipDelta::setMaximum(const float val) {
    mMax = val;
}

float AttrManipDelta::down() const {
    return mDown;
}

float AttrManipDelta::hold() const {
    return mHold;
}

float AttrManipDelta::minimum() const {
    return mMin;
}

float AttrManipDelta::maximum() const {
    return mMax;
}

void AttrManipDelta::setDataref(const std::string & val) {
    mDataref = val;
}

const std::string & AttrManipDelta::dataref() const {
    return mDataref;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipDelta::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipDelta*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mDown, right->mDown) &&
            sts::isEqual(mHold, right->mHold) &&
            sts::isEqual(mMin, right->mMin) &&
            sts::isEqual(mMax, right->mMax) &&
            sts::isEqual(mWheel, right->mWheel) &&
            sts::isEqual(mDataref, right->mDataref));
}

AttrManipBase * AttrManipDelta::clone() const {
    return new AttrManipDelta(*this);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrManipDelta::printObj(AbstractWriter & writer) const {
    StringStream outStr;
    outStr << ATTR_MANIP_DELTA;
    outStr << " " << cursor().toString();
    outStr << " " << down();
    outStr << " " << hold();
    outStr << " " << minimum();
    outStr << " " << maximum();
    outStr << " " << writer.actualDataref(dataref());
    outStr << " " << toolTip();
    writer.printLine(outStr.str());
    return 1 + wheel().printObj(writer);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
