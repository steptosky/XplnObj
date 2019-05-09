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
#include <cstdint>
#include <cstddef>
#include "xpln/Export.h"
#include "xpln/enums/ECockpitDevice.h"

namespace xobj {

class AbstractWriter;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details ATTR_cockpit, ATTR_cockpit_region, ATTR_no_cockpit, ATTR_cockpit_device 
 * \ingroup Attributes
 */
class AttrCockpit {
public:

    //-------------------------------------------------------------------------
    /// @{

    enum eType : std::uint8_t {
        cockpit,
        region_1,
        region_2,
        region_3,
        region_4,
        cockpit_device,
    };

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    AttrCockpit() = default;

    explicit AttrCockpit(const eType type)
        : mType(type) {}

    AttrCockpit(const AttrCockpit &) = default;
    AttrCockpit(AttrCockpit &&) = default;

    ~AttrCockpit() = default;

    AttrCockpit & operator=(const AttrCockpit &) = default;
    AttrCockpit & operator=(AttrCockpit &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib bool operator==(const AttrCockpit & other) const;
    bool operator!=(const AttrCockpit & other) const { return !operator==(other); }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void setType(const eType type) { mType = type; }
    eType type() const { return mType; }

    /// @}
    //-------------------------------------------------------------------------
    /// \name ATTR_cockpit_device
    /// @{

    void setId(const ECockpitDevice id) { mDevName = id.toString(); }
    void setName(const std::string & name) { mDevName = name; }
    void setBus(const std::size_t index) { mDevBus = index; }
    void setLightingChannel(const std::size_t index) { mDevLighting = index; }
    void setAutoAdjust(const bool state) { mDevAutoAdjust = state; }

    const std::string & name() const { return mDevName; }
    std::size_t bus() const { return mDevBus; }
    std::size_t lightingChannel() const { return mDevLighting; }
    bool autoAdjust() const { return mDevAutoAdjust; }

    /// @}
    //-------------------------------------------------------------------------
    /// \name For internal use only
    /// @{

    /*!
     * \note For internal use only.
     * \return String with default values for simulator.
     *         It is needed when attribute has been enabled before
     *         and now should be disabled.
     */
    XpObjLib static std::string objDisableStr();

    /// @}
    //-------------------------------------------------------------------------

private:

    std::string mDevName;
    std::size_t mDevBus = 0;
    std::size_t mDevLighting = 0;
    eType mType = cockpit;
    bool mDevAutoAdjust = false;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
