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

#pragma once

#include <cassert>
#include <limits>
#include <iostream>
#include "Vector3.h"
#include "sts/utilities/Compare.h"
#include "../DrConverters.h"

namespace sts_t {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
\details Quaternion
*/
template<class T>
class Quaternion {
    static_assert(std::numeric_limits<T>::is_iec559,
        "The class can use only floating types");

    T mData[4];

    const unsigned char ioVersion() const;
    const unsigned ioIdSize() const;
    const char * ioId() const;

public:

    typedef T Type;
    typedef Type value_type;

    Quaternion();
    Quaternion(Type inX, Type inY, Type inZ, Type inW);
    ~Quaternion() = default;

    //-------------------------------------------------------------------------

    bool operator ==(const Quaternion & inQ) const;
    bool operator !=(const Quaternion & inQ) const;

    const Type & operator[](size_t i) const;
    Type & operator[](size_t i);

    Quaternion operator *(const Quaternion & inQ) const;
    //Quaternion operator / (const Quaternion& inQ) const;
    Quaternion operator *(Type inScalar) const;
    Quaternion operator /(Type inScalar) const;

    Quaternion & operator *=(const Quaternion & inQ);
    //Quaternion& operator /= (const Quaternion& inQ);
    Quaternion & operator *=(Type inScalar);
    Quaternion & operator /=(Type inScalar);

    //-------------------------------------------------------------------------

    bool isIdentity() const;
    bool isIdentityOrNull() const;
    bool isNull() const;

    //-------------------------------------------------------------------------

    void setX(const Type inX);
    void setY(const Type inY);
    void setZ(const Type inZ);
    void setW(const Type inW);

    Type x() const;
    Type y() const;
    Type z() const;
    Type w() const;

    void set(Type inX, Type inY, Type inZ, Type inW);

    //-------------------------------------------------------------------------

    void conjugate();
    Quaternion conjugated() const;

    double length() const;
    double dot(const Quaternion & q) const;
    void normalize();
    Quaternion normalized() const;
    void clear();
    void zero();
    void identity();

    //-------------------------------------------------------------------------

    void save(std::ostream & outStream) const;

    /*!
    \exception std::runtime_error
    */
    void load(std::istream & inStream);

    template<class T2>
    friend std::ostream & operator <<(std::ostream & stream, const Quaternion<T2> & inMtx);

    /*!
    \exception std::runtime_error
    */
    template<class T2>
    friend std::istream & operator >>(std::istream & stream, Quaternion<T2> & outMtx);

    std::string toString(const std::string & inFormat = "%x %y %z %w", uint8_t precision = 6);

    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

#include "Quaternion.inl"

}
