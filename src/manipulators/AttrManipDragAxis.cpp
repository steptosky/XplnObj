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

#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/enums//EManipulator.h"
#include "sts/string/StringUtils.h"
#include "sts/utilities/Compare.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipDragAxis::AttrManipDragAxis()
    : AttrManipBase(EManipulator(EManipulator::drag_axis)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipDragAxis::setX(float val) {
    mX = val;
}

void AttrManipDragAxis::setY(float val) {
    mY = val;
}

void AttrManipDragAxis::setZ(float val) {
    mZ = val;
}

float AttrManipDragAxis::x() const {
    return mX;
}

float AttrManipDragAxis::y() const {
    return mY;
}

float AttrManipDragAxis::z() const {
    return mZ;
}

void AttrManipDragAxis::setVal1(float val) {
    mVal1 = val;
}

void AttrManipDragAxis::setVal2(float val) {
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

bool AttrManipDragAxis::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const AttrManipDragAxis * right = dynamic_cast<const AttrManipDragAxis*>(manip);
    if (!right)
        return false;

    const AttrManipWheel * rightWheel = static_cast<const AttrManipWheel*>(right);
    if (*static_cast<const AttrManipWheel*>(this) != *rightWheel)
        return false;

    return (sts::isEqual(mX, right->mX) &&
            sts::isEqual(mY, right->mY) &&
            sts::isEqual(mZ, right->mZ) &&
            sts::isEqual(mVal1, right->mVal1) &&
            sts::isEqual(mVal2, right->mVal2) &&
            sts::isEqual(mDataref, right->mDataref));
}

AttrManipBase * AttrManipDragAxis::clone() const {
    return new AttrManipDragAxis(*this);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
