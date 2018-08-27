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

#include "xpln/common/TMatrix.h"
#include "sts/geometry/Quaternion.h"
#include "sts/geometry/Converters.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

typedef sts_t::Vector3<float> Point;
typedef sts_t::TMatrix3<float> Mtx3;

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

TMatrix::TMatrix() {
    reinterpret_cast<Mtx3*>(this)->setIdentity();
}

TMatrix::TMatrix(const TMatrix & inCopy) {
    *reinterpret_cast<Mtx3*>(this) = *reinterpret_cast<const Mtx3*>(&inCopy);
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

TMatrix & TMatrix::operator=(const TMatrix & inCopy) {
    *reinterpret_cast<Mtx3*>(this) = *reinterpret_cast<const Mtx3*>(&inCopy);
    return *this;
}

bool TMatrix::operator==(const TMatrix & tr) const {
    return *reinterpret_cast<const Mtx3*>(this) == *reinterpret_cast<const Mtx3*>(&tr);
}

bool TMatrix::operator!=(const TMatrix & tr) const {
    return *reinterpret_cast<const Mtx3*>(this) != *reinterpret_cast<const Mtx3*>(&tr);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void TMatrix::rotateRadiansX(const float inAngleRadians) {
    reinterpret_cast<Mtx3*>(this)->rotateX(inAngleRadians);
}

void TMatrix::rotateRadiansY(const float inAngleRadians) {
    reinterpret_cast<Mtx3*>(this)->rotateY(inAngleRadians);
}

void TMatrix::rotateRadiansZ(const float inAngleRadians) {
    reinterpret_cast<Mtx3*>(this)->rotateZ(inAngleRadians);
}

void TMatrix::rotateDegreesX(const float inAngleRadians) {
    reinterpret_cast<Mtx3*>(this)->rotateX(sts::toRadians(inAngleRadians));
}

void TMatrix::rotateDegreesY(const float inAngleRadians) {
    reinterpret_cast<Mtx3*>(this)->rotateY(sts::toRadians(inAngleRadians));
}

void TMatrix::rotateDegreesZ(const float inAngleRadians) {
    reinterpret_cast<Mtx3*>(this)->rotateZ(sts::toRadians(inAngleRadians));
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void TMatrix::setPosition(const Point3 & p) {
    reinterpret_cast<Mtx3*>(this)->setTranslateIdentity();
    reinterpret_cast<Mtx3*>(this)->translate(p.x, p.y, p.z);
}

void TMatrix::setRotate(const Quaternion & q) {
    sts::fromQuat(*reinterpret_cast<Mtx3*>(this), sts::QuaternionF(q.x(), q.y(), q.z(), q.w()));
}

void TMatrix::setRotate(const Point3 & p, float angleDegress) {
    sts::fromAxisAngle(*reinterpret_cast<Mtx3*>(this), Mtx3::Vec3(p.x, p.y, p.z), sts::toRadians(angleDegress));
}

//-------------------------------------------------------------------------

bool TMatrix::parity() const {
    return reinterpret_cast<const Mtx3*>(this)->isParity();
}

Point3 TMatrix::row(size_t i) const {
    return Point3((*reinterpret_cast<const Mtx3*>(this))(i, 0),
                  (*reinterpret_cast<const Mtx3*>(this))(i, 1),
                  (*reinterpret_cast<const Mtx3*>(this))(i, 2));
}

Point3 TMatrix::position() const {
    return Point3((*reinterpret_cast<const Mtx3*>(this))(3, 0),
                  (*reinterpret_cast<const Mtx3*>(this))(3, 1),
                  (*reinterpret_cast<const Mtx3*>(this))(3, 2));
}

Quaternion TMatrix::rotation() const {
    sts_t::Quaternion<float> sq = sts::toQuat<float>(*reinterpret_cast<const Mtx3*>(this));
    return Quaternion(sq.x(), sq.y(), sq.z(), sq.w());
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void TMatrix::transformPoints(Point3 * inArray, const unsigned inCount) const {
    if (!inArray || !inCount)
        return;
    auto * p = reinterpret_cast<Point*>(&inArray);
    reinterpret_cast<const Mtx3*>(this)->mapPoints(p, inCount);
}

void TMatrix::transformVectors(Point3 * inArray, const unsigned inCount) const {
    if (!inArray || !inCount)
        return;
    auto * p = reinterpret_cast<Point*>(&inArray);
    reinterpret_cast<const Mtx3*>(this)->mapVectors(p, inCount);
}

void TMatrix::transformPoint(Point3 & inPoint) const {
    auto * p = reinterpret_cast<Point*>(&inPoint);
    *p = reinterpret_cast<const Mtx3*>(this)->mapPoint(*p);
}

void TMatrix::transformVector(Point3 & inVec) const {
    auto * p = reinterpret_cast<Point*>(& inVec);
    *p = reinterpret_cast<const Mtx3*>(this)->mapVector(*p);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

TMatrix & TMatrix::operator*=(const TMatrix & inRight) {
    *reinterpret_cast<Mtx3*>(this) *= *reinterpret_cast<const Mtx3*>(&inRight);
    return *this;
}

TMatrix TMatrix::operator*(const TMatrix & inRight) const {
    TMatrix out(*this);
    out *= inRight;
    return out;
}

TMatrix TMatrix::inversed() const {
    const Mtx3 tmInv = reinterpret_cast<const Mtx3*>(this)->inversed();
    return TMatrix(*reinterpret_cast<const TMatrix*>(&tmInv));
}

std::string TMatrix::toString() const {
    std::string out("\n");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(0, 0))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(0, 1))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(0, 2))).append("\t");
    out.append("\n");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(1, 0))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(1, 1))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(1, 2))).append("\t");
    out.append("\n");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(2, 0))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(2, 1))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(2, 2))).append("\t");
    out.append("\n");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(3, 0))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(3, 1))).append("\t");
    out.append(sts::toMbString((*reinterpret_cast<const Mtx3*>(this))(3, 2))).append("\t");
    out.append("\n");
    return out;
}

void TMatrix::set(
    const float m00, const float m01, const float m02,
    const float m10, const float m11, const float m12,
    const float m20, const float m21, const float m22,
    const float m30, const float m31, const float m32) {
    reinterpret_cast<Mtx3*>(this)->set(m00, m01, m02,
                                       m10, m11, m12,
                                       m20, m21, m22,
                                       m30, m31, m32);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void TMatrix::setTranslateIdentity() {
    reinterpret_cast<Mtx3*>(this)->setTranslateIdentity();
}

void TMatrix::setRotateIdentity(bool leaveScale) {
    reinterpret_cast<Mtx3*>(this)->setRotateIdentity(leaveScale);
}

void TMatrix::setIdentity() {
    reinterpret_cast<Mtx3*>(this)->setIdentity();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
