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

#include "ObjAbstractLight.h"
#include "xpln/common/Color.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the spill light
 * \ingroup Objects
 */
class ObjLightSpillCust : public ObjAbstractLight {
protected:

    ObjLightSpillCust(const ObjLightSpillCust &) = default;
    ObjLightSpillCust(ObjLightSpillCust &&) = default;

public:

    //-------------------------------------------------------------------------
    /// \name Construction/Destruction
    /// @{

    XpObjLib ObjLightSpillCust();
    virtual ~ObjLightSpillCust() = default;

    ObjLightSpillCust & operator=(const ObjLightSpillCust &) = delete;
    ObjLightSpillCust & operator=(ObjLightSpillCust &&) = delete;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Parameters
    /// @{

    void setColor(const Color & color) {
        mColor = color;
    }

    void setSize(const float size) {
        mSize = size;
    }

    void setSemiRaw(const float semi) {
        mSemi = semi;
    }

    XpObjLib void setSemiAngle(float radians);
    XpObjLib void setDirection(const Point3 & direction);

    void setDataRef(const std::string & dataRef) {
        mDataRef = dataRef;
    }

    Color color() const {
        return mColor;
    }

    float size() const {
        return mSize;
    }

    float semiRaw() const {
        return mSemi;
    }

    XpObjLib float semiAngle() const;

    Point3 direction() const {
        return mDirection;
    }

    const std::string & dataRef() const {
        return mDataRef;
    }

    /// @}
    //-------------------------------------------------------------------------
    /// \name
    /// @{

    /*! \copydoc ObjAbstract::objType */
    XpObjLib eObjectType objType() const final;

    /*! \copydoc ObjAbstract::applyTransform */
    XpObjLib void applyTransform(const TMatrix & tm, bool useParity = false) override final;

    /*! \copydoc ObjAbstract::clone */
    XpObjLib ObjAbstract * clone() const override;

    /// @}
    //-------------------------------------------------------------------------

private:

    float mSize;
    float mSemi;
    Color mColor;
    Point3 mDirection;
    std::string mDataRef;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
