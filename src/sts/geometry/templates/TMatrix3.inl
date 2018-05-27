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

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Constructor default
 */
template<class value_type>
TMatrix3<value_type>::TMatrix3()
    : TMatrix3(true) {}

/*!
 * \details Constructor init
 * \param [in] inIdentity true for identity , false for zero
 */
template<class value_type>
TMatrix3<value_type>::TMatrix3(bool inIdentity) {
    inIdentity ? setIdentity() : setZero();
}

/*!
 * \details Constructor init from 'value_type *array'
 * \warning Array size must be minimum 4x3 (12) cells. Row is major
 * \remark TMatrix3::validateFlags will be called automaticly
 * \param [in] inArray pointer to array
 * \param [in] inCount array size
 */
template<class value_type>
TMatrix3<value_type>::TMatrix3(value_type * inArray, size_t inCount) {
    assert(inArray);
    assert(inCount != 0);
    assert(inCount <= 12);
    memcpy(mData, inArray, sizeof(value_type) * inCount);
    validateFlags();
}

/*!
 * \details Constructor init cell by cell
 * \remark TMatrix3::validateFlags will be called automaticly
 */
template<class value_type>
TMatrix3<value_type>::TMatrix3(
    value_type m00, value_type m01, value_type m02,
    value_type m10, value_type m11, value_type m12,
    value_type m20, value_type m21, value_type m22,
    value_type m30, value_type m31, value_type m32)
    : mFlags(0) {
    mData[0][0] = m00, mData[0][1] = m01, mData[0][2] = m02;
    mData[1][0] = m10, mData[1][1] = m11, mData[1][2] = m12;
    mData[2][0] = m20, mData[2][1] = m21, mData[2][2] = m22;
    mData[3][0] = m30, mData[3][1] = m31, mData[3][2] = m32;
    validateFlags();
}

/*!
 * \details Destructor
 */
template<class value_type>
TMatrix3<value_type>::~TMatrix3() {}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Gets const reference to a cell.
 * \param [in] i cell index, maximum value is 11 (12 cells).
 * \return \code  return reinterpret_cast<const value_type*>(mData)[i]; \endcode
 */
template<class value_type>
const value_type & TMatrix3<value_type>::operator[](size_t i) const {
    assert(i < 12);
    return reinterpret_cast<const value_type*>(mData)[i];
}

/*!
 * \details Gets reference to a cell.
 * \param [in] i cell index, maximum value is 11 (12 cells).
 * \return \code  return reinterpret_cast<const value_type*>(mData)[i]; \endcode
 */
template<class value_type>
value_type & TMatrix3<value_type>::operator[](size_t i) {
    assert(i < 12);
    return reinterpret_cast<value_type*>(mData)[i];
}

/*!
 * \details Gets const reference to a cell, by the row and column. \n
 * 00  01  02  \n
 * 10  11  12  \n
 * 20  21  22  \n
 * \param [in] row
 * \param [in] column
 * \return \code return mData[row][column]; \endcode
 */
template<class value_type>
const value_type & TMatrix3<value_type>::operator()(size_t row, size_t column) const {
    assert(row < 4 && column < 3);
    return mData[row][column];
}

/*!
 * \details Gets const reference to a cell, by the row and column. \n
 * 00  01  02  \n
 * 10  11  12  \n
 * 20  21  22  \n
 * \param [in] row
 * \param [in] column
 * \return \code return mData[row][column]; \endcode
 */
template<class value_type>
value_type & TMatrix3<value_type>::operator()(size_t row, size_t column) {
    assert(row < 4 && column < 3);
    return mData[row][column];
}

/*!
 * \details Compares the elements of this matrix and the one specified element by element for equality within the epsilon.
 * \return True if they are 'equal', otherwise false.
 */
template<class value_type>
bool TMatrix3<value_type>::operator==(const TMatrix3<value_type> & inMtx) const {
    return (
        sts::isEqual(mData[0][0], inMtx.mData[0][0]) &&
        sts::isEqual(mData[0][1], inMtx.mData[0][1]) &&
        sts::isEqual(mData[0][2], inMtx.mData[0][2]) &&

        sts::isEqual(mData[1][0], inMtx.mData[1][0]) &&
        sts::isEqual(mData[1][1], inMtx.mData[1][1]) &&
        sts::isEqual(mData[1][2], inMtx.mData[1][2]) &&

        sts::isEqual(mData[2][0], inMtx.mData[2][0]) &&
        sts::isEqual(mData[2][1], inMtx.mData[2][1]) &&
        sts::isEqual(mData[2][2], inMtx.mData[2][2]) &&

        sts::isEqual(mData[3][0], inMtx.mData[3][0]) &&
        sts::isEqual(mData[3][1], inMtx.mData[3][1]) &&
        sts::isEqual(mData[3][2], inMtx.mData[3][2]));
}

/*!
 * \details Opposite '=='
 * \return True if they are not 'equal', otherwise false.
 */
template<class value_type>
bool TMatrix3<value_type>::operator!=(const TMatrix3<value_type> & inMtx) const {
    return !this->operator==(inMtx);
}

/*!
 * \details Subtracts a TMatrix3 from this TMatrix3.
 * \return  *this
 */
template<class value_type>
TMatrix3<value_type> & TMatrix3<value_type>::operator-=(const TMatrix3<value_type> & inMtx) {
    mData[0][0] -= inMtx.mData[0][0], mData[0][1] -= inMtx.mData[0][1], mData[0][2] -= inMtx.mData[0][2];
    mData[1][0] -= inMtx.mData[1][0], mData[1][1] -= inMtx.mData[1][1], mData[1][2] -= inMtx.mData[1][2];
    mData[2][0] -= inMtx.mData[2][0], mData[2][1] -= inMtx.mData[2][1], mData[2][2] -= inMtx.mData[2][2];
    mData[3][0] -= inMtx.mData[3][0], mData[3][1] -= inMtx.mData[3][1], mData[3][2] -= inMtx.mData[3][2];
    __clearIdentFlag(MAT_IDENT);
    return *this;
}

/*!
 * \details Adds a TMatrix3 to this TMatrix3.
 * \return  *this
 */
template<class value_type>
TMatrix3<value_type> & TMatrix3<value_type>::operator+=(const TMatrix3<value_type> & inMtx) {
    mData[0][0] += inMtx.mData[0][0], mData[0][1] += inMtx.mData[0][1], mData[0][2] += inMtx.mData[0][2];
    mData[1][0] += inMtx.mData[1][0], mData[1][1] += inMtx.mData[1][1], mData[1][2] += inMtx.mData[1][2];
    mData[2][0] += inMtx.mData[2][0], mData[2][1] += inMtx.mData[2][1], mData[2][2] += inMtx.mData[2][2];
    mData[3][0] += inMtx.mData[3][0], mData[3][1] += inMtx.mData[3][1], mData[3][2] += inMtx.mData[3][2];
    __clearIdentFlag(MAT_IDENT);
    return *this;
}

/*!
 * \details Multiplies this Matrix3 by the specified Matrix3
 * \remark this = this * M.
 * \return  *this
 */
template<class value_type>
TMatrix3<value_type> & TMatrix3<value_type>::operator*=(const TMatrix3<value_type> & inMtx) {
    if (!inMtx.isIdentity()) {
        (isIdentity() == false) ? *this = this->operator*(inMtx) : *this = inMtx;
    }
    return *this;
}

/*!
 * \details Multiplies this Matrix3 by the specified scalar
 * \remark this = this * M.
 * \return  *this
 */
template<class value_type>
TMatrix3<value_type> & TMatrix3<value_type>::operator*=(value_type scalar) {
    mData[0][0] *= scalar, mData[0][1] *= scalar, mData[0][2] *= scalar;
    mData[1][0] *= scalar, mData[1][1] *= scalar, mData[1][2] *= scalar;
    mData[2][0] *= scalar, mData[2][1] *= scalar, mData[2][2] *= scalar;
    mData[3][0] *= scalar, mData[3][1] *= scalar, mData[3][2] *= scalar;
    __clearIdentFlag(MAT_IDENT);
    return *this;
}

/*!
 * \details Performs matrix multiplication.
 * \return Result matrix
 */
template<class value_type>
TMatrix3<value_type> TMatrix3<value_type>::operator*(const TMatrix3<value_type> & inTm) const {
    if (inTm.isIdentity()) {
        return *this;
    }
    if (isIdentity()) {
        return inTm;
    }
    TMatrix3 outTm(
                   inTm.mData[0][0] * mData[0][0] + inTm.mData[1][0] * mData[0][1] + inTm.mData[2][0] * mData[0][2], // 00
                   inTm.mData[0][1] * mData[0][0] + inTm.mData[1][1] * mData[0][1] + inTm.mData[2][1] * mData[0][2], // 01
                   inTm.mData[0][2] * mData[0][0] + inTm.mData[1][2] * mData[0][1] + inTm.mData[2][2] * mData[0][2], // 02
                   inTm.mData[0][0] * mData[1][0] + inTm.mData[1][0] * mData[1][1] + inTm.mData[2][0] * mData[1][2], // 10
                   inTm.mData[0][1] * mData[1][0] + inTm.mData[1][1] * mData[1][1] + inTm.mData[2][1] * mData[1][2], // 11
                   inTm.mData[0][2] * mData[1][0] + inTm.mData[1][2] * mData[1][1] + inTm.mData[2][2] * mData[1][2], // 12
                   inTm.mData[0][0] * mData[2][0] + inTm.mData[1][0] * mData[2][1] + inTm.mData[2][0] * mData[2][2], // 20
                   inTm.mData[0][1] * mData[2][0] + inTm.mData[1][1] * mData[2][1] + inTm.mData[2][1] * mData[2][2], // 21
                   inTm.mData[0][2] * mData[2][0] + inTm.mData[1][2] * mData[2][1] + inTm.mData[2][2] * mData[2][2], // 22
                   inTm.mData[0][0] * mData[3][0] + inTm.mData[1][0] * mData[3][1] + inTm.mData[2][0] * mData[3][2] + inTm.mData[3][0],
                   inTm.mData[0][1] * mData[3][0] + inTm.mData[1][1] * mData[3][1] + inTm.mData[2][1] * mData[3][2] + inTm.mData[3][1],
                   inTm.mData[0][2] * mData[3][0] + inTm.mData[1][2] * mData[3][1] + inTm.mData[2][2] * mData[3][2] + inTm.mData[3][2]);

    if (isIdentity(SCL_IDENT) && inTm.isIdentity(SCL_IDENT)) {
        outTm.__addIdentFlags(SCL_IDENT);
    }
    return outTm;
}

/*!
 * \details Performs matrix addition.
 * \return Result matrix
 */
template<class value_type>
TMatrix3<value_type> TMatrix3<value_type>::operator+(const TMatrix3<value_type> & inMtx) const {
    return TMatrix3(*this) += inMtx;
}

/*!
 * \details Performs matrix subtraction.
 * \return Result matrix
 */
template<class value_type>
TMatrix3<value_type> TMatrix3<value_type>::operator-(const TMatrix3<value_type> & inMtx) const {
    return TMatrix3<value_type>(*this) -= inMtx;
}

/*!
 * \details Performs matrix multiplication by the specified scalar.
 * \return Result matrix
 */
template<class value_type>
TMatrix3<value_type> TMatrix3<value_type>::operator*(value_type scalar) const {
    return TMatrix3<value_type>(*this) *= scalar;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Compares the elements of this matrix and the one specified element by element for equality within the specified tolerance epsilon.
 * \return True if they are equaled, otherwise false.
 */
template<class value_type>
bool TMatrix3<value_type>::isEqual(const TMatrix3<value_type> & inMtx, value_type epsilon) const {
    return (
        sts::isEqual(mData[0][0], inMtx.mData[0][0], epsilon) &&
        sts::isEqual(mData[0][1], inMtx.mData[0][1], epsilon) &&
        sts::isEqual(mData[0][2], inMtx.mData[0][2], epsilon) &&

        sts::isEqual(mData[1][0], inMtx.mData[1][0], epsilon) &&
        sts::isEqual(mData[1][1], inMtx.mData[1][1], epsilon) &&
        sts::isEqual(mData[1][2], inMtx.mData[1][2], epsilon) &&

        sts::isEqual(mData[2][0], inMtx.mData[2][0], epsilon) &&
        sts::isEqual(mData[2][1], inMtx.mData[2][1], epsilon) &&
        sts::isEqual(mData[2][2], inMtx.mData[2][2], epsilon) &&

        sts::isEqual(mData[3][0], inMtx.mData[3][0], epsilon) &&
        sts::isEqual(mData[3][1], inMtx.mData[3][1], epsilon) &&
        sts::isEqual(mData[3][2], inMtx.mData[3][2], epsilon)
    );
}

/*!
 * \details Sets this matrix to the Identity Matrix.
 */
template<class value_type>
void TMatrix3<value_type>::setIdentity() {
    mData[0][0] = value_type(1);
    mData[0][1] = value_type(0);
    mData[0][2] = value_type(0);
    mData[1][0] = value_type(0);
    mData[1][1] = value_type(1);
    mData[1][2] = value_type(0);
    mData[2][0] = value_type(0);
    mData[2][1] = value_type(0);
    mData[2][2] = value_type(1);
    mData[3][0] = value_type(0);
    mData[3][1] = value_type(0);
    mData[3][2] = value_type(0);
    mFlags = 0;
    __addIdentFlags(MAT_IDENT);
}

/*!
 * \details Sets all elements of the matrix to 0.0
 */
template<class value_type>
void TMatrix3<value_type>::setZero() {
    mData[0][0] = value_type(0);
    mData[0][1] = value_type(0);
    mData[0][2] = value_type(0);
    mData[1][0] = value_type(0);
    mData[1][1] = value_type(0);
    mData[1][2] = value_type(0);
    mData[2][0] = value_type(0);
    mData[2][1] = value_type(0);
    mData[2][2] = value_type(0);
    mData[3][0] = value_type(0);
    mData[3][1] = value_type(0);
    mData[3][2] = value_type(0);
    mFlags = 0;
    __addIdentFlags(POS_IDENT);
}

/*!
 * \details Inverts this matrix.
 * \return Result matrix
 */
template<class value_type>
TMatrix3<value_type> TMatrix3<value_type>::inversed() const {
    TMatrix3<value_type> outMtx(true);
    if (!isIdentity(MAT_IDENT)) {
        if (isIdentity(SCL_IDENT)) {
            outMtx.mData[0][0] = mData[0][0];
            outMtx.mData[0][1] = mData[1][0];
            outMtx.mData[0][2] = mData[2][0];
            outMtx.mData[1][0] = mData[0][1];
            outMtx.mData[1][1] = mData[1][1];
            outMtx.mData[1][2] = mData[2][1];
            outMtx.mData[2][0] = mData[0][2];
            outMtx.mData[2][1] = mData[1][2];
            outMtx.mData[2][2] = mData[2][2];
        }
        else {
            outMtx.mData[0][0] = mData[1][1] * mData[2][2] - mData[1][2] * mData[2][1];
            outMtx.mData[0][1] = mData[0][2] * mData[2][1] - mData[0][1] * mData[2][2];
            outMtx.mData[0][2] = mData[0][1] * mData[1][2] - mData[0][2] * mData[1][1];
            outMtx.mData[1][0] = mData[2][0] * mData[1][2] - mData[1][0] * mData[2][2];
            outMtx.mData[1][1] = mData[2][2] * mData[0][0] - mData[0][2] * mData[2][0];
            outMtx.mData[1][2] = mData[0][2] * mData[1][0] - mData[1][2] * mData[0][0];
            outMtx.mData[2][0] = mData[1][0] * mData[2][1] - mData[2][0] * mData[1][1];
            outMtx.mData[2][1] = mData[0][1] * mData[2][0] - mData[2][1] * mData[0][0];
            outMtx.mData[2][2] = mData[1][1] * mData[0][0] - mData[0][1] * mData[1][0];

            value_type factor = mData[1][0] * outMtx.mData[0][1] + mData[2][0] * outMtx.mData[0][2] + mData[0][0] * outMtx.mData[0][0];
            factor = sts::isEqual(factor, value_type(0)) ? value_type(1.0e7) : value_type(1) / factor;

            outMtx.mData[0][0] *= factor;
            outMtx.mData[0][1] *= factor;
            outMtx.mData[0][2] *= factor;
            outMtx.mData[1][0] *= factor;
            outMtx.mData[1][1] *= factor;
            outMtx.mData[1][2] *= factor;
            outMtx.mData[2][0] *= factor;
            outMtx.mData[2][2] *= factor;
            outMtx.mData[2][1] *= factor;
        }

        outMtx.mData[3][0] = -(mData[3][0] * outMtx.mData[0][0] + mData[3][1] * outMtx.mData[1][0] + mData[3][2] * outMtx.mData[2][0]);
        outMtx.mData[3][1] = -(mData[3][0] * outMtx.mData[0][1] + mData[3][1] * outMtx.mData[1][1] + mData[3][2] * outMtx.mData[2][1]);
        outMtx.mData[3][2] = -(mData[3][0] * outMtx.mData[0][2] + mData[3][1] * outMtx.mData[1][2] + mData[3][2] * outMtx.mData[2][2]);
        outMtx.mFlags = mFlags;
    }
    return outMtx;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details This method zeros the translation portion of this matrix.
 */
template<class value_type>
void TMatrix3<value_type>::setTranslateIdentity() {
    mData[3][0] = 0.0;
    mData[3][1] = 0.0;
    mData[3][2] = 0.0;
    __addIdentFlags(POS_IDENT);
}

/*!
 * \details This method makes rotation portion to identity
 * \warning If the matrix was sheared (skewed) then this method is not able to leave correct scale component.
 * \param [in] leaveScale if true then method will try to leave scale and clear any rotation data.
 */
template<class value_type>
void TMatrix3<value_type>::setRotateIdentity(bool leaveScale) {
    if (isIdentity(ROT_IDENT)) {
        return;
    }
    if (leaveScale) {
        if (!isIdentity(SCL_IDENT)) {
            mData[0][0] = sqrt(mData[0][0] * mData[0][0] + mData[0][1] * mData[0][1] + mData[0][2] * mData[0][2]);
            mData[1][1] = sqrt(mData[1][0] * mData[1][0] + mData[1][1] * mData[1][1] + mData[1][2] * mData[1][2]);
            mData[2][2] = sqrt(mData[2][0] * mData[2][0] + mData[2][1] * mData[2][1] + mData[2][2] * mData[2][2]);
            mData[0][1] = mData[0][2] = 0.0;
            mData[1][0] = mData[1][2] = 0.0;
            mData[2][0] = mData[2][1] = 0.0;
            if (sts::isEqual(mData[0][0], value_type(1)) && sts::isEqual(mData[1][1], value_type(1)) && sts::isEqual(mData[2][2], value_type(1))) {
                __addIdentFlags(ROT_IDENT | SCL_IDENT);
            }
            else {
                __addIdentFlags(ROT_IDENT);
            }
        }
    }
    else {
        mData[0][0] = 1.0;
        mData[0][1] = 0.0;
        mData[0][2] = value_type(0);
        mData[1][0] = 0.0;
        mData[1][1] = 1.0;
        mData[1][2] = value_type(0);
        mData[2][0] = 0.0;
        mData[2][1] = 0.0;
        mData[2][2] = value_type(1);
        __addIdentFlags(ROT_IDENT | SCL_IDENT);
    }
}

/*!
 * \details The method zeros the scale portion of this matrix without orthogonalization.
 * \warning If the matrix was sheared (skewed) then the method is not able to remove scale component completely.
 * Use Orthogonalize() method first for removing the scale.
 * \warning This method will change the matrix internal values anyway.
 * Use isScaling() method to check if scaleIdentity() method was enough to make the matrix to be orthogonal.
 */
template<class value_type>
void TMatrix3<value_type>::setScaleIdentity() {
    if (isIdentity(SCL_IDENT)) {
        return;
    }
    value_type factor = value_type(1);
    value_type len = sqrt(mData[0][0] * mData[0][0] + mData[0][1] * mData[0][1] + mData[0][2] * mData[0][2]);
    if (!sts::isEqual(len, value_type(0))) {
        factor = value_type(1) / len;
        mData[0][0] *= factor;
        mData[0][1] *= factor;
        mData[0][2] *= factor;
    }

    len = sqrt(mData[1][0] * mData[1][0] + mData[1][1] * mData[1][1] + mData[1][2] * mData[1][2]);
    if (!sts::isEqual(len, value_type(0))) {
        factor = value_type(1) / len;
        mData[1][0] *= factor;
        mData[1][1] *= factor;
        mData[1][2] *= factor;
    }

    len = sqrt(mData[2][0] * mData[2][0] + mData[2][1] * mData[2][1] + mData[2][2] * mData[2][2]);
    if (!sts::isEqual(len, value_type(0))) {
        factor = value_type(1) / len;
        mData[2][0] *= factor;
        mData[2][1] *= factor;
        mData[2][2] *= factor;
    }

    if (!sts::isEqual((mData[1][1] * mData[0][1]) + (mData[1][2] * mData[0][2]) + (mData[1][0] * mData[0][0]), value_type(0)))
        return;
    if (!sts::isEqual((mData[0][2] * mData[2][2]) + (mData[0][1] * mData[2][1]) + (mData[0][0] * mData[2][0]), value_type(0)))
        return;
    if (!sts::isEqual((mData[1][2] * mData[2][2]) + (mData[1][1] * mData[2][1]) + (mData[1][0] * mData[2][0]), value_type(0)))
        return;

    Vec3 res = Vec3(mData[0][0], mData[0][1], mData[0][2]).crossProduct(Vec3(mData[1][0], mData[1][1], mData[1][2]));
    if (((mData[2][0] * res.x) + (mData[2][1] * res.y) + (mData[2][2] * res.z)) > value_type(0.5)) {
        __addIdentFlags(SCL_IDENT);
    }
}

//------------------------------------------------------------------------

/*!
 * \details Applies an incremental translation transformation to this matrix.
 * \param [in] inVec vector 3
 */
template<class value_type>
void TMatrix3<value_type>::translate(const Vector3<value_type> & inVec) {
    translate(inVec.x, inVec.y, inVec.z);
}

/*!
 * \details Applies an incremental translation transformation to this matrix.
 * \param [in] inX
 * \param [in] inY
 * \param [in] inZ
 */
template<class value_type>
void TMatrix3<value_type>::translate(value_type inX, value_type inY, value_type inZ) {
    mData[3][0] += inX;
    mData[3][1] += inY;
    mData[3][2] += inZ;
    __clearIdentFlag(POS_IDENT);
}

//-------------------------------------------------------------------------

/*!
 * \details Sets actual translation transformation of this matrix.
 * \param [in] inVec vector 3
 */
template<class value_type>
void TMatrix3<value_type>::setTranslate(const sts_t::Vector3<value_type> & inVec) {
    translation(inVec.x, inVec.y, inVec.z);
}

/*!
 * \details Sets actual translation transformation of this matrix.
 * \param [in] inX
 * \param [in] inY
 * \param [in] inZ
 */
template<class value_type>
void TMatrix3<value_type>::setTranslate(value_type inX, value_type inY, value_type inZ) {
    mData[3][0] = inX;
    mData[3][1] = inY;
    mData[3][2] = inZ;
    __clearIdentFlag(POS_IDENT);
}

/*!
 * \details Gets actual translation transformation of this matrix.
 * \return Vector 3
 */
template<class value_type>
sts_t::Vector3<value_type> TMatrix3<value_type>::translation() const {
    return sts_t::Vector3<value_type>(translationX(),
                                      translationY(),
                                      translationZ());
}

/*!
 * \details Gets X component of the actual translation transformation of this matrix.
 * \return X component
 */
template<class value_type>
value_type TMatrix3<value_type>::translationX() const {
    return mData[3][0];
}

/*!
 * \details Gets Y component of the actual translation transformation of this matrix.
 * \return Y component
 */
template<class value_type>
value_type TMatrix3<value_type>::translationY() const {
    return mData[3][1];
}

/*!
 * \details Gets Z component of the actual translation transformation of this matrix.
 * \return Z component
 */
template<class value_type>
value_type TMatrix3<value_type>::translationZ() const {
    return mData[3][2];
}

//-------------------------------------------------------------------------

/*!
 * \details Apply an incremental X rotation transformation to this matrix.
 * This is equivalent to multiplying on the RIGHT by the transform.
 * \param [in] inAngleRadians angle in radians
 */
template<class value_type>
void TMatrix3<value_type>::rotateX(value_type inAngleRadians) {
    if (sts::isEqual(inAngleRadians, value_type(0))) {
        return;
    }
    value_type sinA = sin(inAngleRadians);
    value_type cosA = cos(inAngleRadians);

    value_type tmpCell1 = mData[0][1];
    value_type tmpCell2 = mData[0][2];
    mData[0][1] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[0][2] = tmpCell2 * cosA + tmpCell1 * sinA;
    tmpCell1 = mData[1][1];
    tmpCell2 = mData[1][2];
    mData[1][1] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[1][2] = tmpCell2 * cosA + tmpCell1 * sinA;
    tmpCell1 = mData[2][1];
    tmpCell2 = mData[2][2];
    mData[2][1] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[2][2] = tmpCell2 * cosA + tmpCell1 * sinA;

    tmpCell1 = mData[3][1];
    tmpCell2 = mData[3][2];
    mData[3][1] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[3][2] = tmpCell2 * cosA + tmpCell1 * sinA;

    __clearIdentFlag(ROT_IDENT);
}

/*!
 * \details Apply an incremental Y rotation transformation to this matrix.
 * This is equivalent to multiplying on the RIGHT by the transform.
 * \param [in] inAngleRadians angle in radians
 */
template<class value_type>
void TMatrix3<value_type>::rotateY(value_type inAngleRadians) {
    if (sts::isEqual(inAngleRadians, value_type(0))) {
        return;
    }
    value_type sinA = sin(inAngleRadians);
    value_type cosA = cos(inAngleRadians);

    value_type tmpCell1 = mData[0][0];
    value_type tmpCell2 = mData[0][2];
    mData[0][0] = tmpCell1 * cosA + tmpCell2 * sinA;
    mData[0][2] = tmpCell2 * cosA - tmpCell1 * sinA;
    tmpCell1 = mData[1][0];
    tmpCell2 = mData[1][2];
    mData[1][0] = tmpCell1 * cosA + tmpCell2 * sinA;
    mData[1][2] = tmpCell2 * cosA - tmpCell1 * sinA;
    tmpCell1 = mData[2][0];
    tmpCell2 = mData[2][2];
    mData[2][0] = tmpCell1 * cosA + tmpCell2 * sinA;
    mData[2][2] = tmpCell2 * cosA - tmpCell1 * sinA;

    tmpCell1 = mData[3][0];
    tmpCell2 = mData[3][2];
    mData[3][0] = tmpCell1 * cosA + tmpCell2 * sinA;
    mData[3][2] = tmpCell2 * cosA - tmpCell1 * sinA;

    __clearIdentFlag(ROT_IDENT);
}

/*!
 * \details Apply an incremental Z rotation transformation to this matrix.
 * This is equivalent to multiplying on the RIGHT by the transform.
 * \param [in] inAngleRadians angle in radians
 */
template<class value_type>
void TMatrix3<value_type>::rotateZ(value_type inAngleRadians) {
    if (sts::isEqual(inAngleRadians, value_type(0))) {
        return;
    }
    value_type sinA = sin(inAngleRadians);
    value_type cosA = cos(inAngleRadians);

    value_type tmpCell1 = mData[0][0];
    value_type tmpCell2 = mData[0][1];
    mData[0][0] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[0][1] = tmpCell2 * cosA + tmpCell1 * sinA;
    tmpCell1 = mData[1][0];
    tmpCell2 = mData[1][1];
    mData[1][0] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[1][1] = tmpCell2 * cosA + tmpCell1 * sinA;
    tmpCell1 = mData[2][0];
    tmpCell2 = mData[2][1];
    mData[2][0] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[2][1] = tmpCell2 * cosA + tmpCell1 * sinA;

    tmpCell1 = mData[3][0];
    tmpCell2 = mData[3][1];
    mData[3][0] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[3][1] = tmpCell2 * cosA + tmpCell1 * sinA;

    __clearIdentFlag(ROT_IDENT);
}

/*!
 * \details Sets the rotation portion of the matrix to the rotation specified by the angle and axis.
 * \warning Scale will be identity too.
 * \param [in] inAxis The normalized axis of rotation.
 * \param [in] inAngleRadians The angle of rotation about the axis in radians.
 */
template<class value_type>
void TMatrix3<value_type>::setRotate(const Vector3<value_type> & inAxis, value_type inAngleRadians) {
    fromAxisAngle(inAxis, inAngleRadians);
}

//-------------------------------------------------------------------------

/*!
 * \details Applies an incremental scaling transformation to this matrix.
 * This is equivalent to multiplying on the RIGHT by the transform.
 * \param [in] s scale
 */
template<class value_type>
void TMatrix3<value_type>::scale(const Vector3<value_type> & inVec) {
    scale(inVec.x, inVec.y, inVec.z);
}

/*!
 * \details Applies an incremental scaling transformation to this matrix.
 * This is equivalent to multiplying on the RIGHT by the transform.
 * \param [in] inX
 * \param [in] inY
 * \param [in] inZ
 */
template<class value_type>
void TMatrix3<value_type>::scale(value_type inX, value_type inY, value_type inZ) {
    if (sts::isEqual(inX, value_type(1)) && sts::isEqual(inY, value_type(1)) && sts::isEqual(inZ, value_type(1))) {
        return;
    }
    mData[0][0] *= inX, mData[0][1] *= inY, mData[0][2] *= inZ;
    mData[1][0] *= inX, mData[1][1] *= inY, mData[1][2] *= inZ;
    mData[2][0] *= inX, mData[2][1] *= inY, mData[2][2] *= inZ;
    mData[3][0] *= inX, mData[3][1] *= inY, mData[3][2] *= inZ;
    __clearIdentFlag(SCL_IDENT);
}

//-------------------------------------------------------------------------

/*!
 * \details Applies an incremental translation transformation to this matrix.
 * This is equivalent to multiplying on the LEFT by the transform.
 * \param [in] p Specifies the translation distance.
 */
template<class value_type>
void TMatrix3<value_type>::preTranslate(const Vector3<value_type> & p) {
    preTranslate(p.setX(), p.setY(), p.setZ());
}

/*!
 * \details Applies an incremental translation transformation to this matrix.
 * This is equivalent to multiplying on the LEFT by the transform.
 * \param [in] inX Specifies the translation distance.
 * \param [in] inY Specifies the translation distance.
 * \param [in] inZ Specifies the translation distance.
 */
template<class value_type>
void TMatrix3<value_type>::preTranslate(value_type inX, value_type inY, value_type inZ) {
    // Temp variables are very important, don't optimize it!
    value_type tmpX = ((mData[0][0] * inX) + (mData[1][0] * inY) + (mData[2][0] * inZ)) + mData[3][0];
    value_type tmpY = ((mData[0][1] * inX) + (mData[1][1] * inY) + (mData[2][1] * inZ)) + mData[3][1];
    value_type tmpZ = ((mData[0][2] * inX) + (mData[1][2] * inY) + (mData[2][2] * inZ)) + mData[3][2];
    mData[3][0] = tmpX;
    mData[3][1] = tmpY;
    mData[3][2] = tmpZ;
    __clearIdentFlag(POS_IDENT);
}

//-------------------------------------------------------------------------

/*!
 * \details Applies an incremental X rotation transformation to this matrix.
 * This is equivalent to multiplying on the LEFT by the transform.
 * \param [in] inAngleRadians Specifies the X rotation in radians.
 */
template<class value_type>
void TMatrix3<value_type>::preRotateX(value_type inAngleRadians) {
    if (sts::isEqual(inAngleRadians, value_type(0))) {
        return;
    }
    value_type sinA = sin(inAngleRadians);
    value_type cosA = cos(inAngleRadians);

    value_type tmpCell1 = mData[1][0];
    value_type tmpCell2 = mData[2][0];
    mData[1][0] = tmpCell2 * sinA + tmpCell1 * cosA;
    mData[2][0] = tmpCell2 * cosA - tmpCell1 * sinA;
    tmpCell1 = mData[1][1];
    tmpCell2 = mData[2][1];
    mData[1][1] = tmpCell2 * sinA + tmpCell1 * cosA;
    mData[2][1] = tmpCell2 * cosA - tmpCell1 * sinA;
    tmpCell1 = mData[1][2];
    tmpCell2 = mData[2][2];
    mData[1][2] = tmpCell2 * sinA + tmpCell1 * cosA;
    mData[2][2] = tmpCell2 * cosA - tmpCell1 * sinA;

    __clearIdentFlag(ROT_IDENT);
}

/*!
 * \details Applies an incremental Y rotation transformation to this matrix.
 * This is equivalent to multiplying on the LEFT by the transform.
 * \param [in] inAngleRadians Specifies the Y rotation in radians.
 */
template<class value_type>
void TMatrix3<value_type>::preRotateY(value_type inAngleRadians) {
    if (sts::isEqual(inAngleRadians, value_type(0))) {
        return;
    }
    value_type sinA = sin(inAngleRadians);
    value_type cosA = cos(inAngleRadians);

    value_type tmpCell1 = mData[0][0];
    value_type tmpCell2 = mData[2][0];
    mData[0][0] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[2][0] = tmpCell1 * sinA + tmpCell2 * cosA;
    tmpCell1 = mData[0][1];
    tmpCell2 = mData[2][1];
    mData[0][1] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[2][1] = tmpCell1 * sinA + tmpCell2 * cosA;
    tmpCell1 = mData[0][2];
    tmpCell2 = mData[2][2];
    mData[0][2] = tmpCell1 * cosA - tmpCell2 * sinA;
    mData[2][2] = tmpCell1 * sinA + tmpCell2 * cosA;

    __clearIdentFlag(ROT_IDENT);
}

/*!
 * \details Applies an incremental Z rotation transformation to this matrix.
 * This is equivalent to multiplying on the LEFT by the transform.
 * \param [in] inAngleRadians Specifies the Z rotation in radians.
 */
template<class value_type>
void TMatrix3<value_type>::preRotateZ(value_type inAngleRadians) {
    if (sts::isEqual(inAngleRadians, value_type(0))) {
        return;
    }
    value_type sinA = sin(inAngleRadians);
    value_type cosA = cos(inAngleRadians);

    value_type tmpCell1 = mData[0][0];
    value_type tmpCell2 = mData[1][0];
    mData[0][0] = tmpCell2 * sinA + tmpCell1 * cosA;
    mData[1][0] = tmpCell2 * cosA - tmpCell1 * sinA;
    tmpCell1 = mData[0][1];
    tmpCell2 = mData[1][1];
    mData[0][1] = tmpCell2 * sinA + tmpCell1 * cosA;
    mData[1][1] = tmpCell2 * cosA - tmpCell1 * sinA;
    tmpCell1 = mData[0][2];
    tmpCell2 = mData[1][2];
    mData[0][2] = tmpCell2 * sinA + tmpCell1 * cosA;
    mData[1][2] = tmpCell2 * cosA - tmpCell1 * sinA;

    __clearIdentFlag(ROT_IDENT);
}

//-------------------------------------------------------------------------

/*!
 * \details Applies an incremental scaling transformation to this matrix.
 * This is equivalent to multiplying on the LEFT by the transform.
 * \param [in] p The scale values.
 */
template<class value_type>
void TMatrix3<value_type>::preScale(const Vector3<value_type> & p) {
    preScale(p.setX(), p.setY(), p.setZ());
}

/*!
 * \details Applies an incremental scaling transformation to this matrix.
 * This is equivalent to multiplying on the LEFT by the transform.
 * \param [in] inX The scale values.
 * \param [in] inY The scale values.
 * \param [in] inZ The scale values.
 */
template<class value_type>
void TMatrix3<value_type>::preScale(value_type inX, value_type inY, value_type inZ) {
    if (sts::isEqual(inX, value_type(1)) && sts::isEqual(inY, value_type(1)) && sts::isEqual(inZ, value_type(1)))
        return;
    // Note: we must not effect for translate!
    mData[0][0] *= inX, mData[0][1] *= inX, mData[0][2] *= inX;
    mData[1][0] *= inY, mData[1][1] *= inY, mData[1][2] *= inY;
    mData[2][0] *= inZ, mData[2][1] *= inZ, mData[2][2] *= inZ;
    __clearIdentFlag(SCL_IDENT);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Transforms a point by this matrix.
 * \remark The point will be transformed by all rows of this matrix.
 * If you want transformation only by rotation part use mapVector().
 * \param [in] inPoint The point to transform by this matrix.
 * \return The specified point transformed by this matrix.
 */
template<class value_type>
sts_t::Vector3<value_type> TMatrix3<value_type>::mapPoint(const sts_t::Vector3<value_type> & inPoint) const {
    if (isIdentity()) {
        return inPoint;
    }
    return sts_t::Vector3<value_type>(
                                      mData[0][0] * inPoint.x + mData[1][0] * inPoint.y + mData[2][0] * inPoint.z + mData[3][0],
                                      mData[0][1] * inPoint.x + mData[1][1] * inPoint.y + mData[2][1] * inPoint.z + mData[3][1],
                                      mData[0][2] * inPoint.x + mData[1][2] * inPoint.y + mData[2][2] * inPoint.z + mData[3][2]);
}

/*!
 * \details Transforms a vector by this matrix.
 * \remark The vector will be transformed only by the 'rotation' rows of this matrix.
 * \param [in] inVec The vector to transform by this matrix.
 * \return The specified vector transformed by this matrix.
 */
template<class value_type>
sts_t::Vector3<value_type> TMatrix3<value_type>::mapVector(const sts_t::Vector3<value_type> & inVec) const {
    if (isIdentity()) {
        return inVec;
    }
    return sts_t::Vector3<value_type>(
                                      mData[0][0] * inVec.x + mData[1][0] * inVec.y + mData[2][0] * inVec.z,
                                      mData[0][1] * inVec.x + mData[1][1] * inVec.y + mData[2][1] * inVec.z,
                                      mData[0][2] * inVec.x + mData[1][2] * inVec.y + mData[2][2] * inVec.z);
}

/*!
 * \details Transforms the specified list of points with this matrix.
 * \remark For more details read mapPoint().
 * \param [in, out] inOutPoints The array of the points to transform with this matrix.
 * \param [in] inCount count the points in the specified points array.
 */
template<class value_type>
void TMatrix3<value_type>::mapPoints(sts_t::Vector3<value_type> * inOutPoints, size_t inCount) const {
    if (inOutPoints == nullptr || inCount == 0 || isIdentity()) {
        return;
    }
    sts_t::Vector3<value_type> tmp;
    for (size_t i = 0; i < inCount; ++i) {
        tmp = *inOutPoints;
        inOutPoints->x = mData[0][0] * tmp.x + mData[1][0] * tmp.y + mData[2][0] * tmp.z + mData[3][0];
        inOutPoints->y = mData[0][1] * tmp.x + mData[1][1] * tmp.y + mData[2][1] * tmp.z + mData[3][1];
        inOutPoints->z = mData[0][2] * tmp.x + mData[1][2] * tmp.y + mData[2][2] * tmp.z + mData[3][2];
        ++inOutPoints;
    }
}

/*!
 * \details Transforms the specified list of vectors with this matrix.
 * \remark For more details read mapVector().
 * \param [in, out] inOutVec The array of the vectors to transform with this matrix.
 * \param [in] inCount count the vectors in the specified vectors array.
 */
template<class value_type>
void TMatrix3<value_type>::mapVectors(sts_t::Vector3<value_type> * inOutVec, size_t inCount) const {
    if (inOutVec == nullptr || inCount == 0 || isIdentity()) {
        return;
    }
    sts_t::Vector3<value_type> tmp;
    for (size_t i = 0; i < inCount; ++i) {
        tmp = *inOutVec;
        inOutVec->x = mData[0][0] * tmp.x + mData[1][0] * tmp.y + mData[2][0] * tmp.z;
        inOutVec->y = mData[0][1] * tmp.x + mData[1][1] * tmp.y + mData[2][1] * tmp.z;
        inOutVec->z = mData[0][2] * tmp.x + mData[1][2] * tmp.y + mData[2][2] * tmp.z;
        ++inOutVec;
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details This is an "unbiased" orthogonalization of this matrix.
 * \warning Scale will be identity
 * The algorithm seems to take a maximum of 11 iterations to converge.
 * An orthogonal matrix has an axis system where each axis is 90 degrees from the others (it's not skewed).
 * \param [in] maxIteration iteration count
 */
template<class value_type>
void TMatrix3<value_type>::orthogonalize(int maxIteration) {
    Vector3<value_type> row0(mData[0][0], mData[0][1], mData[0][2]);
    Vector3<value_type> row1(mData[1][0], mData[1][1], mData[1][2]);
    Vector3<value_type> row2(mData[2][0], mData[2][1], mData[2][2]);
    Vector3<value_type> res;
    int counter = 0;
    do {
        res = row1.crossProduct(row2);
        res.normalize();
        mData[0][0] = res.x;
        mData[0][1] = res.y;
        mData[0][2] = res.z;

        res = row2.crossProduct(row0);
        res.normalize();
        mData[1][0] = res.x;
        mData[1][1] = res.y;
        mData[1][2] = res.z;

        res = row0.crossProduct(row1);
        res.normalize();
        mData[2][0] = res.x;
        mData[2][1] = res.y;
        mData[2][2] = res.z;

        if (sts::isEqual(value_type(
                                    fabs(mData[1][0] * mData[2][0] + mData[1][1] * mData[2][1] + mData[1][2] * mData[2][2]) +
                                    fabs(mData[1][0] * mData[0][0] + mData[1][1] * mData[0][1] + mData[1][2] * mData[0][2]) +
                                    fabs(mData[2][0] * mData[0][0] + mData[2][1] * mData[0][1] + mData[2][2] * mData[0][2])), value_type(0))) {
            break;
        }

        row1.x = (row1.x + mData[1][0]) * value_type(0.5);
        row1.y = (row1.y + mData[1][1]) * value_type(0.5);
        row1.z = (row1.z + mData[1][2]) * value_type(0.5);

        row2.x = (row2.x + mData[2][0]) * value_type(0.5);
        row2.y = (row2.y + mData[2][1]) * value_type(0.5);
        row2.z = (row2.z + mData[2][2]) * value_type(0.5);

        row0.x = (row0.x + mData[0][0]) * value_type(0.5);
        row0.y = (row0.y + mData[0][1]) * value_type(0.5);
        row0.z = (row0.z + mData[0][2]) * value_type(0.5);

        ++counter;
    } while (counter < maxIteration);

    __addIdentFlags(SCL_IDENT);
}

/*!
 * \details Get the 'parity' of the matrix.
 * Scaling one axis of the matrix negatively switches the 'parity'.
 * However if you scale two axis the parity will flip back.
 * Scaling three axis switches the parity again.
 * \remarks It can be used for check to flip normals
 * \return The 'parity' of the matrix
 */
template<class value_type>
bool TMatrix3<value_type>::isParity() const {
    Vec3 res = Vec3(mData[0][0], mData[0][1], mData[0][2]).crossProduct(Vec3(mData[1][0], mData[1][1], mData[1][2]));
    return ((res.x * mData[2][0]) + (res.y * mData[2][1]) + (res.z * mData[2][2]) < value_type(0));
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Initializes the matrix with the cells data passed and validates the matrix flags.
 * \param [in] m00 row 0
 * \param [in] m01 row 0
 * \param [in] m02 row 0
 * \param [in] m10 row 1
 * \param [in] m11 row 1
 * \param [in] m12 row 1
 * \param [in] m20 row 2
 * \param [in] m21 row 2
 * \param [in] m22 row 2
 * \param [in] m30 row 3
 * \param [in] m31 row 3
 * \param [in] m32 row 3
 * \return
 */
template<class value_type>
void TMatrix3<value_type>::set(
    value_type m00, value_type m01, value_type m02,
    value_type m10, value_type m11, value_type m12,
    value_type m20, value_type m21, value_type m22,
    value_type m30, value_type m31, value_type m32) {
    mData[0][0] = m00, mData[0][1] = m01, mData[0][2] = m02;
    mData[1][0] = m10, mData[1][1] = m11, mData[1][2] = m12;
    mData[2][0] = m20, mData[2][1] = m21, mData[2][2] = m22;
    mData[3][0] = m30, mData[3][1] = m31, mData[3][2] = m32;
    validateFlags();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class value_type>
bool TMatrix3<value_type>::isRotating() const {
    return !isIdentity(static_cast<uint32_t>(TMatrix3<value_type>::ROT_IDENT));
}

template<class value_type>
bool TMatrix3<value_type>::isScaling() const {
    return !isIdentity(static_cast<uint32_t>(TMatrix3<value_type>::SCL_IDENT));
}

template<class value_type>
bool TMatrix3<value_type>::isTranslating() const {
    return !isIdentity(static_cast<uint32_t>(TMatrix3<value_type>::POS_IDENT));
}

/*!
 * \warning For internal use only
 */
template<class value_type>
void TMatrix3<value_type>::__addIdentFlags(uint32_t f) {
    mFlags |= f;
}

template<class value_type>
bool TMatrix3<value_type>::isIdentity(uint32_t f) const {
    return ((mFlags & f) == f);
}

template<class value_type>
int TMatrix3<value_type>::identFlags() const {
    return mFlags;
}

/*!
 * \warning For internal use only
 */
template<class value_type>
void TMatrix3<value_type>::__clearIdentFlag(uint32_t f) {
    mFlags &= ~f;
}

template<class value_type>
bool TMatrix3<value_type>::isIdentity() const {
    return ((mFlags & MAT_IDENT) == MAT_IDENT);
}

template<class value_type>
void TMatrix3<value_type>::validateFlags() {
    int flags = MAT_IDENT;
    int i = 0;
    do {
        if (!sts::isEqual(value_type(sqrt(mData[i][0] * mData[i][0] + mData[i][1] * mData[i][1] + mData[i][2] * mData[i][2])), value_type(1))) /// check it in the max
            flags &= ~SCL_IDENT;

        if (!sts::isEqual(mData[3][i], value_type(0)))
            flags &= ~POS_IDENT;

        if (i) {
            if (!sts::isEqual(mData[i][0], value_type(0)))
                flags &= ~ROT_IDENT;
        }

        if (i != 1) {
            if (!sts::isEqual(mData[i][1], value_type(0)))
                flags &= ~ROT_IDENT;
        }

        if (i != 2) {
            if (!sts::isEqual(mData[i][2], value_type(0)))
                flags &= ~ROT_IDENT;
        }
        ++i;
    } while (i < 3);

    if ((flags & ROT_IDENT) == ROT_IDENT) {
        if (!sts::isEqual(mData[0][0], value_type(1)))
            flags &= ~ROT_IDENT;
        else if (!sts::isEqual(mData[1][1], value_type(1)))
            flags &= ~ROT_IDENT;
        else if (!sts::isEqual(mData[2][2], value_type(1)))
            flags &= ~ROT_IDENT;
    }
    mFlags = (mFlags & ~MAT_IDENT) | flags;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*! \details for internal use only \code return reinterpret_cast<value_type*>(mData); \endcode */
template<class value_type>
value_type * TMatrix3<value_type>::rawData() {
    return reinterpret_cast<value_type*>(mData);
}

/*! \details for internal use only \code return reinterpret_cast<const value_type*>(mData); \endcode */
template<class value_type>
const value_type * TMatrix3<value_type>::rawData() const {
    return reinterpret_cast<const value_type*>(mData);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
