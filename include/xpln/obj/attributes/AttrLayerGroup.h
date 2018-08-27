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

#include "xpln/Export.h"
#include "xpln/enums/ELayer.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details ATTR_layer_group
 * \ingroup Attributes
 */
class AttrLayerGroup {
public:

    /*!
     * \details Constructor default.
     * \note Makes the disabled attribute.
     */
    XpObjLib AttrLayerGroup();

    /*!
     * \details Constructor init.
     * \note Makes the enabled attribute.
     * \param [in] layer 
     * \param [in] offset 
     */
    XpObjLib AttrLayerGroup(ELayer layer, int32_t offset = 0);

    ~AttrLayerGroup() = default;

    //-------------------------------------------------------------------------

    /*!
     * \details Check whether the attribute is enabled.
     * \note All class's setters will enable this attribute.
     */
    XpObjLib operator bool() const;

    /*!
     * \details Sets the attribute enabled/disabled.
     * \note All class's setters will enable this attribute.
     * \param [in] state
     */
    XpObjLib void setEnabled(bool state);

    //-------------------------------------------------------------------------

    XpObjLib bool operator==(const AttrLayerGroup & other) const;
    XpObjLib bool operator!=(const AttrLayerGroup & other) const;

    //-------------------------------------------------------------------------

    XpObjLib void setOffset(int32_t offset);
    XpObjLib void setLayer(ELayer layer);

    XpObjLib int32_t offset() const;
    XpObjLib ELayer layer() const;

    //-------------------------------------------------------------------------

private:

    int8_t mOffset;
    ELayer mLayer;
    bool mIsEnabled : 1;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
