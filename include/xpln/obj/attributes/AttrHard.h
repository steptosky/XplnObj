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
#include "xpln/enums/ESurface.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details ATTR_hard, ATTR_no_hard / ATTR_hard_deck
 * \ingroup Attributes
 */
class AttrHard final {
public:

    //-------------------------------------------------------------------------
    /// @{

    AttrHard() = default;

    explicit AttrHard(const ESurface surface, const bool deck = false)
        : mESurface(surface),
          mIsDeck(deck) { }

    AttrHard(const AttrHard &) = default;
    AttrHard(AttrHard &&) = default;

    ~AttrHard() = default;

    AttrHard & operator=(const AttrHard &) = default;
    AttrHard & operator=(AttrHard &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib bool operator==(const AttrHard & other) const;
    bool operator!=(const AttrHard & other) const { return !operator==(other); }

    //-------------------------------------------------------------------------

    void setESurface(const ESurface & surface, bool deck = false) {
        mESurface = surface;
        mIsDeck = deck;
    }

    const ESurface & surface() const { return mESurface; }
    bool isDeck() const { return mIsDeck; }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \note For internal use only.
     * \return String with default values for simulator.
     *         It is needed when attribute has been enabled before
     *         and now should be disabled.
     */
    XpObjLib static std::string objDisableStr();

    /*!
     * \note For internal use only.
     * \return String for obj format.
     */
    XpObjLib std::string objStr() const;

    /// @}
    //-------------------------------------------------------------------------

private:

    ESurface mESurface = ESurface(ESurface::eId::none);
    bool mIsDeck = false;
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
