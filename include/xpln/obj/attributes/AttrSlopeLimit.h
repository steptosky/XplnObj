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

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details SLOPE_LIMIT
 * \ingroup Attributes
 */
class AttrSlopeLimit {
public:

    //-------------------------------------------------------------------------
    /// @{

    AttrSlopeLimit() = default;

    AttrSlopeLimit(const float minPitch, const float maxPitch,
                   const float minRoll, const float maxRoll)
        : mMinPitch(minPitch),
          mMaxPitch(maxPitch),
          mMinRoll(minRoll),
          mMaxRoll(maxRoll) { }

    AttrSlopeLimit(const AttrSlopeLimit &) = default;
    AttrSlopeLimit(AttrSlopeLimit &&) = default;

    ~AttrSlopeLimit() = default;

    AttrSlopeLimit & operator=(const AttrSlopeLimit &) = default;
    AttrSlopeLimit & operator=(AttrSlopeLimit &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib bool operator==(const AttrSlopeLimit & other) const;
    bool operator!=(const AttrSlopeLimit & other) const { return !operator==(other); }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void setMinPitch(const float minPitch) { mMinPitch = minPitch; }
    void setMaxPitch(const float maxPitch) { mMaxPitch = maxPitch; }
    void setMinRoll(const float minRoll) { mMinRoll = minRoll; }
    void setMaxRoll(const float maxRoll) { mMaxRoll = maxRoll; }

    float minPitch() const { return mMinPitch; }
    float maxPitch() const { return mMaxPitch; }
    float minRoll() const { return mMinRoll; }
    float maxRoll() const { return mMaxRoll; }

    /// @}
    //-------------------------------------------------------------------------

private:

    float mMinPitch = 0.0f;
    float mMaxPitch = 0.0f;
    float mMinRoll = 0.0f;
    float mMaxRoll = 0.0f;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
