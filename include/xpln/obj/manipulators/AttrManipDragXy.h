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

namespace xobj {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details ATTR_manip_drag_xy
 * \ingroup Manipulators
 */
class AttrManipDragXy : public AttrManipBase {
public:

    XpObjLib AttrManipDragXy();
    virtual ~AttrManipDragXy() = default;

    //-------------------------------------------------------------------------

    XpObjLib void setX(float val);
    XpObjLib void setXMin(float val);
    XpObjLib void setXMax(float val);
    XpObjLib float x() const;
    XpObjLib float xMin() const;
    XpObjLib float xMax() const;
    XpObjLib void setXDataref(const std::string & val);
    XpObjLib const std::string & xDataref() const;

    XpObjLib void setY(float val);
    XpObjLib void setYMin(float val);
    XpObjLib void setYMax(float val);
    XpObjLib float y() const;
    XpObjLib float yMin() const;
    XpObjLib float yMax() const;
    XpObjLib void setYDataref(const std::string & val);
    XpObjLib const std::string & yDataref() const;

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
    float mXMin = 0.0f;
    float mXMax = 0.0f;
    float mYMin = 0.0f;
    float mYMax = 0.0f;
    std::string mXDataref = "none";
    std::string mYDataref = "none";

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
