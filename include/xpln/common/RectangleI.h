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

#include "Point2.h"

namespace xobj {

/***********************************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************************************************/

/*!
 * \details Rectangle for texture coordinates, dimension by 2 points.
 * \remark s1,t1,s2,t2 - the texture coordinates (fractions from 0 to 1).
 *         S refers to horizontal coordinates, and T for vertical coordinates.
 */
class RectangleI {
public:

    /*! 
     * \details Sets rectangle
     * \param [in] p1 x = s1, y = t1
     * \param [in] p2 x = s2, y = t2
     */
    void setRect(const Point2 & p1, const Point2 & p2);

    /*!
     * \details Sets point 1
     * \param [in] p1 x = s1, y = t1
     */
    void setPoint1(const Point2 & p1);

    /*! 
     * \details Sets point 2
     * \param [in] p2 x = s2, y = t2
     */
    void setPoint2(const Point2 & p2);

    /*! 
     * \details Gets rectangle
     * \param [out] p1 x = s1, y = t1
     * \param [out] p2 x = s2, y = t2
     */
    void rect(Point2 & p1, Point2 & p2) const;

    /*! 
     * \details Sets point 1
     * \return Point1 x = s1, y = t1
     */
    const Point2 & point1() const;

    /*! 
     * \details Sets point 2
     * \return Point2 x = s2, y = t2
     */
    const Point2 & point2() const;

    /*! Operator = */
    RectangleI & operator=(const RectangleI & other);

    /*! Constructor default */
    RectangleI();

    /*! 
     * \details Constructor init
     * \param [in] p1 x = s1, y = t1
     * \param [in] p2 x = s2, y = t2
     */
    RectangleI(const Point2 & p1, const Point2 & p2);

    /*! Constructor copy  */
    RectangleI(const RectangleI & other);

    virtual ~RectangleI() = default;

private:

    Point2 mPoint1;
    Point2 mPoint2;

};

/***********************************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************************************************/

inline void RectangleI::setRect(const Point2 & p1, const Point2 & p2) {
    mPoint1 = p1;
    mPoint2 = p2;
}

inline void RectangleI::setPoint1(const Point2 & p1) {
    mPoint1 = p1;
}

inline void RectangleI::setPoint2(const Point2 & p2) {
    mPoint2 = p2;
}

inline void RectangleI::rect(Point2 & p1, Point2 & p2) const {
    p1 = mPoint1;
    p2 = mPoint2;
}

inline const Point2 & RectangleI::point1() const {
    return mPoint1;
}

inline const Point2 & RectangleI::point2() const {
    return mPoint2;
}

inline RectangleI & RectangleI::operator=(const RectangleI & other) {
    mPoint1 = other.mPoint1;
    mPoint2 = other.mPoint2;
    return *this;
}

inline RectangleI::RectangleI() = default;

inline RectangleI::RectangleI(const Point2 & p1, const Point2 & p2)
    : mPoint1(p1),
      mPoint2(p2) { }

inline RectangleI::RectangleI(const RectangleI & other)
    : mPoint1(other.mPoint1),
      mPoint2(other.mPoint2) { }

/***********************************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************************************************/

}
