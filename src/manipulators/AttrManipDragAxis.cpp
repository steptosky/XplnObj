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
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/enums//EManipulator.h"
#include "common/AttributeNames.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipDragAxis::AttrManipDragAxis()
    : AttrManipBase(EManipulator(EManipulator::drag_axis)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipDragAxis::setDirectionX(const float val) {
    mX = val;
}

void AttrManipDragAxis::setDirectionY(const float val) {
    mY = val;
}

void AttrManipDragAxis::setDirectionZ(const float val) {
    mZ = val;
}

float AttrManipDragAxis::directionX() const {
    return mX;
}

float AttrManipDragAxis::directionY() const {
    return mY;
}

float AttrManipDragAxis::directionZ() const {
    return mZ;
}

void AttrManipDragAxis::setVal1(const float val) {
    mVal1 = val;
}

void AttrManipDragAxis::setVal2(const float val) {
    mVal2 = val;
}

float AttrManipDragAxis::val1() const {
    return mVal1;
}

float AttrManipDragAxis::val2() const {
    return mVal2;
}

const std::string & AttrManipDragAxis::dataref() const {
    return mDataref;
}

void AttrManipDragAxis::setDataref(const std::string & val) {
    mDataref = val;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

const AttrAxisDetented & AttrManipDragAxis::axisDetented() const {
    return mAxisDetented;
}

void AttrManipDragAxis::setAxisDetented(const AttrAxisDetented & val) {
    mAxisDetented = val;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipDragAxis::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipDragAxis*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mX, right->mX) &&
            sts::isEqual(mY, right->mY) &&
            sts::isEqual(mZ, right->mZ) &&
            sts::isEqual(mVal1, right->mVal1) &&
            sts::isEqual(mVal2, right->mVal2) &&
            sts::isEqual(mAxisDetented, right->mAxisDetented) &&
            sts::isEqual(mAxisDetentRanges, right->mAxisDetentRanges) &&
            sts::isEqual(mWheel, right->mWheel) &&
            sts::isEqual(mDataref, right->mDataref));
}

AttrManipBase * AttrManipDragAxis::clone() const {
    return new AttrManipDragAxis(*this);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrManipDragAxis::printObj(AbstractWriter & writer) const {
    std::size_t outCounter = 1;
    StringStream outStr;
    outStr << ATTR_MANIP_DRAG_AXIS;
    outStr << " " << cursor().toString();
    outStr << " " << directionX();
    outStr << " " << directionY();
    outStr << " " << directionZ();
    outStr << " " << val1();
    outStr << " " << val2();
    outStr << " " << writer.actualDataref(dataref());
    outStr << " " << toolTip();
    writer.printLine(outStr.str());

    outCounter += wheel().printObj(writer);

    const auto & detented = axisDetented();
    if (detented.isEnabled()) {
        outCounter += detented.printObj(writer);

        const auto & detentRangesList = detentRanges();
        for (const auto & v : detentRangesList) {
            outCounter += v.printObj(writer);
        }
    }

    return outCounter;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
