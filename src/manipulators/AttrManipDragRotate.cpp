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

#include "stdafx.h"

#include "xpln/obj/manipulators/AttrManipDragRotate.h"
#include "xpln/enums//EManipulator.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipDragRotate::AttrManipDragRotate()
    : AttrManipBase(EManipulator(EManipulator::drag_rotate)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AttrManipDragRotate::setX(const float val) {
    mX = val;
}

void AttrManipDragRotate::setY(const float val) {
    mY = val;
}

void AttrManipDragRotate::setZ(const float val) {
    mZ = val;
}

float AttrManipDragRotate::x() const {
    return mX;
}

float AttrManipDragRotate::y() const {
    return mY;
}

float AttrManipDragRotate::z() const {
    return mZ;
}

//-------------------------------------------------------------------------

void AttrManipDragRotate::setDirectionX(const float val) {
    mDirX = val;
}

void AttrManipDragRotate::setDirectionY(const float val) {
    mDirY = val;
}

void AttrManipDragRotate::setDirectionZ(const float val) {
    mDirZ = val;
}

float AttrManipDragRotate::directionX() const {
    return mDirX;
}

float AttrManipDragRotate::directionY() const {
    return mDirY;
}

float AttrManipDragRotate::directionZ() const {
    return mDirZ;
}

//-------------------------------------------------------------------------

void AttrManipDragRotate::setAngle1(const float val) {
    mAngle1 = val;
}

void AttrManipDragRotate::setAngle2(const float val) {
    mAngle2 = val;
}

float AttrManipDragRotate::angle1() const {
    return mAngle1;
}

float AttrManipDragRotate::angle2() const {
    return mAngle2;
}

//-------------------------------------------------------------------------

void AttrManipDragRotate::setLift(const float val) {
    mLift = val;
}

float AttrManipDragRotate::lift() const {
    return mLift;
}

//-------------------------------------------------------------------------

void AttrManipDragRotate::setV1Min(const float val) {
    mV1Min = val;
}

void AttrManipDragRotate::setV1Max(const float val) {
    mV1Max = val;
}

float AttrManipDragRotate::v1Min() const {
    return mV1Min;
}

float AttrManipDragRotate::v1Max() const {
    return mV1Max;
}

//-------------------------------------------------------------------------

void AttrManipDragRotate::setV2Min(const float val) {
    mV2Min = val;
}

void AttrManipDragRotate::setV2Max(const float val) {
    mV2Max = val;
}

float AttrManipDragRotate::v2Min() const {
    return mV2Min;
}

float AttrManipDragRotate::v2Max() const {
    return mV2Max;
}

//-------------------------------------------------------------------------

void AttrManipDragRotate::setDataref1(const std::string & val) {
    mDataref1 = val;
}

void AttrManipDragRotate::setDataref2(const std::string & val) {
    mDataref2 = val;
}

const std::string & AttrManipDragRotate::dataref1() const {
    return mDataref1;
}

const std::string & AttrManipDragRotate::dataref2() const {
    return mDataref2;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipDragRotate::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipDragRotate*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mX, right->mX) &&
            sts::isEqual(mY, right->mY) &&
            sts::isEqual(mZ, right->mZ) &&
            sts::isEqual(mDirX, right->mDirX) &&
            sts::isEqual(mDirY, right->mDirY) &&
            sts::isEqual(mDirZ, right->mDirZ) &&
            sts::isEqual(mAngle1, right->mAngle1) &&
            sts::isEqual(mAngle2, right->mAngle2) &&
            sts::isEqual(mLift, right->mLift) &&
            sts::isEqual(mV1Min, right->mV1Min) &&
            sts::isEqual(mV1Max, right->mV1Max) &&
            sts::isEqual(mV2Min, right->mV2Min) &&
            sts::isEqual(mV2Max, right->mV2Max) &&
            sts::isEqual(mDataref1, right->mDataref1) &&
            sts::isEqual(mDataref2, right->mDataref2) &&
            sts::isEqual(mKeys, right->mKeys) &&
            sts::isEqual(mAxisDetentRanges, right->mAxisDetentRanges));
}

AttrManipBase * AttrManipDragRotate::clone() const {
    return new AttrManipDragRotate(*this);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
