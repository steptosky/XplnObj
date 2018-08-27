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

#include <vector>
#include <cstdint>
#include "xpln/Export.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Names of the named lights
 * \ingroup Enumerations
 */
class ELightNamed {
public:

    /*!
     * \note It is NOT guaranteed that the existing indexes will be constant when new data is added.
     *       So you can consider it when you design your serialization solution. You can use obj string (toString()).
     */
    enum eId : int32_t {
        none = 0,
        airplane_nav_left,
        airplane_nav_right,
        airplane_nav_tail,
        airplane_beacon,
        airplane_taxi,
        airplane_landing,
        airplane_strobe,
        taillight,
        headlight,
        carrier_meatball1,
        carrier_meatball2,
        carrier_meatball3,
        carrier_meatball4,
        carrier_meatball5,
        carrier_deck_blue_e,
        carrier_deck_blue_n,
        carrier_deck_blue_w,
        carrier_deck_blue_s,
        carrier_thresh_white,
        carrier_edge_white,
        carrier_center_white,
        carrier_foul_line_white,
        carrier_mast_strobe,
        carrier_waveoff,
        carrier_datum,
        carrier_foul_line_red,
        carrier_pitch_lights,
        ship_mast_powered,
        ship_mast_grn,
        ship_mast_obs,
        ship_nav_right,
        ship_nav_left,
        ship_nav_tail,
        obs_red_night,
        obs_red_day,
        obs_strobe_night,
        obs_strobe_day,
        frigate_deck_green,
        frigate_SGSI_hi,
        frigate_SGSI_on,
        frigate_SGSI_lo,
        oilrig_deck_blue,
        town_tiny_light_omni,
        town_tiny_light_60,
        town_tiny_light_90,
        town_tiny_light_150,
        town_tiny_light_180,
        town_tiny_light_220,
        town_tiny_light_280,
        town_tiny_light_330,
        town_tiny_light_350,
        town_light_omni,
        town_light_60,
        town_light_90,
        town_light_150,
        town_light_180,
        town_light_220,
        town_light_280,
        town_light_330,
        town_light_350,
    };

    //-------------------------------------------------------------------------

    typedef std::vector<ELightNamed> List;

    //-------------------------------------------------------------------------

    /*!
     * \details Constructor default.
     */
    XpObjLib ELightNamed();

    /*!
     * \details Constructor init from Id.
     * \param [in] id
     */
    XpObjLib explicit ELightNamed(eId id);

    XpObjLib ~ELightNamed() = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator ==(const ELightNamed & other) const;
    XpObjLib bool operator ==(eId id) const;

    XpObjLib bool operator !=(const ELightNamed & other) const;
    XpObjLib bool operator !=(eId id) const;

    //-------------------------------------------------------------------------

    /*!
     * \details Makes from string which is used in the UI.
     * \param [in] name
     */
    XpObjLib static ELightNamed fromUiString(const char * name);

    /*!
     * \details Makes from string which is used in the obj files.
     * \param [in] attrName
     */
    XpObjLib static ELightNamed fromString(const char * attrName);

    //-------------------------------------------------------------------------

    /*!
     * \details Checks whether this instance is valid.
     * \return True if valid otherwise false.
     */
    XpObjLib bool isValid() const;

    /*!
     * \details Gets id.
     */
    XpObjLib eId id() const;

    /*!
     * \details Gets string which is used in obj files.
     */
    XpObjLib const char * toString() const;

    /*!
     * \details Gets string which can be used for UI.
     */
    XpObjLib const char * toUiString() const;

    /*!
     * \details Gets list of all id.
     */
    XpObjLib static const List & list();

    //-------------------------------------------------------------------------

private:

    eId mId;
    static void makeList(List &);
    static List mList;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
