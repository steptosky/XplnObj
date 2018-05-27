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

#include "xpln/common/Quaternion.h"
#include "sts/geometry/Quaternion.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

inline sts::QuaternionF * gTreePtr(void * inPtr) {
    return reinterpret_cast<sts::QuaternionF*>(inPtr);
}

#define QUAT_PTR gTreePtr(this->mData)

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

Quaternion::Quaternion() {
    mData = new sts::QuaternionF();
}

//-------------------------------------------------------------------------

Quaternion::Quaternion(const Quaternion & copy) {
    *this = copy;
}

//-------------------------------------------------------------------------

Quaternion::Quaternion(float x, float y, float z, float w) {
    mData = new sts::QuaternionF(x, y, z, w);
}

//-------------------------------------------------------------------------

Quaternion::~Quaternion() {
    if (mData)
        delete QUAT_PTR;
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

Quaternion & Quaternion::operator =(const Quaternion & copy) {
    *reinterpret_cast<sts::QuaternionF*>(mData) = *reinterpret_cast<sts::QuaternionF*>(copy.mData);
    return *this;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void Quaternion::setX(float x) {
    QUAT_PTR->setX(x);
}

//-------------------------------------------------------------------------

void Quaternion::setY(float y) {
    QUAT_PTR->setY(y);
}

//-------------------------------------------------------------------------

void Quaternion::setZ(float z) {
    QUAT_PTR->setZ(z);
}

//-------------------------------------------------------------------------

void Quaternion::setW(float w) {
    QUAT_PTR->setW(w);
}

//-------------------------------------------------------------------------

void Quaternion::setValues(float x, float y, float z, float w) {
    QUAT_PTR->set(x, y, z, w);
}

//-------------------------------------------------------------------------

float Quaternion::x() const {
    return QUAT_PTR->x();
}

//-------------------------------------------------------------------------

float Quaternion::y() const {
    return QUAT_PTR->y();
}

//-------------------------------------------------------------------------

float Quaternion::z() const {
    return QUAT_PTR->z();
}

//-------------------------------------------------------------------------

float Quaternion::w() const {
    return QUAT_PTR->w();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
