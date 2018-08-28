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
 * \details Names of the params lights
 * \ingroup Enumerations
 */
class ELightParams {
public:

    /*!
     * \note It is NOT guaranteed that the existing indexes will be constant when new data is added.
     *       So you can consider it when you design your serialization solution. You can use obj string (toString()).
     */
    enum eId : std::int32_t {
        none = 0,
        light_params_custom,
        full_custom_halo,
        full_custom_halo_night,

        airplane_landing_core,
        airplane_landing_glow,
        airplane_landing_flare,
        airplane_landing_sp,

        airplane_taxi_core,
        airplane_taxi_glow,
        airplane_taxi_flare,
        airplane_taxi_sp,

        airplane_spot_core,
        airplane_spot_glow,
        airplane_spot_flare,
        airplane_spot_sp,

        airplane_generic_core,
        airplane_generic_glow,
        airplane_generic_flare,
        airplane_generic_sp,

        airplane_beacon_rotate,
        airplane_beacon_rotate_sp,

        airplane_beacon_strobe,
        airplane_beacon_strobe_sp,

        airplane_strobe_omni,
        airplane_strobe_dir,
        airplane_strobe_sp,

        airplane_nav_tail_size,
        airplane_nav_left_size,
        airplane_nav_right_size,
        airplane_nav_sp,

        airplane_panel_sp,
        airplane_inst_sp,
    };

    //-------------------------------------------------------------------------

    typedef std::vector<ELightParams> List;

    //-------------------------------------------------------------------------

    /*!
    * \details Constructor default.
    */
    XpObjLib ELightParams();

    /*!
     * \details Constructor init from Id.
     * \param [in] id
     */
    XpObjLib explicit ELightParams(eId id);

    XpObjLib ~ELightParams() = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator ==(const ELightParams & other) const;
    XpObjLib bool operator ==(eId id) const;

    XpObjLib bool operator !=(const ELightParams & other) const;
    XpObjLib bool operator !=(eId id) const;

    //-------------------------------------------------------------------------

    /*!
     * \details Makes from string which is used in the UI.
     * \param [in] name
     */
    XpObjLib static ELightParams fromUiString(const char * name);

    /*!
     * \details Makes from string which is used in the obj files.
     * \param [in] attrName
     */
    XpObjLib static ELightParams fromString(const char * attrName);

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
