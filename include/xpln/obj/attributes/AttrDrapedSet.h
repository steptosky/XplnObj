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

#include "xpln/obj/attributes/AttrDrapedLayerGroup.h"
#include "xpln/obj/attributes/AttrLodDrap.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the draped geometry attributes set.
 * \ingroup Attributes
 */
class AttrDrapedSet {
public:

    //-------------------------------------------------------------------------
    /// @{

    AttrDrapedSet() = default;
    virtual ~AttrDrapedSet() = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void setLayerGroup(const AttrDrapedLayerGroup & attr);
    void setLod(const AttrLodDrap & attr);

    const AttrDrapedLayerGroup & layerGroup() const;
    const AttrLodDrap & lod() const;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void reset();

    /// @}
    //-------------------------------------------------------------------------

private:

    AttrDrapedLayerGroup mLayerGroup;
    AttrLodDrap mLod;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline void AttrDrapedSet::reset() {
    mLayerGroup = AttrDrapedLayerGroup();
    mLod = AttrLodDrap();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

inline void AttrDrapedSet::setLayerGroup(const AttrDrapedLayerGroup & attr) {
    mLayerGroup = attr;
}

inline const AttrDrapedLayerGroup & AttrDrapedSet::layerGroup() const {
    return mLayerGroup;
}

inline void AttrDrapedSet::setLod(const AttrLodDrap & attr) {
    mLod = attr;
}

inline const AttrLodDrap & AttrDrapedSet::lod() const {
    return mLod;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
