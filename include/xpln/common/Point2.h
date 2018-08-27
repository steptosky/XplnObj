#pragma once

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

#include <cstdint>
#include <string>
#include "xpln/Export.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class Point2 {
public:

    float x;
    float y;

    //-------------------------------------------------------------------------

    XpObjLib Point2();
    XpObjLib Point2(const Point2 & c);
    XpObjLib explicit Point2(const float & v);
    XpObjLib Point2(float inX, float inY);

    ~Point2() = default;

    //-------------------------------------------------------------------------

    XpObjLib Point2 & operator =(const Point2 & c);
    XpObjLib Point2 & operator =(float v);

    XpObjLib Point2 & operator +=(const Point2 & p);
    XpObjLib Point2 & operator +=(float v);
    XpObjLib Point2 & operator -=(const Point2 & p);
    XpObjLib Point2 & operator -=(float v);
    XpObjLib Point2 & operator *=(const Point2 & p);
    XpObjLib Point2 & operator *=(float v);
    XpObjLib Point2 & operator /=(const Point2 & p);
    XpObjLib Point2 & operator /=(float v);

    XpObjLib bool operator ==(const Point2 & p) const;
    XpObjLib bool operator ==(float v) const;
    XpObjLib bool operator !=(const Point2 & p) const;
    XpObjLib bool operator !=(float v) const;

    XpObjLib friend Point2 operator +(const Point2 & p1, const Point2 & p2);
    XpObjLib friend Point2 operator +(const Point2 & p, float v);
    XpObjLib friend Point2 operator +(float v, const Point2 & p);

    XpObjLib friend Point2 operator -(const Point2 & p1, const Point2 & p2);
    XpObjLib friend Point2 operator -(const Point2 & p, float v);
    XpObjLib friend Point2 operator -(float v, const Point2 & p);

    XpObjLib friend Point2 operator *(const Point2 & p1, const Point2 & p2);
    XpObjLib friend Point2 operator *(const Point2 & p, float v);
    XpObjLib friend Point2 operator *(float v, const Point2 & p);

    XpObjLib friend Point2 operator /(const Point2 & p1, const Point2 & p2);
    XpObjLib friend Point2 operator /(const Point2 & p, float v);
    XpObjLib friend Point2 operator /(float v, const Point2 & p);

    //-------------------------------------------------------------------------

    void set(const float inX, const float inY) {
        x = inX;
        y = inY;
    }

    //-------------------------------------------------------------------------

    XpObjLib float length() const;
    XpObjLib void normalize();
    XpObjLib bool isEmpty() const;
    XpObjLib void clear();

    //-------------------------------------------------------------------------

    XpObjLib std::string toString(uint8_t precision = 6) const;

    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
