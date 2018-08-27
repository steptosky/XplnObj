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

#include "stdafx.h"

#include "xpln/obj/manipulators/AttrManipDragXy.h"
#include "xpln/enums/EManipulator.h"
#include "common/AttributeNames.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipDragXy::AttrManipDragXy()
    : AttrManipBase(EManipulator(EManipulator::drag_xy)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipDragXy::setX(const float val) {
    mX = val;
}

void AttrManipDragXy::setXMin(const float val) {
    mXMin = val;
}

void AttrManipDragXy::setXMax(const float val) {
    mXMax = val;
}

float AttrManipDragXy::x() const {
    return mX;
}

float AttrManipDragXy::xMin() const {
    return mXMin;
}

float AttrManipDragXy::xMax() const {
    return mXMax;
}

void AttrManipDragXy::setY(float val) {
    mY = val;
}

void AttrManipDragXy::setYMin(float val) {
    mYMin = val;
}

void AttrManipDragXy::setYMax(float val) {
    mYMax = val;
}

float AttrManipDragXy::y() const {
    return mY;
}

float AttrManipDragXy::yMin() const {
    return mYMin;
}

float AttrManipDragXy::yMax() const {
    return mYMax;
}

const std::string & AttrManipDragXy::yDataref() const {
    return mYDataref;
}

void AttrManipDragXy::setYDataref(const std::string & val) {
    mYDataref = val;
}

const std::string & AttrManipDragXy::xDataref() const {
    return mXDataref;
}

void AttrManipDragXy::setXDataref(const std::string & val) {
    mXDataref = val;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipDragXy::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipDragXy*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mX, right->mX) &&
            sts::isEqual(mY, right->mY) &&
            sts::isEqual(mXMin, right->mXMin) &&
            sts::isEqual(mXMax, right->mXMax) &&
            sts::isEqual(mYMin, right->mYMin) &&
            sts::isEqual(mYMax, right->mYMax) &&
            sts::isEqual(mXDataref, right->mXDataref) &&
            sts::isEqual(mYDataref, right->mYDataref));
}

AttrManipBase * AttrManipDragXy::clone() const {
    return new AttrManipDragXy(*this);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrManipDragXy::printObj(AbstractWriter & writer) const {
    StringStream outStr;
    outStr << ATTR_MANIP_DRAG_XY;
    outStr << " " << cursor().toString();
    outStr << " " << x();
    outStr << " " << y();
    outStr << " " << xMin();
    outStr << " " << xMax();
    outStr << " " << yMin();
    outStr << " " << yMax();
    outStr << " " << xDataref();
    outStr << " " << yDataref();
    outStr << " " << toolTip();
    writer.printLine(outStr.str());
    return 1;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
