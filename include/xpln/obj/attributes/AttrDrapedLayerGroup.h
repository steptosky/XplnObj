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
#include "xpln/enums/ELayer.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details ATTR_layer_group_draped
 * \ingroup Attributes
 */
class AttrDrapedLayerGroup final {
public:

    //-------------------------------------------------------------------------
    /// @{
    /// 
    AttrDrapedLayerGroup() = default;

    explicit AttrDrapedLayerGroup(const ELayer layer, const std::int32_t offset = 0)
        : mOffset(static_cast<uint8_t>(offset)),
          mLayer(layer) { }

    AttrDrapedLayerGroup(const AttrDrapedLayerGroup &) = default;
    AttrDrapedLayerGroup(AttrDrapedLayerGroup &&) = default;

    ~AttrDrapedLayerGroup() = default;

    AttrDrapedLayerGroup & operator=(const AttrDrapedLayerGroup &) = default;
    AttrDrapedLayerGroup & operator=(AttrDrapedLayerGroup &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib bool operator==(const AttrDrapedLayerGroup & other) const;
    bool operator!=(const AttrDrapedLayerGroup & other) const { return !operator==(other); }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib void setOffset(std::int32_t offset);
    void setLayer(const ELayer layer) { mLayer = layer; }

    std::int32_t offset() const { return static_cast<std::int32_t>(mOffset); }
    ELayer layer() const { return mLayer; }

    /// @}
    //-------------------------------------------------------------------------

private:

    std::int8_t mOffset = 0;
    ELayer mLayer = ELayer(ELayer::objects);

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
