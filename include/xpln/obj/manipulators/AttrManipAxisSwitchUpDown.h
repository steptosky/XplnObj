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

#include "AttrManipBase.h"
#include "embeddable/AttrManipWheel.h"

namespace xobj {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details Delta ATTR_manip_axis_switch_up_down
 * \ingroup Manipulators
 */
class AttrManipAxisSwitchUpDown : public AttrManipBase {
public:

    XpObjLib AttrManipAxisSwitchUpDown();
    virtual ~AttrManipAxisSwitchUpDown() = default;

	bool operator==(const AttrManipAxisSwitchUpDown& other) const { return equals(&other); }
	bool operator!=(const AttrManipAxisSwitchUpDown& other) const { return !equals(&other); }

    //-------------------------------------------------------------------------

    XpObjLib void setClickDelta(float val);
    XpObjLib void setHoldDelta(float val);
    XpObjLib void setMinimum(float val);
    XpObjLib void setMaximum(float val);
    XpObjLib float clickDelta() const;
    XpObjLib float holdDelta() const;
    XpObjLib float minimum() const;
    XpObjLib float maximum() const;

    XpObjLib const std::string & dataref() const;
    XpObjLib void setDataref(const std::string & val);

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

    /*! \copydoc AttrManipBase::equals */
    XpObjLib bool equals(const AttrManipBase * manip) const override;

    /*! \copydoc AttrManipBase::clone */
    XpObjLib AttrManipBase * clone() const override;

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::printObj */
    XpObjLib std::size_t printObj(AbstractWriter & writer) const override final;

    //-------------------------------------------------------------------------

private:

    float mClickDelta = 0.0f;
    float mHoldDelta = 0.0f;
    float mMin = 0.0f;
    float mMax = 0.0f;
    std::string mDataref = "none";
    AttrManipWheel mWheel;

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
