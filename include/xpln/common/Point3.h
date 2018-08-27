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

class Point3 {
public:

    float x;
    float y;
    float z;

    //-------------------------------------------------------------------------

    XpObjLib Point3();
    XpObjLib Point3(const Point3 & c);
    XpObjLib explicit Point3(const float & v);
    XpObjLib Point3(float inX, float inY, float inZ);

    ~Point3() = default;

    //-------------------------------------------------------------------------

    XpObjLib Point3 & operator =(const Point3 & c);
    XpObjLib Point3 & operator =(float v);

    XpObjLib Point3 & operator +=(const Point3 & p);
    XpObjLib Point3 & operator +=(float v);
    XpObjLib Point3 & operator -=(const Point3 & p);
    XpObjLib Point3 & operator -=(float v);
    XpObjLib Point3 & operator *=(const Point3 & p);
    XpObjLib Point3 & operator *=(float v);
    XpObjLib Point3 & operator /=(const Point3 & p);
    XpObjLib Point3 & operator /=(float v);

    XpObjLib bool operator ==(const Point3 & p) const;
    XpObjLib bool operator ==(float v) const;
    XpObjLib bool operator !=(const Point3 & p) const;
    XpObjLib bool operator !=(float v) const;

    XpObjLib friend Point3 operator +(const Point3 & p1, const Point3 & p2);
    XpObjLib friend Point3 operator +(const Point3 & p, float v);
    XpObjLib friend Point3 operator +(float v, const Point3 & p);

    XpObjLib friend Point3 operator -(const Point3 & p1, const Point3 & p2);
    XpObjLib friend Point3 operator -(const Point3 & p, float v);
    XpObjLib friend Point3 operator -(float v, const Point3 & p);

    XpObjLib friend Point3 operator *(const Point3 & p1, const Point3 & p2);
    XpObjLib friend Point3 operator *(const Point3 & p, float v);
    XpObjLib friend Point3 operator *(float v, const Point3 & p);

    XpObjLib friend Point3 operator /(const Point3 & p1, const Point3 & p2);
    XpObjLib friend Point3 operator /(const Point3 & p, float v);
    XpObjLib friend Point3 operator /(float v, const Point3 & p);

    //-------------------------------------------------------------------------

    void set(const float inX, const float inY, const float inZ) {
        x = inX;
        y = inY;
        z = inZ;
    }

    //-------------------------------------------------------------------------

    XpObjLib float length() const;
    XpObjLib void normalize();
    XpObjLib Point3 normalized() const;
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
