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

#include <string>
#include <optional>
#include "xpln/obj/attributes/AttrBlend.h"
#include "xpln/obj/attributes/AttrLayerGroup.h"
#include "xpln/obj/attributes/AttrSlungLoadWeight.h"
#include "xpln/obj/attributes/AttrSpecular.h"
#include "xpln/obj/attributes/AttrTint.h"
#include "xpln/obj/attributes/AttrWetDry.h"
#include "xpln/obj/attributes/AttrSlopeLimit.h"
#include "xpln/obj/attributes/AttrCockpitRegion.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the global attributes set
 * \ingroup Attributes
 */
class AttrGlobSet final {
public:

    //-------------------------------------------------------------------------
    /// @{

    AttrGlobSet() = default;
    AttrGlobSet(const AttrGlobSet &) = default;
    AttrGlobSet(AttrGlobSet &&) = default;

    ~AttrGlobSet() = default;

    AttrGlobSet & operator=(const AttrGlobSet &) = default;
    AttrGlobSet & operator=(AttrGlobSet &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void reset() { *this = AttrGlobSet(); }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    std::optional<std::string> mTexture;
    std::optional<std::string> mTextureLit;
    std::optional<std::string> mTextureNormal;
    std::optional<std::string> mParticleSystemPath;

    std::optional<AttrBlend> mBlend;
    std::optional<AttrLayerGroup> mLayerGroup;
    std::optional<AttrSlungLoadWeight> mSlungLoadWeight;
    std::optional<AttrSpecular> mSpecular;
    std::optional<AttrTint> mTint;
    std::optional<AttrWetDry> mWetDry;
    std::optional<AttrSlopeLimit> mSlopeLimit;
    std::optional<AttrCockpitRegion> mCockpitRegion1;
    std::optional<AttrCockpitRegion> mCockpitRegion2;
    std::optional<AttrCockpitRegion> mCockpitRegion3;
    std::optional<AttrCockpitRegion> mCockpitRegion4;

    bool mBlendClass = false;
    bool mNormalMetalness = false;
    bool mTilted = false;
    // todo check for bool inversion as the method was named as "setNoShadow()"
    bool mDropShadow = false;
    bool mCockpitLit = false;
    bool mDebug = false;

    /// @}
    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
