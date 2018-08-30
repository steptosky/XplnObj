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

#include <sstream>
#include "sts/utilities/Compare.h"

namespace sts_t {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details 3 Dimensions vector.
 */
template<class T>
class Vector3 {
public:

    T x;
    T y;
    T z;

    typedef T value_type;

    //-------------------------------------------------------------------------

    /*! \details Constructor default. */
    Vector3() = default;

    /*! \details Constructor fill. */
    explicit Vector3(value_type inFill) {
        *this = inFill;
    }

    /*! \details Constructor init. */
    Vector3(value_type inX, value_type inY, value_type inZ)
        : x(inX),
          y(inY),
          z(inZ) {}

    /*! \details Destructor. */
    ~Vector3() = default;

    //-------------------------------------------------------------------------

    void set(const value_type & inX, const value_type & inY, const value_type & inZ) {
        x = inX;
        y = inY;
        z = inZ;
    }

    void clear() {
        set(value_type(0), value_type(0), value_type(0));
    }

    //-------------------------------------------------------------------------

    void offsetX(value_type inOffset) {
        x += inOffset;
    }

    void offsetY(value_type inOffset) {
        y += inOffset;
    }

    void offsetZ(value_type inOffset) {
        z += inOffset;
    }

    void offset(value_type inX, value_type inY, value_type inZ) {
        x += inX;
        y += inY;
        z += inZ;
    }

    //-------------------------------------------------------------------------

    /*!
    * \details Mirrors the vector.
    */
    void mirror() {
        static_assert(std::numeric_limits<value_type>::is_signed,
            "The method can't use unsigned type");
        *this *= static_cast<value_type>(-1);
    }

    /*!
    * \details Gets new mirrored vector.
    * \return New mirrored vector.
    */
    Vector3 mirrored() const {
        static_assert(std::numeric_limits<value_type>::is_signed,
            "The method can't use unsigned type");
        return Vector3(-x, -y, -z);
    }

    //-------------------------------------------------------------------------

    /*!
    * \details Gets the vector length.
    * \return vector length.
    */
    value_type length() const {
        return static_cast<value_type>(sqrt(static_cast<double>(x * x + y * y + z * z)));
    }

    //-------------------------------------------------------------------------

    /*!
    * \details Sets the vector length.
    * \param [in] len new length.
    */
    void setLength(value_type len) {
        static_assert(std::numeric_limits<value_type>::is_iec559,
            "The method can use only floating types");
        isNull() ? set(value_type(1), value_type(0), value_type(0)) : normalize();
        *this *= len;
    }

    //-------------------------------------------------------------------------

    /*!
    * \details Check is the vector's components are equaled 0.
    * \return True if all vector's components are equaled 0, otherwise false.
    */
    bool isNull() const {
        return (sts::isEqual(x, value_type(0)) &&
                sts::isEqual(y, value_type(0)) &&
                sts::isEqual(z, value_type(0)));
    }

    /*!
    * \see isNull.
    */
    bool isEmpty() const {
        return isNull();
    }

    //-------------------------------------------------------------------------

    /*! \details Normalize the vector. */
    void normalize() {
        static_assert(std::numeric_limits<value_type>::is_iec559,
            "The method can use only floating types");
        value_type len = length();
        if (sts::isEqual(len, value_type(0)))
            return;
        *this /= len;
    }

    //-------------------------------------------------------------------------

    /*!
     * \details Gets new normalized vector
     * \return New normalized vector
     */
    Vector3 normalized() const {
        static_assert(std::numeric_limits<value_type>::is_iec559,
            "The method can use only floating types");
        value_type len = length();
        if (sts::isEqual(len, value_type(0)))
            return Vector3();
        return Vector3(*this / len);
    }

    //-------------------------------------------------------------------------

    /*!
     * \details Dot product.
     * \param [in] inVec other vector.
     */
    value_type dot(const Vector3 & inVec) const {
        return (x * inVec.x + y * inVec.y + z * inVec.z);
    }

    //-------------------------------------------------------------------------

    Vector3 crossProduct(const Vector3 & inVec) const {
        static_assert(std::numeric_limits<value_type>::is_signed,
            "The method can't use unsigned type");
        /*
        vec vector;
        vector.x = y*Bz - By*z;
        vector.y = Bx*z - x*Bz;
        vector.z = x*By - y*Bx;
        */
        Vector3 outVec;
        outVec.x = (this->y * inVec.z - inVec.y * this->z);
        outVec.y = (inVec.x * this->z - this->x * inVec.z);
        outVec.z = (this->x * inVec.y - this->y * inVec.x);
        return outVec;
    }

    //-------------------------------------------------------------------------

    /*!
    * \details Compares two vector with epsilon.
    * \return True if the verctors are equaled otherwise false.
    */
    bool compare(const Vector3 & p2, const value_type epsilon = std::numeric_limits<value_type>::epsilon()) const {
        static_assert(std::numeric_limits<value_type>::is_iec559,
            "The method can use only floating types");
        return (
            sts::isEqual(x, p2.x, epsilon) &&
            sts::isEqual(y, p2.y, epsilon) &&
            sts::isEqual(z, p2.z, epsilon));
    }

    /*!
    * \details Compares vector's components to value with epsilon.
    * \return True if the vector's components and value are equaled otherwise false.
    */
    bool compare(const value_type & v, const value_type epsilon = std::numeric_limits<value_type>::epsilon()) const {
        static_assert(std::numeric_limits<value_type>::is_iec559,
            "The method can use only floating types");
        return (
            sts::isEqual(x, v, epsilon) &&
            sts::isEqual(y, v, epsilon) &&
            sts::isEqual(z, v, epsilon));
    }

    //-------------------------------------------------------------------------

    bool operator ==(const Vector3 & p2) const {
        return (
            sts::isEqual(x, p2.x) &&
            sts::isEqual(y, p2.y) &&
            sts::isEqual(z, p2.z));
    }

    bool operator ==(const value_type & v) const {
        return (
            sts::isEqual(x, v) &&
            sts::isEqual(y, v) &&
            sts::isEqual(z, v));
    }

    bool operator !=(const Vector3 & p2) const {
        return (
            sts::isNotEqual(x, p2.x) ||
            sts::isNotEqual(y, p2.y) ||
            sts::isNotEqual(z, p2.z));
    }

    bool operator !=(const value_type & v) const {
        return (
            sts::isNotEqual(x, v) ||
            sts::isNotEqual(y, v) ||
            sts::isNotEqual(z, v));
    }

    //-------------------------------------------------------------------------

    Vector3 & operator =(const Vector3 & p) {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }

    Vector3 & operator =(const value_type & v) {
        x = v;
        y = v;
        z = v;
        return *this;
    }

    //-------------------------------------------------------------------------

    Vector3 & operator +=(const Vector3 & p) {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    Vector3 & operator +=(const value_type & v) {
        x += v;
        y += v;
        z += v;
        return *this;
    }

    //-------------------------------------------------------------------------

    Vector3 & operator -=(const Vector3 & p) {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }

    Vector3 & operator -=(const value_type & v) {
        x -= v;
        y -= v;
        z -= v;
        return *this;
    }

    //-------------------------------------------------------------------------

    Vector3 & operator *=(const Vector3 & p) {
        x *= p.x;
        y *= p.y;
        z *= p.z;
        return *this;
    }

    Vector3 & operator *=(const value_type & v) {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }

    //-------------------------------------------------------------------------

    Vector3 & operator /=(const Vector3 & p) {
        if (!sts::isEqual(p.x, value_type(0)))
            x /= p.x;
        if (!sts::isEqual(p.y, value_type(0)))
            y /= p.y;
        if (!sts::isEqual(p.z, value_type(0)))
            z /= p.z;
        return *this;
    }

    Vector3 & operator /=(const value_type & v) {
        if (sts::isEqual(v, value_type(0)))
            return *this;
        x /= v;
        y /= v;
        z /= v;
        return *this;
    }

    //-------------------------------------------------------------------------

    friend Vector3 operator +(const Vector3 & p1, const Vector3 & p2) { return Vector3(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z); }
    friend Vector3 operator +(const Vector3 & p, const value_type & v) { return Vector3(p.x + v, p.y + v, p.z + v); }
    friend Vector3 operator +(const value_type & v, const Vector3 & p) { return Vector3(v + p.x, v + p.y, v + p.z); }

    //-------------------------------------------------------------------------

    friend Vector3 operator -(const Vector3 & p1, const Vector3 & p2) { return Vector3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z); }
    friend Vector3 operator -(const Vector3 & p, const value_type & v) { return Vector3(p.x - v, p.y - v, p.z - v); }
    friend Vector3 operator -(const value_type & v, const Vector3 & p) { return Vector3(v - p.x, v - p.y, v - p.z); }

    //-------------------------------------------------------------------------

    friend Vector3 operator *(const Vector3 & p1, const Vector3 & p2) { return Vector3(p1.x * p2.x, p1.y * p2.y, p1.z * p2.z); }
    friend Vector3 operator *(const Vector3 & p, const value_type & v) { return Vector3(p.x * v, p.y * v, p.z * v); }
    friend Vector3 operator *(const value_type & v, const Vector3 & p) { return Vector3(v * p.x, v * p.y, v * p.z); }

    //-------------------------------------------------------------------------

    friend Vector3 operator /(const Vector3 & p1, const Vector3 & p2) {
        return Vector3(
                       sts::isEqual(p2.x, value_type(0)) ? p1.x : p1.x / p2.x,
                       sts::isEqual(p2.y, value_type(0)) ? p1.y : p1.y / p2.y,
                       sts::isEqual(p2.z, value_type(0)) ? p1.z : p1.z / p2.z);
    }

    friend Vector3 operator /(const Vector3 & p, const value_type & v) {
        if (sts::isEqual(v, value_type(0)))
            return Vector3(p);
        return Vector3(p.x / v, p.y / v, p.z / v);
    }

    friend Vector3 operator /(const value_type & v, const Vector3 & p) {
        return Vector3(
                       sts::isEqual(p.x, value_type(0)) ? v : v / p.x,
                       sts::isEqual(p.y, value_type(0)) ? v : v / p.y,
                       sts::isEqual(p.z, value_type(0)) ? v : v / p.z);
    }

    //-------------------------------------------------------------------------

    /*!
     * \details Make a formated string with values of the vector.
     * \param [in] inFormat use x, y, z, for printing the values. Example: "x:%x y:%y z:%z"
     * \param [in] precision
     * \return formated string.
     */
    std::string toString(const std::string & inFormat = "x:%x y:%y z:%z", std::streamsize precision = 6) const {
        std::stringstream out;
        out.precision(precision);
        out << std::fixed;
        bool val = false;
        for (const char & curr : inFormat) {
            if (val) {
                switch (curr) {
                    case 'x': out << x;
                        break;
                    case 'y': out << y;
                        break;
                    case 'z': out << z;
                        break;
                    default: break;
                }
                val = false;
                continue;
            }
            if (curr == '%') {
                val = true;
                continue;
            }

            out << curr;
        }
        return out.str();
    }

    //-------------------------------------------------------------------------

    Vector3<int8_t> toInt8() const { return Vector3<int8_t>(int8_t(x), int8_t(y), int8_t(z)); }
    Vector3<uint8_t> toUint8() const { return Vector3<uint8_t>(uint8_t(x), uint8_t(y), uint8_t(z)); }
    Vector3<int16_t> toInt16() const { return Vector3<int16_t>(int16_t(x), int16_t(y), int16_t(z)); }
    Vector3<uint16_t> toUint16() const { return Vector3<uint16_t>(uint16_t(x), uint16_t(y), uint16_t(z)); }
    Vector3<int32_t> toInt32() const { return Vector3<int32_t>(int32_t(x), int32_t(y), int32_t(z)); }
    Vector3<uint32_t> toUint32() const { return Vector3<uint32_t>(uint32_t(x), uint32_t(y), uint32_t(z)); }
    Vector3<int64_t> toInt64() const { return Vector3<int64_t>(int64_t(x), int64_t(y), int64_t(z)); }
    Vector3<uint64_t> toUint64() const { return Vector3<uint64_t>(uint64_t(x), uint64_t(y), uint64_t(z)); }
    Vector3<float> toFloat() const { return Vector3<float>(float(x), float(y), float(z)); }
    Vector3<double> toDouble() const { return Vector3<double>(double(x), double(y), double(z)); }

    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
