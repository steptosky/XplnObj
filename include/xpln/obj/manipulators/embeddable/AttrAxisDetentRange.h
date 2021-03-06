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

#include <cstddef>
#include "xpln/Export.h"

namespace xobj {

class AbstractWriter;

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details ATTR_axis_detent_range
 * \ingroup Manipulators
 */
class AttrAxisDetentRange {
public:

    //-------------------------------------------------------------------------

    AttrAxisDetentRange() = default;

    AttrAxisDetentRange(const float start, const float end, const float height)
        : mStart(start),
          mEnd(end),
          mHeight(height) {}

    AttrAxisDetentRange(const AttrAxisDetentRange &) = default;
    AttrAxisDetentRange(AttrAxisDetentRange &&) = default;

    virtual ~AttrAxisDetentRange() = default;

    AttrAxisDetentRange & operator=(const AttrAxisDetentRange &) = default;
    AttrAxisDetentRange & operator=(AttrAxisDetentRange &&) = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator==(const AttrAxisDetentRange & other) const;
    XpObjLib bool operator!=(const AttrAxisDetentRange & other) const;

    //-------------------------------------------------------------------------

    XpObjLib void setStart(float val);
    XpObjLib void setEnd(float val);
    XpObjLib void setHeight(float val);

    XpObjLib float start() const;
    XpObjLib float end() const;
    XpObjLib float height() const;

    //-------------------------------------------------------------------------

    /*! \copydoc AttrManipBase::printObj */
    XpObjLib std::size_t printObj(AbstractWriter & writer) const;

    //-------------------------------------------------------------------------

private:

    float mStart = 0.0f;
    float mEnd = 0.0f;
    float mHeight = 0.0f;

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
}
