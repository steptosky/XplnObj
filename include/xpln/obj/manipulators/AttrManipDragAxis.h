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

#include <vector>
#include "AttrManipBase.h"
#include "embeddable/AttrManipWheel.h"
#include "embeddable/AttrAxisDetented.h"
#include "embeddable/AttrAxisDetentRange.h"

namespace xobj {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details ATTR_manip_drag_axis
 * \ingroup Manipulators
 */
class AttrManipDragAxis : public AttrManipBase {
public:

    typedef std::vector<AttrAxisDetentRange> DetentRanges;

    //-------------------------------------------------------------------------

    XpObjLib AttrManipDragAxis();
    virtual ~AttrManipDragAxis() = default;

    //-------------------------------------------------------------------------

    [[deprecated("use setDirectionX")]]
    void setX(const float val) { setDirectionX(val); }

    [[deprecated("use setDirectionY")]]
    void setY(const float val) { setDirectionY(val); }

    [[deprecated("use setDirectionZ")]]
    void setZ(const float val) { setDirectionZ(val); }

    [[deprecated("use directionX")]]
    float x() const { return directionX(); }

    [[deprecated("use directionY")]]
    float y() const { return directionY(); }

    [[deprecated("use directionZ")]]
    float z() const { return directionZ(); }

    //-------------------------------------------------------------------------

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

    void setValues(const float x1, const float x2) {
        setVal1(x1);
        setVal2(x2);
    }

    XpObjLib void setVal1(float val);
    XpObjLib void setVal2(float val);
    XpObjLib float val1() const;
    XpObjLib float val2() const;

    XpObjLib void setDataref(const std::string & val);
    XpObjLib const std::string & dataref() const;

    //-------------------------------------------------------------------------

    XpObjLib void setAxisDetented(const AttrAxisDetented & val);
    XpObjLib const AttrAxisDetented & axisDetented() const;

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::equals */
    XpObjLib bool equals(const AttrManipBase * manip) const override;

    /*! \copydoc AttrManipBase::clone */
    XpObjLib AttrManipBase * clone() const override;

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::printObj */
    XpObjLib std::size_t printObj(AbstractWriter & writer) const override final;

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

    /*!
     * \see AttrManipWheel
     */
    void setWheel(const AttrManipWheel & ranges) {
        mWheel = ranges;
    }

    /*!
     * \see AttrManipWheel
     */
    AttrManipWheel & wheel() {
        return mWheel;
    }

    /*!
     * \see AttrManipWheel
     */
    const AttrManipWheel & wheel() const {
        return mWheel;
    }
        
    //------------------------------------------

    [[deprecated("use wheel().serEnabled()")]]
    void setWheelEnabled(const bool state) { wheel().setEnabled(state); }

    [[deprecated("use wheel().setDelta()")]]
    void setWheelDelta(const float delta) { wheel().setDelta(delta); }

    [[deprecated("use wheel().isEnabled()")]]
    bool isWheelEnabled() const { return wheel().isEnabled(); }

    [[deprecated("use wheel().delta()")]]
    float wheelDelta() const { return wheel().delta(); }

    //-------------------------------------------------------------------------

private:

    float mX = 0.0f;
    float mY = 0.0f;
    float mZ = 0.0f;
    float mVal1 = 0.0f;
    float mVal2 = 1.0f;
    AttrAxisDetented mAxisDetented;
    DetentRanges mAxisDetentRanges;
    std::string mDataref = "none";
    AttrManipWheel mWheel;

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
