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

#include "Point3.h"
#include "Quaternion.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details The transformation matrix 4x3
 */
class XpObjLib TMatrix {
public:

    TMatrix();
    TMatrix(const TMatrix & inCopy);
    ~TMatrix() = default;

    //-------------------------------------------------------------------------

    TMatrix & operator=(const TMatrix & inCopy);
    TMatrix & operator *=(const TMatrix & inRight);
    TMatrix operator *(const TMatrix & inRight) const;

    bool operator ==(const TMatrix & tr) const;
    bool operator !=(const TMatrix & tr) const;

    //-------------------------------------------------------------------------

    TMatrix inversed() const;

    void transformPoints(Point3 * inArray, unsigned inCount) const;
    void transformVectors(Point3 * inArray, unsigned inCount) const;
    void transformPoint(Point3 & inPoint) const;
    void transformVector(Point3 & inVec) const;

    //-------------------------------------------------------------------------

    void setPosition(const Point3 & p);
    void setRotate(const Quaternion & q);
    void setRotate(const Point3 & p, float angleDegress);

    //-------------------------------------------------------------------------

    void rotateRadiansX(float inAngleRadians);
    void rotateRadiansY(float inAngleRadians);
    void rotateRadiansZ(float inAngleRadians);

    void rotateDegreesX(float inAngleRadians);
    void rotateDegreesY(float inAngleRadians);
    void rotateDegreesZ(float inAngleRadians);

    //-------------------------------------------------------------------------

    void set(float m00, float m01, float m02,
             float m10, float m11, float m12,
             float m20, float m21, float m22,
             float m30, float m31, float m32);

    //-------------------------------------------------------------------------

    Point3 position() const;
    Quaternion rotation() const;

    /*!
     * \details Get the 'parity' of the matrix.
     *          Scaling one axis of the matrix negatively switches the 'parity'.
     *          However if you scale two axis the parity will flip back.
     *          Scaling three axis switches the parity again.
     * \remarks It can be used for check to flip normals
     * \return The 'parity' of the matrix
     */
    bool parity() const;

    /*!
     * \deprecated use \link TMatrix::parity \endlink
     */
    [[deprecated("use parity()")]]
    bool isParity() const { return parity(); }

    //-------------------------------------------------------------------------

    Point3 row(size_t i) const;

    //-------------------------------------------------------------------------

    void setTranslateIdentity();
    void setRotateIdentity(bool leaveScale = false);
    void setIdentity();

    //-------------------------------------------------------------------------

    std::string toString() const; // Print matrix for debug

    //-------------------------------------------------------------------------

    TMatrix toTranslation() const {
        TMatrix out = *this;
        out.setRotateIdentity();
        return out;
    }

    TMatrix toRotation() const {
        TMatrix out = *this;
        out.setTranslateIdentity();
        return out;
    }

    //-------------------------------------------------------------------------

private:

    float mData[4][3];
    uint32_t mFlags;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
