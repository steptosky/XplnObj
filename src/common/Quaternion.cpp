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

inline sts::QuaternionF & quat(Quaternion * quat) {
    return reinterpret_cast<sts::QuaternionF&>(*quat);
}

inline const sts::QuaternionF & quat(const Quaternion * quat) {
    return reinterpret_cast<const sts::QuaternionF&>(*quat);
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

Quaternion::Quaternion(const Quaternion & copy) noexcept {
    *this = copy;
}

Quaternion::Quaternion(const float x, const float y, const float z, const float w) noexcept {
    quat(this).set(x, y, z, w);
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

Quaternion & Quaternion::operator =(const Quaternion & copy) noexcept {
    quat(this) = quat(&copy);
    return *this;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void Quaternion::setX(const float x) noexcept {
    quat(this).setX(x);
}

//-------------------------------------------------------------------------

void Quaternion::setY(const float y) noexcept {
    quat(this).setY(y);
}

//-------------------------------------------------------------------------

void Quaternion::setZ(const float z) noexcept {
    quat(this).setZ(z);
}

//-------------------------------------------------------------------------

void Quaternion::setW(const float w) noexcept {
    quat(this).setW(w);
}

//-------------------------------------------------------------------------

void Quaternion::setValues(const float x, const float y, const float z, const float w) noexcept {
    quat(this).set(x, y, z, w);
}

//-------------------------------------------------------------------------

float Quaternion::x() const noexcept {
    return quat(this).x();
}

//-------------------------------------------------------------------------

float Quaternion::y() const noexcept {
    return quat(this).y();
}

//-------------------------------------------------------------------------

float Quaternion::z() const noexcept {
    return quat(this).z();
}

//-------------------------------------------------------------------------

float Quaternion::w() const noexcept {
    return quat(this).w();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
