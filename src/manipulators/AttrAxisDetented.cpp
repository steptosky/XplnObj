/*
**  Copyright(C) 2018, StepToSky
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
#include "xpln/obj/manipulators/AttrAxisDetented.h"
#include "common/AttributeNames.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrAxisDetented::operator==(const AttrAxisDetented & other) const {
    return sts::isEqual(mDirX, other.mDirX) &&
           sts::isEqual(mDirY, other.mDirY) &&
           sts::isEqual(mDirZ, other.mDirZ) &&
           sts::isEqual(mVMin, other.mVMin) &&
           sts::isEqual(mVMax, other.mVMax) &&
           sts::isEqual(mDataref, other.mDataref) &&
           sts::isEqual(mIsEnabled, other.mIsEnabled);
}

bool AttrAxisDetented::operator!=(const AttrAxisDetented & other) const {
    return !this->operator==(other);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrAxisDetented::setDirectionX(const float val) {
    mDirX = val;
    setEnabled();
}

void AttrAxisDetented::setDirectionY(const float val) {
    mDirY = val;
    setEnabled();
}

void AttrAxisDetented::setDirectionZ(const float val) {
    mDirZ = val;
    setEnabled();
}

float AttrAxisDetented::directionX() const {
    return mDirX;
}

float AttrAxisDetented::directionY() const {
    return mDirY;
}

float AttrAxisDetented::directionZ() const {
    return mDirZ;
}

//-------------------------------------------------------------------------

void AttrAxisDetented::setVMin(const float val) {
    mVMin = val;
    setEnabled();
}

void AttrAxisDetented::setVMax(const float val) {
    mVMax = val;
    setEnabled();
}

float AttrAxisDetented::vMin() const {
    return mVMin;
}

float AttrAxisDetented::vMax() const {
    return mVMax;
}

//-------------------------------------------------------------------------

void AttrAxisDetented::setDataref(const std::string & val) {
    mDataref = val;
    setEnabled();
}

const std::string & AttrAxisDetented::dataref() const {
    return mDataref;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrAxisDetented::printObj(AbstractWriter & writer) const {
    StringStream outStr;
    outStr << ATTR_MANIP_AXIS_DETENTED;
    outStr << " " << directionX();
    outStr << " " << directionY();
    outStr << " " << directionZ();
    outStr << " " << vMin();
    outStr << " " << vMax();
    outStr << " " << dataref();
    writer.printLine(outStr.str());
    return 1;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
