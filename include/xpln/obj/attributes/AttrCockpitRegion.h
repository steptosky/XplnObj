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

#include <cstdint>
#include "xpln/Export.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details COCKPIT_REGION
 * \ingroup Attributes
 */
class AttrCockpitRegion {
public:

    enum eNum {
        r1,
        r2,
        r3,
        r4
    };

    /*!
     * \details Constructor default.
     * \note Makes the disabled attribute.
     */
    XpObjLib AttrCockpitRegion();

    /*!
     * \details Constructor init.
     * \note Makes the enabled attribute.
     * \param [in] left 
     * \param [in] bottom 
     * \param [in] right 
     * \param [in] top 
     */
    XpObjLib AttrCockpitRegion(std::int32_t left, std::int32_t bottom,
                               std::int32_t right, std::int32_t top);

    ~AttrCockpitRegion() = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator==(const AttrCockpitRegion & other) const;
    XpObjLib bool operator!=(const AttrCockpitRegion & other) const;

    //-------------------------------------------------------------------------

    XpObjLib void setLeft(int32_t left);
    XpObjLib void setBottom(int32_t bottom);
    XpObjLib void setRight(int32_t right);
    XpObjLib void setTop(int32_t top);

    XpObjLib int32_t left() const;
    XpObjLib int32_t bottom() const;
    XpObjLib int32_t right() const;
    XpObjLib int32_t top() const;

    //-------------------------------------------------------------------------

private:

    std::int32_t mLeft;
    std::int32_t mBottom;
    std::int32_t mRight;
    std::int32_t mTop;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
