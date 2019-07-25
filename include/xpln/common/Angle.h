#pragma once

/*
**  Copyright(C) 2019, StepToSky
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

#include <limits>
#include <cmath>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<typename Real>
class DegreesT;

template<typename Real>
class RadiansT;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<typename T>
constexpr T radians(T deg) {
    static_assert(std::numeric_limits<T>::is_iec559, "'radians' only accept floating-point input");
    return deg * static_cast<T>(0.01745329251994329576923690768489);
}

template<typename T>
constexpr T degrees(const T rad) {
    static_assert(std::numeric_limits<T>::is_iec559, "'degrees' only accept floating-point input");
    return rad * static_cast<T>(57.295779513082320876798154814105);
}

template<typename T>
constexpr RadiansT<T> radians(DegreesT<T> deg) {
    return RadiansT<T>(radians(deg.value()));
}

template<typename T>
constexpr DegreesT<T> degrees(RadiansT<T> rad) {
    return DegreesT<T>(degrees(rad.value()));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<typename T>
class DegreesT {
    static_assert(std::numeric_limits<T>::is_iec559, "'Degrees' accept floating-point only");
public:

    typedef T value_type;

    //-------------------------------------------

    explicit DegreesT() = default;

    constexpr explicit DegreesT(const T val)
        : mVal(val) {}

    constexpr DegreesT(const DegreesT &) = default;
    constexpr DegreesT & operator=(const DegreesT &) = default;

    //-------------------------------------------

    constexpr bool operator==(const DegreesT & r) const { return mVal == r.mVal; }
    constexpr bool operator!=(const DegreesT & r) const { return mVal != r.mVal; }

    constexpr bool operator>(const DegreesT & r) const { return mVal > r.mVal; }
    constexpr bool operator<(const DegreesT & r) const { return mVal < r.mVal; }
    constexpr bool operator>=(const DegreesT & r) const { return mVal >= r.mVal; }
    constexpr bool operator<=(const DegreesT & r) const { return mVal <= r.mVal; }

    constexpr bool compare(const DegreesT & r, const T epsilon = std::numeric_limits<T>::epsilon()) const {
        return std::fabs(mVal - r.mVal) <= epsilon;
    }

    //-------------------------------------------

    constexpr DegreesT & operator+=(const DegreesT & r) const {
        mVal += r.mVal;
        return *this;
    }

    constexpr DegreesT & operator-=(const DegreesT & r) const {
        mVal -= r.mVal;
        return *this;
    }

    constexpr DegreesT & operator*=(const DegreesT & r) const {
        mVal *= r.mVal;
        return *this;
    }

    constexpr DegreesT & operator/=(const DegreesT & r) const {
        mVal /= r.mVal;
        return *this;
    }

    //-------------------------------------------

    constexpr DegreesT operator+(const DegreesT & r) const { return DegreesT(mVal + r.mVal); }
    constexpr DegreesT operator-(const DegreesT & r) const { return DegreesT(mVal - r.mVal); }
    constexpr DegreesT operator*(const DegreesT & r) const { return DegreesT(mVal * r.mVal); }
    constexpr DegreesT operator/(const DegreesT & r) const { return DegreesT(mVal / r.mVal); }

    //-------------------------------------------

    constexpr void set(const T val) { mVal = val; }
    constexpr void setDeg(const T val) { mVal = val; }
    constexpr void setRad(const T rad) { mVal = degrees(rad); }
    constexpr void setRad(const RadiansT<T> rad) { mVal = degrees(rad.value()); }
    constexpr T value() const { return mVal; }

    constexpr static DegreesT fromRad(const T rad) { return DegreesT(degrees(rad)); }
    constexpr static DegreesT fromRad(const RadiansT<T> rad) { return degrees(rad); }

    constexpr RadiansT<T> rad() { return RadiansT<T>(radians(mVal)); }

    //-------------------------------------------

private:
    T mVal = T(0.0);
};

template<typename T>
class RadiansT {
    static_assert(std::numeric_limits<T>::is_iec559, "'Radians' accept floating-point only");
public:

    typedef T value_type;

    //-------------------------------------------

    explicit RadiansT() = default;

    constexpr explicit RadiansT(const T val)
        : mVal(val) {}

    constexpr RadiansT(const RadiansT &) = default;
    constexpr RadiansT & operator=(const RadiansT &) = default;

    //-------------------------------------------

    constexpr bool operator==(const RadiansT & r) const { return mVal == r.mVal; }
    constexpr bool operator!=(const RadiansT & r) const { return mVal != r.mVal; }

    constexpr bool operator>(const RadiansT & r) const { return mVal > r.mVal; }
    constexpr bool operator<(const RadiansT & r) const { return mVal < r.mVal; }
    constexpr bool operator>=(const RadiansT & r) const { return mVal >= r.mVal; }
    constexpr bool operator<=(const RadiansT & r) const { return mVal <= r.mVal; }

    constexpr bool compare(const RadiansT & r, const T epsilon = std::numeric_limits<T>::epsilon()) const {
        return std::fabs(mVal - r.mVal) <= epsilon;
    }

    //-------------------------------------------

    constexpr RadiansT & operator+=(const RadiansT & r) const {
        mVal += r.mVal;
        return *this;
    }

    constexpr RadiansT & operator-=(const RadiansT & r) const {
        mVal -= r.mVal;
        return *this;
    }

    constexpr RadiansT & operator*=(const RadiansT & r) const {
        mVal *= r.mVal;
        return *this;
    }

    constexpr RadiansT & operator/=(const RadiansT & r) const {
        mVal /= r.mVal;
        return *this;
    }

    //-------------------------------------------

    constexpr RadiansT operator+(const RadiansT & r) const { return RadiansT(mVal + r.mVal); }
    constexpr RadiansT operator-(const RadiansT & r) const { return RadiansT(mVal - r.mVal); }
    constexpr RadiansT operator*(const RadiansT & r) const { return RadiansT(mVal * r.mVal); }
    constexpr RadiansT operator/(const RadiansT & r) const { return RadiansT(mVal / r.mVal); }

    //-------------------------------------------

    constexpr void set(const T val) { mVal = val; }
    constexpr void setRad(const T val) { mVal = val; }
    constexpr void setDeg(const T deg) { mVal = radians(deg); }
    constexpr void setDeg(const DegreesT<T> deg) { mVal = radians(deg.value()); }
    constexpr T value() const { return mVal; }

    constexpr static RadiansT fromDeg(const T deg) { return RadiansT(radians(deg)); }
    constexpr static RadiansT fromDeg(const DegreesT<T> deg) { return radians(deg); }

    constexpr DegreesT<T> deg() { return DegreesT<T>(degrees(mVal)); }

    //-------------------------------------------

private:
    T mVal = T(0.0);
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

using Degrees = DegreesT<float>;
using Radians = RadiansT<float>;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
