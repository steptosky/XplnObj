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

#include "xpln/common/Point2.h"
#include "sts/geometry/templates/Vector2.h"
#include "converters/Defines.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

typedef sts_t::Vector2<float> Point;

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

Point2::Point2()
    : Point2(0.0f, 0.0f) { }

Point2::Point2(const Point2 & c)
    : Point2(c.x, c.y) {}

Point2::Point2(const float & v)
    : Point2(v, v) { }

Point2::Point2(float inX, float inY)
    : x(inX),
      y(inY) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

Point2 & Point2::operator=(const Point2 & c) {
    x = c.x;
    y = c.y;
    return *this;
}

Point2 & Point2::operator=(const float v) {
    *reinterpret_cast<Point*>(this) = v;
    return *this;
}

Point2 & Point2::operator+=(const Point2 & p) {
    *reinterpret_cast<Point*>(this) += *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point2 & Point2::operator+=(const float v) {
    *reinterpret_cast<Point*>(this) += v;
    return *this;
}

Point2 & Point2::operator-=(const Point2 & p) {
    *reinterpret_cast<Point*>(this) -= *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point2 & Point2::operator-=(const float v) {
    *reinterpret_cast<Point*>(this) -= v;
    return *this;
}

Point2 & Point2::operator*=(const Point2 & p) {
    *reinterpret_cast<Point*>(this) *= *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point2 & Point2::operator*=(const float v) {
    *reinterpret_cast<Point*>(this) *= v;
    return *this;
}

Point2 & Point2::operator/=(const Point2 & p) {
    *reinterpret_cast<Point*>(this) /= *reinterpret_cast<const Point*>(&p);
    return *this;
}

Point2 & Point2::operator/=(const float v) {
    *reinterpret_cast<Point*>(this) /= v;
    return *this;
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool Point2::operator==(const Point2 & p) const {
    return reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&p), FEPSILON);
}

bool Point2::operator==(const float v) const {
    return reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&v), FEPSILON);
}

bool Point2::operator!=(const Point2 & p) const {
    return !reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&p), FEPSILON);
}

bool Point2::operator!=(const float v) const {
    return !reinterpret_cast<const Point*>(this)->compare(*reinterpret_cast<const Point*>(&v), FEPSILON);
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

Point2 operator +(const Point2 & p1, const Point2 & p2) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p1);
    const Point * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 + *pp2;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator +(const Point2 & p, float v) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 + v;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator +(float v, const Point2 & p) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v + *pp1;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator -(const Point2 & p1, const Point2 & p2) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p1);
    const Point * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 - *pp2;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator -(const Point2 & p, float v) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 - v;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator -(float v, const Point2 & p) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v - *pp1;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator *(const Point2 & p1, const Point2 & p2) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p1);
    const Point * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 * *pp2;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator *(const Point2 & p, float v) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 * v;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator *(float v, const Point2 & p) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v * *pp1;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator /(const Point2 & p1, const Point2 & p2) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p1);
    const Point * pp2 = reinterpret_cast<const Point*>(&p2);
    Point res = *pp1 / *pp2;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator /(const Point2 & p, float v) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = *pp1 / v;
    return *reinterpret_cast<const Point2*>(&res);
}

Point2 operator /(float v, const Point2 & p) {
    const Point * pp1 = reinterpret_cast<const Point*>(&p);
    Point res = v / *pp1;
    return *reinterpret_cast<const Point2*>(&res);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

std::string Point2::toString(uint8_t precision /*= 4*/) const {
    return reinterpret_cast<const Point*>(this)->toString("%x %y", precision);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

float Point2::length() const {
    return reinterpret_cast<const Point*>(this)->length();
}

void Point2::normalize() {
    reinterpret_cast<Point*>(this)->normalize();
}

bool Point2::isEmpty() const {
    return reinterpret_cast<const Point*>(this)->isEmpty();
}

void Point2::clear() {
    reinterpret_cast<Point*>(this)->clear();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

}
