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
#include "xpln/obj/manipulators/AttrManipToggle.h"
#include "xpln/enums/EManipulator.h"
#include "common/AttributeNames.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipToggle::AttrManipToggle()
    : AttrManipBase(EManipulator(EManipulator::toggle)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipToggle::setOn(const float val) {
    mOn = val;
}

void AttrManipToggle::setOff(const float val) {
    mOff = val;
}

float AttrManipToggle::on() const {
    return mOn;
}

float AttrManipToggle::off() const {
    return mOff;
}

const std::string & AttrManipToggle::dataref() const {
    return mDataref;
}

void AttrManipToggle::setDataref(const std::string & val) {
    mDataref = val;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipToggle::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipToggle*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mOn, right->mOn) &&
            sts::isEqual(mOff, right->mOff) &&
            sts::isEqual(mWheel, right->mWheel) &&
            sts::isEqual(mDataref, right->mDataref));
}

AttrManipBase * AttrManipToggle::clone() const {
    return new AttrManipToggle(*this);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrManipToggle::printObj(AbstractWriter & writer) const {
    StringStream outStr;
    outStr << ATTR_MANIP_TOGGLE;
    outStr << " " << cursor().toString();
    outStr << " " << on();
    outStr << " " << off();
    outStr << " " << writer.actualDataref(dataref());
    outStr << " " << toolTip();
    writer.writeLine(outStr.str());
    return 1 + wheel().printObj(writer);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
