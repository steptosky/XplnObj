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

template<class Type>
AxisAngle<Type>::AxisAngle()
    : AxisAngle<Type>(Type(0), Type(0), Type(0), Type(0)) {}

template<class Type>
AxisAngle<Type>::AxisAngle(const Vector3<Type> & inVec, Type inAngleRad)
    : AxisAngle<Type>(inVec.x, inVec.y, inVec.z, inAngleRad) {}

template<class Type>
AxisAngle<Type>::AxisAngle(Type inX, Type inY, Type inZ, Type inW) {
    mData[0] = inX;
    mData[1] = inY;
    mData[2] = inZ;
    mData[3] = inW;
}

template<class Type>
AxisAngle<Type>::~AxisAngle() {}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
bool AxisAngle<Type>::operator !=(const AxisAngle<Type> & inRight) const {
    return (
        !sts::isEqual(mData[0], inRight.mData[0]) ||
        !sts::isEqual(mData[1], inRight.mData[1]) ||
        !sts::isEqual(mData[2], inRight.mData[2]) ||
        !sts::isEqual(mData[3], inRight.mData[3]));
}

template<class Type>
bool AxisAngle<Type>::operator ==(const AxisAngle<Type> & inRight) const {
    return (
        sts::isEqual(mData[0], inRight.mData[0]) &&
        sts::isEqual(mData[1], inRight.mData[1]) &&
        sts::isEqual(mData[2], inRight.mData[2]) &&
        sts::isEqual(mData[3], inRight.mData[3]));
}

/*!
 * \details Gets const reference to a cell.
 * \param [in] i cell index, maximum value is 3 (4 cells).
 * \return \code  return reinterpret_cast<const Type*>(mData)[i]; \endcode
 */
template<class Type>
const Type & AxisAngle<Type>::operator[](size_t i) const {
    assert(i < 4);
    return reinterpret_cast<const Type*>(mData)[i];
}

/*!
 * \details Gets reference to a cell.
 * \param [in] i cell index, maximum value is 3 (4 cells).
 * \return \code  return reinterpret_cast<const Type*>(mData)[i]; \endcode
 */
template<class Type>
Type & AxisAngle<Type>::operator[](size_t i) {
    assert(i < 4);
    return reinterpret_cast<Type*>(mData)[i];
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
void AxisAngle<Type>::setX(const Type inX) {
    mData[0] = inX;
}

template<class Type>
void AxisAngle<Type>::setY(const Type inY) {
    mData[1] = inY;
}

template<class Type>
void AxisAngle<Type>::setZ(const Type inZ) {
    mData[2] = inZ;
}

template<class Type>
void AxisAngle<Type>::setW(const Type inW) {
    mData[3] = inW;
}

template<class Type>
Type AxisAngle<Type>::x() const {
    return mData[0];
}

template<class Type>
Type AxisAngle<Type>::y() const {
    return mData[1];
}

template<class Type>
Type AxisAngle<Type>::z() const {
    return mData[2];
}

template<class Type>
Type AxisAngle<Type>::w() const {
    return mData[3];
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
void AxisAngle<Type>::set(Type inX, Type inY, Type inZ, Type inAngleRad) {
    mData[0] = inX;
    mData[1] = inY;
    mData[2] = inZ;
    mData[3] = inAngleRad;
}

template<class Type>
void AxisAngle<Type>::set(const Vector3<Type> & inVec, Type inAngleRad) {
    mData[0] = inVec.x;
    mData[1] = inVec.y;
    mData[2] = inVec.z;
    mData[3] = inAngleRad;
}

template<class Type>
void sts_t::AxisAngle<Type>::clear() {
    mData[0] = Type(0);
    mData[1] = Type(0);
    mData[2] = Type(0);
    mData[3] = Type(0);
}

template<class Type>
void AxisAngle<Type>::setVector(const Vector3<Type> & inVec) {
    mData[0] = inVec.x;
    mData[1] = inVec.y;
    mData[2] = inVec.z;
}

/*!
 * \details Sets angle
 * \param [in] inAngleRad  angle in radians
 */
template<class Type>
void AxisAngle<Type>::setAngle(Type inAngleRad) {
    mData[3] = inAngleRad;
}

/*!
 * \details Gets angle.
 * \return angle in radians
 */
template<class Type>
double AxisAngle<Type>::angle() const {
    return mData[3];
}

template<class Type>
const Vector3<Type> & AxisAngle<Type>::vector() const {
    return *reinterpret_cast<const Vector3<Type>*>(&mData);
}

template<class Type>
Vector3<Type> & AxisAngle<Type>::vector() {
    return *reinterpret_cast<Vector3<Type>*>(&mData);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Returns the number of revolutions represented by the angle.
 * \return
 */
template<class Type>
int AxisAngle<Type>::numRevs() const {
    return static_cast<int>(angle() / (Type(2) * Type(3.14159265358979323846)));
}

/*!
 * \details Adds the number of revolution to num.
 * \param [in] inNum
 */
template<class Type>
void AxisAngle<Type>::addRevs(int inNum) {
    mData[3] += static_cast<Type>(inNum) * (Type(2) * Type(3.14159265358979323846));
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
std::string AxisAngle<Type>::toString(const std::string & inFormat /*= "%setX %setY %setZ %ad"*/, uint8_t precision /*= 6*/) {
    std::stringstream out;
    out.precision(precision);
    bool val = false;
    for (size_t i = 0; i < inFormat.size(); ++i) {
        if (val) {
            switch (inFormat[i]) {
                case 'x': out << mData[0];
                    break;
                case 'y': out << mData[1];
                    break;
                case 'z': out << mData[2];
                    break;
                case 'a': {
                    if (i == inFormat.size() - 1) {
                        out << mData[3];
                        break;
                    }
                    if (inFormat[i + 1] == 'd') {
                        out << sts::toDegrees(mData[3]);
                        ++i;
                    }
                    else if (inFormat[i + 1] == 'r') {
                        out << mData[3];
                        ++i;
                    }
                    else {
                        out << mData[3];
                    }
                    break;
                }
            }
            val = false;
            continue;
        }
        if (inFormat[i] == '%') {
            val = true;
            continue;
        }
        out << inFormat[i];
    }
    return out.str();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
