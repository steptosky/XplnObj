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

#include <cstddef>
#include "xpln/Export.h"

namespace xobj {

class AbstractWriter;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details ATTR_manip_wheel
 * \ingroup Manipulators
 */
class AttrManipWheel {
public:

    AttrManipWheel() = default;
    XpObjLib explicit AttrManipWheel(float delta);
    virtual ~AttrManipWheel() = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator==(const AttrManipWheel & other) const;
    XpObjLib bool operator!=(const AttrManipWheel & other) const;

    //-------------------------------------------------------------------------

    XpObjLib void setEnabled(bool state);
    XpObjLib void setDelta(float delta);
    XpObjLib bool isEnabled() const;
    XpObjLib float delta() const;

    //-------------------------------------------------------------------------

    [[deprecated("use serEnabled()")]]
    void setWheelEnabled(const bool state) { setEnabled(state); }

    [[deprecated("use setDelta()")]]
    void setWheelDelta(const float delta) { setDelta(delta); }

    [[deprecated("use isEnabled()")]]
    bool isWheelEnabled() const { return isEnabled(); }

    [[deprecated("use delta()")]]
    float wheelDelta() const { return delta(); }

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::printObj */
    XpObjLib std::size_t printObj(AbstractWriter & writer) const;

    //-------------------------------------------------------------------------

private:

    bool mWheel = false;
    float mWheelDelta = 0.0f;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
