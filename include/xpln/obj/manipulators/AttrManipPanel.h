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

#include <optional>
#include "xpln/Export.h"
#include "xpln/enums/EManipulator.h"
#include "xpln/obj/attributes/AttrCockpit.h"

namespace xobj {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details Panel-Click manipulator
 * \ingroup Manipulators
 */
class AttrManipPanel final {
public:

    //-------------------------------------------------------------------------
    /// @{

    AttrManipPanel() = default;

    explicit AttrManipPanel(AttrCockpit cockpit)
        : mAttrCockpit(std::move(cockpit)) {}

    AttrManipPanel(const AttrManipPanel &) = default;
    AttrManipPanel(AttrManipPanel &&) = default;

    ~AttrManipPanel() = default;

    AttrManipPanel & operator=(const AttrManipPanel &) = default;
    AttrManipPanel & operator=(AttrManipPanel &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib bool operator==(const AttrManipPanel & other) const;
    bool operator!=(const AttrManipPanel & other) const { return !this->operator==(other); }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

	XpObjLib static const EManipulator mType;

    /*!
     * \details Panel manipulator can be enabled with the cockpit attribute only.
     *        This is the cockpit attribute which will be used for enabling the manipulator.
     * \note This var is for internal using only! The developer must not use it.
     */
    std::optional<AttrCockpit> mAttrCockpit;

    /// @}
    //-------------------------------------------------------------------------

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

}
