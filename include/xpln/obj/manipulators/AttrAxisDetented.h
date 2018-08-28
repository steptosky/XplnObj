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

#include <string>
#include "xpln/Export.h"

namespace xobj {

class AbstractWriter;

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details ATTR_axis_detented
 * \ingroup Manipulators
 */
class AttrAxisDetented {
public:

    //-------------------------------------------------------------------------

    AttrAxisDetented() = default;
    AttrAxisDetented(const AttrAxisDetented &) = default;
    AttrAxisDetented(AttrAxisDetented &&) = default;

    virtual ~AttrAxisDetented() = default;

    AttrAxisDetented & operator=(const AttrAxisDetented &) = default;
    AttrAxisDetented & operator=(AttrAxisDetented &&) = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator==(const AttrAxisDetented & other) const;
    XpObjLib bool operator!=(const AttrAxisDetented & other) const;

    //-------------------------------------------------------------------------

    bool isEnabled() const { return mIsEnabled; }

    //-------------------------------------------------------------------------

    void setDirection(const float x, const float y, const float z) {
        setDirectionX(x);
        setDirectionY(y);
        setDirectionZ(z);
    }

    void setValue(const float min, const float max) {
        setVMin(min);
        setVMax(max);
    }

    XpObjLib void setDirectionX(float val);
    XpObjLib void setDirectionY(float val);
    XpObjLib void setDirectionZ(float val);
    XpObjLib float directionX() const;
    XpObjLib float directionY() const;
    XpObjLib float directionZ() const;

    XpObjLib void setVMin(float val);
    XpObjLib void setVMax(float val);
    XpObjLib float vMin() const;
    XpObjLib float vMax() const;

    XpObjLib void setDataref(const std::string & val);
    XpObjLib const std::string & dataref() const;

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::printObj */
    XpObjLib std::size_t printObj(AbstractWriter & writer) const;

    //-------------------------------------------------------------------------

private:

    void setEnabled(const bool state = true) {
        mIsEnabled = state;
    }

    float mDirX = 0.0f;
    float mDirY = 0.0f;
    float mDirZ = 0.0f;

    float mVMin = 0.0f;
    float mVMax = 1.0f;

    std::string mDataref = "none";

    bool mIsEnabled = false;

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
