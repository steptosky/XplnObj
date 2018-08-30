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
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
inline const unsigned char Quaternion<Type>::ioVersion() const {
    return 0;
}

template<class Type>
inline const unsigned Quaternion<Type>::ioIdSize() const {
    return 5;
}

template<class Type>
inline const char * Quaternion<Type>::ioId() const {
    return "@QUAT";
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
inline Quaternion<Type>::Quaternion()
    : Quaternion(Type(0), Type(0), Type(0), Type(1)) {}

template<class Type>
inline Quaternion<Type>::Quaternion(Type inX, Type inY, Type inZ, Type inW) {
    mData[0] = inX;
    mData[1] = inY;
    mData[2] = inZ;
    mData[3] = inW;
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
inline bool Quaternion<Type>::operator !=(const Quaternion<Type> & inRight) const {
    return (
        mData[0] != inRight.mData[0] ||
        mData[1] != inRight.mData[1] ||
        mData[2] != inRight.mData[2] ||
        mData[3] != inRight.mData[3]
    );
}

template<class Type>
inline bool Quaternion<Type>::operator ==(const Quaternion<Type> & inRight) const {
    return (
        mData[0] == inRight.mData[0] &&
        mData[1] == inRight.mData[1] &&
        mData[2] == inRight.mData[2] &&
        mData[3] == inRight.mData[3]
    );
}

//-------------------------------------------------------------------------

/*!
\details Gets const reference to a cell.
\param [in] i cell index, maximum value is 3 (4 cells).
\return \code  return reinterpret_cast<const Type*>(mData)[i]; \endcode
*/
template<class Type>
inline const Type & Quaternion<Type>::operator[](size_t i) const {
    assert(i < 4);
    return reinterpret_cast<const Type*>(mData)[i];
}

/*!
\details Gets reference to a cell.
\param [in] i cell index, maximum value is 3 (4 cells).
\return \code  return reinterpret_cast<const Type*>(mData)[i]; \endcode
*/
template<class Type>
inline Type & Quaternion<Type>::operator[](size_t i) {
    assert(i < 4);
    return reinterpret_cast<Type*>(mData)[i];
}

//-------------------------------------------------------------------------

/*!
\warning Multiplication is not commutative! p*q != q*p.
\remark <b> \n
(X) q0 = q3 * p0 + q0 * p3 + q1 * p2 - q2 * p1 \n
(Y) q1 = q3 * p1 - q0 * p2 + q1 * p3 + q2 * p0 \n
(Z) q2 = q3 * p2 + q0 * p1 - q1 * p0 + q2 * p3 \n
(W) q3 = q3 * p3 - q0 * p0 - q1 * p1 - q2 * p2 \n
</b>
*/
template<class Type>
inline Quaternion<Type> Quaternion<Type>::operator *(const Quaternion<Type> & inQ) const {
    return Quaternion<Type>(*this) *= inQ;
}

// template<class Type>
// inline Quaternion<Type> Quaternion<Type>::operator / (const Quaternion<Type> & inQ) const {
//     return Quaternion<Type>(*this) /= inQ;
// }

template<class Type>
inline Quaternion<Type> Quaternion<Type>::operator *(Type inScalar) const {
    return Quaternion(
                      mData[0] * inScalar,
                      mData[1] * inScalar,
                      mData[2] * inScalar,
                      mData[3] * inScalar
                     );
}

template<class Type>
inline Quaternion<Type> Quaternion<Type>::operator /(Type inScalar) const {
    return Quaternion<Type>(*this) /= inScalar;
}

//-------------------------------------------------------------------------

template<class Type>
inline Quaternion<Type> & Quaternion<Type>::operator *=(const Quaternion & inQ) {
    set(
        // (X) q0 = q3 * p0 + q0 * p3 + q1 * p2 - q2 * p1
        mData[3] * inQ.mData[0] +
        mData[0] * inQ.mData[3] +
        mData[1] * inQ.mData[2] -
        mData[2] * inQ.mData[1],
        // (Y) q1 = q3 * p1 - q0 * p2 + q1 * p3 + q2 * p0
        mData[3] * inQ.mData[1] -
        mData[0] * inQ.mData[2] +
        mData[1] * inQ.mData[3] +
        mData[2] * inQ.mData[0],
        // (Z) q2 = q3 * p2 + q0 * p1 - q1 * p0 + q2 * p3
        mData[3] * inQ.mData[2] +
        mData[0] * inQ.mData[1] -
        mData[1] * inQ.mData[0] +
        mData[2] * inQ.mData[3],
        // (W) q3 = q3 * p3 - q0 * p0 - q1 * p1 - q2 * p2
        mData[3] * inQ.mData[3] -
        mData[0] * inQ.mData[0] -
        mData[1] * inQ.mData[1] -
        mData[2] * inQ.mData[2]
       );
    return *this;
}

/*
\details The result is the ratio of two quaternions:
This creates a result quaternion r = p/q, such that q*r = p. (Order of multiplication is important)
\param [in] inQ
\return this
*/
// template<class Type>
// inline Quaternion<Type> & Quaternion<Type> ::operator /= (const Quaternion& inQ) {
//     return *this;
// }

template<class Type>
inline Quaternion<Type> & Quaternion<Type>::operator *=(Type inScalar) {
    mData[0] *= inScalar;
    mData[1] *= inScalar;
    mData[2] *= inScalar;
    mData[3] *= inScalar;
    return *this;
}

template<class Type>
inline Quaternion<Type> & Quaternion<Type>::operator /=(Type inScalar) {
    if (!sts::isEqual(inScalar, Type(0))) {
        Type invScalar = Type(1) / inScalar;
        *this *= invScalar;
        return *this;
    }
    clear();
    return *this;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
\details Length 4 components (x,y,z,w) of the quaternion
*/
template<class Type>
inline double Quaternion<Type>::length() const {
    return sqrt(
                mData[0] * mData[0] +
                mData[1] * mData[1] +
                mData[2] * mData[2] +
                mData[3] * mData[3]
               );
}

/*!
\details Dot product
\param [in] q other quaternion
*/
template<class Type>
inline double Quaternion<Type>::dot(const Quaternion<Type> & q) const {
    return (
        mData[0] * q.mData[0] +
        mData[1] * q.mData[1] +
        mData[2] * q.mData[2] +
        mData[3] * q.mData[3]
    );
}

/*!
\details Normalize the quaternion
*/
template<class Type>
inline void Quaternion<Type>::normalize() {
    double len = length();
    if (sts::isEqual(len, Type(0))) {
        clear();
        return;
    }
    double invLength = Type(1) / len;
    mData[0] *= invLength;
    mData[1] *= invLength;
    mData[2] *= invLength;
    mData[3] *= invLength;
}

/*!
\details Gets normalized
*/
template<class Type>
inline Quaternion<Type> Quaternion<Type>::normalized() const {
    Quaternion<Type> out(*this);
    out.normalize();
    return out;
}

/*!
\details Conjugate quaternion
\details Change vector's components to opposite sign. It can be need for opposite rotation.
*/
template<class Type>
inline void Quaternion<Type>::conjugate() {
    mData[0] = -mData[0];
    mData[1] = -mData[1];
    mData[2] = -mData[2];
}

/*!
\details Get new conjugate quaternion
\details more \link Quaternion::conjugate \endlink .
*/
template<class Type>
inline Quaternion<Type> Quaternion<Type>::conjugated() const {
    return Quaternion<Type>(-mData[0], -mData[1], -mData[2], mData[3]);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
inline void Quaternion<Type>::setX(const Type inX) {
    mData[0] = inX;
}

template<class Type>
inline void Quaternion<Type>::setY(const Type inY) {
    mData[1] = inY;
}

template<class Type>
inline void Quaternion<Type>::setZ(const Type inZ) {
    mData[2] = inZ;
}

template<class Type>
inline void Quaternion<Type>::setW(const Type inW) {
    mData[3] = inW;
}

template<class Type>
inline Type Quaternion<Type>::x() const {
    return mData[0];
}

template<class Type>
inline Type Quaternion<Type>::y() const {
    return mData[1];
}

template<class Type>
inline Type Quaternion<Type>::z() const {
    return mData[2];
}

template<class Type>
inline Type Quaternion<Type>::w() const {
    return mData[3];
}

template<class Type>
inline void Quaternion<Type>::set(Type inX, Type inY, Type inZ, Type inW) {
    mData[0] = inX;
    mData[1] = inY;
    mData[2] = inZ;
    mData[3] = inW;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
inline void Quaternion<Type>::clear() {
    zero();
}

template<class Type>
inline void Quaternion<Type>::identity() {
    mData[0] = Type(0);
    mData[1] = Type(0);
    mData[2] = Type(0);
    mData[3] = Type(1);
}

template<class Type>
inline bool Quaternion<Type>::isIdentity() const {
    return (
        sts::isEqual(mData[0], Type(0)) &&
        sts::isEqual(mData[1], Type(0)) &&
        sts::isEqual(mData[2], Type(0)) &&
        mData[3] > Type(0)
    );
}

template<class Type>
inline bool Quaternion<Type>::isNull() const {
    return (
        sts::isEqual(mData[0], Type(0)) &&
        sts::isEqual(mData[1], Type(0)) &&
        sts::isEqual(mData[2], Type(0)) &&
        sts::isEqual(mData[3], Type(0))
    );
}

template<class Type>
inline bool Quaternion<Type>::isIdentityOrNull() const {
    return (
        sts::isEqual(mData[0], Type(0)) &&
        sts::isEqual(mData[1], Type(0)) &&
        sts::isEqual(mData[2], Type(0))
    );
}

template<class Type>
inline void Quaternion<Type>::zero() {
    mData[0] = Type(0);
    mData[1] = Type(0);
    mData[2] = Type(0);
    mData[3] = Type(0);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*! \details Saves data to a stream */
template<class Type>
inline void Quaternion<Type>::save(std::ostream & outStream) const {
    unsigned char typeSize = sizeof(Type);
    unsigned char version = ioVersion();
    outStream.write(ioId(), ioIdSize());
    outStream.write(reinterpret_cast<const char*>(&version), sizeof(version));
    outStream.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
    outStream.write(reinterpret_cast<const char*>(mData), sizeof(mData));
}

/*! \details Loads data from a stream */
template<class Type>
inline void Quaternion<Type>::load(std::istream & inStream) {
    //-------------------------------------------------------------------------
    char * id = new char[ioIdSize()];
    inStream.read(id, ioIdSize());
    std::string strId(id, ioIdSize());
    delete[] id;
    if (strId != ioId()) {
        throw std::runtime_error(std::string(__FUNCTION__) +
                                 " Incorrect data \"id\". Input: <" + strId +
                                 "> must be <" + ioId() + ">.\n");
    }
    //-------------------------------------------------------------------------
    unsigned char version = 0;
    inStream.read(reinterpret_cast<char*>(&version), sizeof(version));
    if (version != ioVersion()) {
        throw std::runtime_error(std::string(__FUNCTION__) +
                                 " Incorrect data \"Version\". Input: <" + std::to_string(version) +
                                 "> must be <" + std::to_string(ioVersion()) + ">.\n");
    }
    //-------------------------------------------------------------------------
    unsigned char typeSize = 0;
    inStream.read(reinterpret_cast<char*>(&typeSize), sizeof(typeSize));
    if (typeSize != static_cast<unsigned char>(sizeof(Type))) {
        throw std::runtime_error(std::string(__FUNCTION__) +
                                 " Incorrect data \"Type size\". Input: <" + strId.c_str() +
                                 "> must be <" + std::to_string(sizeof(Type)) + ">.\n");
    }
    //-------------------------------------------------------------------------
    inStream.read(reinterpret_cast<char*>(mData), sizeof(mData));
    //-------------------------------------------------------------------------
}

template<class Type>
inline std::ostream & operator <<(std::ostream & stream, const Quaternion<Type> & inMtx) {
    inMtx.save(stream);
    return stream;
}

template<class Type>
inline std::istream & operator >>(std::istream & stream, Quaternion<Type> & outMtx) {
    outMtx.load(stream);
    return stream;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
std::string Quaternion<Type>::toString(const std::string & inFormat, uint8_t precision) {
    std::stringstream out;
    out.precision(precision);
    bool val = false;
    for (const char & curr : inFormat) {
        if (val) {
            switch (curr) {
                case 'x': out << mData[0];
                    break;
                case 'y': out << mData[1];
                    break;
                case 'z': out << mData[2];
                    break;
                case 'w': out << mData[3];
                    break;
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

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
