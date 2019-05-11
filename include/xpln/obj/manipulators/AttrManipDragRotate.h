#pragma once

/*
**  Copyright(C) 2018, StepToSky
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

#include "AttrManipBase.h"
#include "embeddable/AttrManipKeyFrame.h"
#include "embeddable/AttrAxisDetentRange.h"

namespace xobj {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details ATTR_manip_drag_rotate
 * \ingroup Manipulators
 */
class AttrManipDragRotate : public AttrManipBase {
public:

    typedef std::vector<AttrManipKeyFrame> Keys;
    typedef std::vector<AttrAxisDetentRange> DetentRanges;

	bool operator==(const AttrManipDragRotate& other) const { return equals(&other); }
	bool operator!=(const AttrManipDragRotate& other) const { return !equals(&other); }

    //-------------------------------------------------------------------------

    XpObjLib AttrManipDragRotate();
    virtual ~AttrManipDragRotate() = default;

    //-------------------------------------------------------------------------

    void setOrigin(const float x, const float y, const float z) {
        setOriginX(x);
        setOriginY(y);
        setOriginZ(z);
    }

    XpObjLib void setOriginX(float val);
    XpObjLib void setOriginY(float val);
    XpObjLib void setOriginZ(float val);
    XpObjLib float originX() const;
    XpObjLib float originY() const;
    XpObjLib float originZ() const;

    void setDirection(const float x, const float y, const float z) {
        setDirectionX(x);
        setDirectionY(y);
        setDirectionZ(z);
    }

    XpObjLib void setDirectionX(float val);
    XpObjLib void setDirectionY(float val);
    XpObjLib void setDirectionZ(float val);
    XpObjLib float directionX() const;
    XpObjLib float directionY() const;
    XpObjLib float directionZ() const;

    void setAngles(const float a1, const float a2) {
        setAngle1(a1);
        setAngle2(a2);
    }

    XpObjLib void setAngle1(float val);
    XpObjLib void setAngle2(float val);
    XpObjLib float angle1() const;
    XpObjLib float angle2() const;

    XpObjLib void setLift(float val);
    XpObjLib float lift() const;

    // todo min max checking (min <= max)

    void setV1(const float min, const float max) {
        setV1Min(min);
        setV1Max(max);
    }

    XpObjLib void setV1Min(float val);
    XpObjLib void setV1Max(float val);
    XpObjLib float v1Min() const;
    XpObjLib float v1Max() const;

    void setV2(const float min, const float max) {
        setV2Min(min);
        setV2Max(max);
    }

    XpObjLib void setV2Min(float val);
    XpObjLib void setV2Max(float val);
    XpObjLib float v2Min() const;
    XpObjLib float v2Max() const;

    void setDatarefs(const std::string & drf1, const std::string & drf2) {
        setDataref1(drf1);
        setDataref2(drf2);
    }

    XpObjLib void setDataref1(const std::string & val);
    XpObjLib void setDataref2(const std::string & val);
    XpObjLib const std::string & dataref1() const;
    XpObjLib const std::string & dataref2() const;

    //-------------------------------------------------------------------------

    /*!
     * \see AttrManipKeyFrame
     */
    void setKeys(const Keys & keys) { mKeys = keys; }

    /*!
     * \see AttrManipKeyFrame
     */
    Keys & keys() { return mKeys; }

    /*!
     * \see AttrManipKeyFrame
     */
    const Keys & keys() const { return mKeys; }

    //-------------------------------------------------------------------------

    /*!
     * \see AttrAxisDetentRange
     */
    void setDetentRanges(const DetentRanges & ranges) {
        mAxisDetentRanges = ranges;
    }

    /*!
     * \see AttrAxisDetentRange
     */
    DetentRanges & detentRanges() {
        return mAxisDetentRanges;
    }

    /*!
     * \see AttrAxisDetentRange
     */
    const DetentRanges & detentRanges() const {
        return mAxisDetentRanges;
    }

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::equals */
    XpObjLib bool equals(const AttrManipBase * manip) const override;

    /*! \copydoc AttrManipBase::clone */
    XpObjLib AttrManipBase * clone() const override;

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::printObj */
    XpObjLib std::size_t printObj(AbstractWriter & writer) const override final;

    //-------------------------------------------------------------------------

private:

    float mX = 0.0f;
    float mY = 0.0f;
    float mZ = 0.0f;

    float mDirX = 0.0f;
    float mDirY = 0.0f;
    float mDirZ = 0.0f;

    float mAngle1 = 0.0f;
    float mAngle2 = 0.0f;

    float mLift = 0.0f;

    float mV1Min = 0.0f;
    float mV1Max = 1.0f;

    float mV2Min = 0.0f;
    float mV2Max = 1.0f;

    std::string mDataref1 = "none";
    std::string mDataref2 = "none";

    Keys mKeys;
    DetentRanges mAxisDetentRanges;

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
