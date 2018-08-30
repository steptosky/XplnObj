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

#include "xpln/common/Point3.h"
#include "sts/geometry/templates/Vector3.h"
#include "converters/Defines.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

typedef sts_t::Vector3<float> Point;

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

Point3::Point3()
    : Point3(0.0f, 0.0f, 0.0f) { }

Point3::Point3(const Point3 & c)
    : Point3(c.x, c.y, c.z) {}

Point3::Point3(const float & v)
    : Point3(v, v, v) { }

Point3::Point3(const float inX, const float inY, const float inZ)
    : x(inX),
      y(inY),
      z(inZ) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

Point3 & Point3::operator=(const Point3 & c) {
    x = c.x;
    y = c.y;
    z = c.z;
    return *this;
}

Point3 & Point3::operator=(const float v) {
    *reinterpret_cast<Point*>(this) = v;
    return *this;
}

Point3 & Point3::operator+=(const Point3 & p) {
    *reinterpret_cast<Point*>(this) += *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point3 & Point3::operator+=(const float v) {
    *reinterpret_cast<Point*>(this) += v;
    return *this;
}

Point3 & Point3::operator-=(const Point3 & p) {
    *reinterpret_cast<Point*>(this) -= *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point3 & Point3::operator-=(const float v) {
    *reinterpret_cast<Point*>(this) -= v;
    return *this;
}

Point3 & Point3::operator*=(const Point3 & p) {
    *reinterpret_cast<Point*>(this) *= *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point3 & Point3::operator*=(const float v) {
    *reinterpret_cast<Point*>(this) *= v;
    return *this;
}

Point3 & Point3::operator/=(const Point3 & p) {
    *reinterpret_cast<Point*>(this) /= *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point3 & Point3::operator/=(const float v) {
    *reinterpret_cast<Point*>(this) /= v;
    return *this;
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool Point3::operator==(const Point3 & p) const {
    return reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&p), FEPSILON);
}

bool Point3::operator==(const float v) const {
    return reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&v), FEPSILON);
}

bool Point3::operator!=(const Point3 & p) const {
    return !reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&p), FEPSILON);
}

bool Point3::operator!=(const float v) const {
    return !reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&v), FEPSILON);
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

Point3 operator +(const Point3 & p1, const Point3 & p2) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p1);
    const auto * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 + *pp2;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator +(const Point3 & p, const float v) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 + v;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator +(const float v, const Point3 & p) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v + *pp1;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator -(const Point3 & p1, const Point3 & p2) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p1);
    const auto * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 - *pp2;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator -(const Point3 & p, const float v) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 - v;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator -(const float v, const Point3 & p) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v - *pp1;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator *(const Point3 & p1, const Point3 & p2) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p1);
    const auto * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 * *pp2;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator *(const Point3 & p, const float v) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 * v;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator *(const float v, const Point3 & p) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v * *pp1;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator /(const Point3 & p1, const Point3 & p2) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p1);
    const auto * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 / *pp2;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator /(const Point3 & p, const float v) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 / v;
    return *reinterpret_cast<const Point3*>(&res);
}

Point3 operator /(const float v, const Point3 & p) {
    const auto * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v / *pp1;
    return *reinterpret_cast<const Point3*>(&res);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

std::string Point3::toString(const std::uint8_t precision /*= 4*/) const {
    return reinterpret_cast<const Point*>(this)->toString("%x %y %z", precision);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

float Point3::length() const {
    return reinterpret_cast<const Point*>(this)->length();
}

void Point3::normalize() {
    reinterpret_cast<Point*>(this)->normalize();
}

Point3 Point3::normalized() const {
    Point n = reinterpret_cast<const Point*>(this)->normalized();
    return *reinterpret_cast<Point3*>(&n);
}

bool Point3::isEmpty() const {
    return reinterpret_cast<const Point*>(this)->isEmpty();
}

void Point3::clear() {
    reinterpret_cast<Point*>(this)->clear();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

}
