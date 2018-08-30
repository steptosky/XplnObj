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
#include "sts/utilities/Compare.h"
#include "Vector3.h"

namespace sts_t {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details This class implements a 4x3 3D transformation matrix object. Methods are provided to zero the matrix,
 * set it to the identity, compute its inverse, apply incremental translation, rotation and scaling, and build new X, Y and Z rotation matrices.
 * Operators are provided for matrix addition, subtraction, and multiplication.
 * \remark
 * Coordinate axis rotation matrices are of the form \n
 * RX = \n
 * 1  0  0  \n
 * 0  c -s  \n
 * 0  s  c  \n
 * where t > 0 indicates a counterclockwise rotation in the yz-plane  \n
 * RY =  \n
 * c  0  s  \n
 * 0  1  0  \n
 * -s  0  c  \n
 * where t > 0 indicates a counterclockwise rotation in the zx-plane  \n
 * RZ =   \n
 * c -s  0  \n
 * s  c  0  \n
 * 0  0  1  \n
 * where t > 0 indicates a counterclockwise rotation in the xy-plane.  \n
 * 
 * Coordinate translation  \n
 * 1     0     0  \n
 * 0     1     0  \n
 * 0     0     1  \n
 * x     y     x  \n
 * where xyz is translation
 */

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<class T>
class TMatrix3 {
public:

    static_assert(std::numeric_limits<T>::is_specialized,
        "The class can use only arithmetic types");

    typedef T value_type;
    typedef Vector3<value_type> Vec3;

    //-------------------------------------------------------------------------

    enum eFlag {
        POS_IDENT = 1,
        ROT_IDENT = 2,
        SCL_IDENT = 4,
        MAT_IDENT = POS_IDENT | ROT_IDENT | SCL_IDENT,
    };

    //-------------------------------------------------------------------------
    // INIT

    TMatrix3();
    explicit TMatrix3(bool inIdentity);
    explicit TMatrix3(value_type * inArray /*4x3*/, size_t inCount = 12); // size 12, row major
    TMatrix3(
        value_type m00, value_type m01, value_type m02,
        value_type m10, value_type m11, value_type m12,
        value_type m20, value_type m21, value_type m22,
        value_type m30, value_type m31, value_type m32);
    ~TMatrix3();

    //-------------------------------------------------------------------------
    // OPERATORS

    bool operator==(const TMatrix3 & inTm) const;
    bool operator!=(const TMatrix3 & inTm) const;
    value_type & operator()(size_t row, size_t column);
    const value_type & operator()(size_t row, size_t column) const;
    const value_type & operator[](size_t i) const;
    value_type & operator[](size_t i);

    TMatrix3 & operator-=(const TMatrix3 & inTm);
    TMatrix3 & operator+=(const TMatrix3 & inTm);
    TMatrix3 & operator*=(const TMatrix3 & inTm);
    TMatrix3 & operator*=(value_type scalar);

    TMatrix3 operator+(const TMatrix3 & inTm) const;
    TMatrix3 operator-(const TMatrix3 & inTm) const;
    TMatrix3 operator*(const TMatrix3 & inTm) const;
    TMatrix3 operator*(value_type scalar) const;

    //-------------------------------------------------------------------------
    // RAW DATA

    value_type * rawData();
    const value_type * rawData() const;

    //-------------------------------------------------------------------------
    // FLAGS

    void __addIdentFlags(uint32_t f);
    void __clearIdentFlag(uint32_t f);

    bool isIdentity(uint32_t f) const;
    bool isIdentity() const;
    bool isRotating() const;
    bool isScaling() const;
    bool isTranslating() const;
    int identFlags() const;
    void validateFlags();

    //-------------------------------------------------------------------------
    // ACTIONS

    void setRotate(const Vec3 & inAxis, value_type inAngleRadians);
    void setTranslate(const Vec3 & inVec);
    void setTranslate(value_type inX, value_type inY, value_type inZ);

    Vec3 translation() const;
    value_type translationX() const;
    value_type translationY() const;
    value_type translationZ() const;

    // global (multiplying on the RIGHT by the transform)
    void translate(const Vec3 & inVec);
    void translate(value_type inX, value_type inY, value_type inZ);
    void rotateX(value_type inAngleRadians);
    void rotateY(value_type inAngleRadians);
    void rotateZ(value_type inAngleRadians);
    void scale(const Vec3 & s);
    void scale(value_type inX, value_type inY, value_type inZ);

    // local (multiplying on the LEFT by the transform)
    void preTranslate(const Vec3 & p);
    void preTranslate(value_type inX, value_type inY, value_type inZ);
    void preRotateX(value_type inAngleRadians);
    void preRotateY(value_type inAngleRadians);
    void preRotateZ(value_type inAngleRadians);
    void preScale(const Vec3 & s);
    void preScale(value_type inX, value_type inY, value_type inZ);

    // common
    TMatrix3 inversed() const;
    void orthogonalize(int maxIteration = 16);

    //-------------------------------------------------------------------------
    // STATE

    void setTranslateIdentity();
    void setRotateIdentity(bool leaveScale = false);
    void setScaleIdentity();
    void setIdentity();
    void setZero();

    bool isParity() const;
    bool isEqual(const TMatrix3 & M, value_type epsilon) const;

    //-------------------------------------------------------------------------

    Vec3 mapPoint(const Vec3 & inPoint) const;
    Vec3 mapVector(const Vec3 & inVec) const;
    void mapPoints(Vec3 * inOutPoints, size_t inCount) const;
    void mapVectors(Vec3 * inOutVec, size_t inCount) const;

    //-------------------------------------------------------------------------
    // DATA ACCESSORS

    void set(
        value_type m00, value_type m01, value_type m02,
        value_type m10, value_type m11, value_type m12,
        value_type m20, value_type m21, value_type m22,
        value_type m30, value_type m31, value_type m32);

    //-------------------------------------------------------------------------

private:

    value_type mData[4][3];
    uint32_t mFlags;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

#include "TMatrix3.inl"

}
