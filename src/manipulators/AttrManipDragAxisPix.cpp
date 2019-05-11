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
#include "xpln/obj/manipulators/AttrManipDragAxisPix.h"
#include "xpln/enums/EManipulator.h"
#include "common/AttributeNames.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipDragAxisPix::AttrManipDragAxisPix()
    : AttrManipBase(EManipulator(EManipulator::drag_axis_pix)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipDragAxisPix::setDxPix(const int val) {
    mDxPix = val;
}

void AttrManipDragAxisPix::setStep(const int val) {
    mStep = val;
}

void AttrManipDragAxisPix::setExp(const float val) {
    mExp = val;
}

int AttrManipDragAxisPix::dxPix() const {
    return mDxPix;
}

int AttrManipDragAxisPix::step() const {
    return mStep;
}

float AttrManipDragAxisPix::exp() const {
    return mExp;
}

void AttrManipDragAxisPix::setVal1(const float val) {
    mVal1 = val;
}

void AttrManipDragAxisPix::setVal2(const float val) {
    mVal2 = val;
}

float AttrManipDragAxisPix::val1() const {
    return mVal1;
}

float AttrManipDragAxisPix::val2() const {
    return mVal2;
}

const std::string & AttrManipDragAxisPix::dataref() const {
    return mDataref;
}

void AttrManipDragAxisPix::setDataref(const std::string & val) {
    mDataref = val;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipDragAxisPix::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipDragAxisPix*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mDxPix, right->mDxPix) &&
            sts::isEqual(mStep, right->mStep) &&
            sts::isEqual(mExp, right->mExp) &&
            sts::isEqual(mVal1, right->mVal1) &&
            sts::isEqual(mVal2, right->mVal2) &&
            sts::isEqual(mWheel, right->mWheel) &&
            sts::isEqual(mDataref, right->mDataref));
}

AttrManipBase * AttrManipDragAxisPix::clone() const {
    return new AttrManipDragAxisPix(*this);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrManipDragAxisPix::printObj(AbstractWriter & writer) const {
    StringStream outStr;
    outStr << ATTR_MANIP_DRAG_AXIS_PIX;
    outStr << " " << cursor().toString();
    outStr << " " << dxPix();
    outStr << " " << step();
    outStr << " " << exp();
    outStr << " " << val1();
    outStr << " " << val2();
    outStr << " " << writer.actualDataref(dataref());
    outStr << " " << toolTip();
    writer.writeLine(outStr.str());
    return 1 + wheel().printObj(writer);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
