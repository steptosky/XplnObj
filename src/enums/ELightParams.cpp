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

#include "stdafx.h"
#include <cstring>

#include "xpln/enums/ELightParams.h"
#include "common/ArrayLength.h"
#include "common/Logger.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

ELightParams::List ELightParams::mList;

namespace EObjLightParamsData {

    struct Data {
        const char * mUi;
        const char * mAttr;
        ELightParams::eId mId;

        Data(const char * attr, const char * ui, const ELightParams::eId id)
            : mUi(ui),
              mAttr(attr),
              mId(id) {}
    };

    const Data gList[] = {
        /* 00 */ Data(TOTEXT(none), "none", ELightParams::none),
        /* 01 */ Data(TOTEXT(light_params_custom), "Custom", ELightParams::light_params_custom),

        /* 02 */ Data(TOTEXT(full_custom_halo), "Full custom halo", ELightParams::full_custom_halo),
        /* 03 */ Data(TOTEXT(full_custom_halo_night), "Full custom halo-night", ELightParams::full_custom_halo_night),

        /* 04 */ Data(TOTEXT(airplane_landing_core), "Airplane landing core", ELightParams::airplane_landing_core),
        /* 05 */ Data(TOTEXT(airplane_landing_glow), "Airplane landing glow", ELightParams::airplane_landing_glow),
        /* 06 */ Data(TOTEXT(airplane_landing_flare), "Airplane landing flare", ELightParams::airplane_landing_flare),
        /* 07 */ Data(TOTEXT(airplane_landing_sp), "Airplane landing sp", ELightParams::airplane_landing_sp),

        /* 08 */ Data(TOTEXT(airplane_taxi_core), "Airplane taxi core", ELightParams::airplane_taxi_core),
        /* 09 */ Data(TOTEXT(airplane_taxi_glow), "Airplane taxi glow", ELightParams::airplane_taxi_glow),
        /* 10 */ Data(TOTEXT(airplane_taxi_flare), "Airplane taxi flare", ELightParams::airplane_taxi_flare),
        /* 11 */ Data(TOTEXT(airplane_taxi_sp), "Airplane taxi sp", ELightParams::airplane_taxi_sp),

        /* 12 */ Data(TOTEXT(airplane_spot_core), "Airplane spot core", ELightParams::airplane_spot_core),
        /* 13 */ Data(TOTEXT(airplane_spot_glow), "Airplane spot glow", ELightParams::airplane_spot_glow),
        /* 14 */ Data(TOTEXT(airplane_spot_flare), "Airplane spot flare", ELightParams::airplane_spot_flare),
        /* 15 */ Data(TOTEXT(airplane_spot_sp), "Airplane spot sp", ELightParams::airplane_spot_sp),

        /* 16 */ Data(TOTEXT(airplane_generic_core), "Airplane generic_core", ELightParams::airplane_generic_core),
        /* 17 */ Data(TOTEXT(airplane_generic_glow), "Airplane generic_glow", ELightParams::airplane_generic_glow),
        /* 18 */ Data(TOTEXT(airplane_generic_flare), "Airplane generic flare", ELightParams::airplane_generic_flare),
        /* 19 */ Data(TOTEXT(airplane_generic_sp), "Airplane generic sp", ELightParams::airplane_generic_sp),

        /* 20 */ Data(TOTEXT(airplane_beacon_rotate), "Airplane beacon rotate", ELightParams::airplane_beacon_rotate),
        /* 21 */
        Data(TOTEXT(airplane_beacon_rotate_sp), "Airplane beacon rotate sp", ELightParams::airplane_beacon_rotate_sp),

        /* 22 */ Data(TOTEXT(airplane_beacon_strobe), "Airplane beacon strobe", ELightParams::airplane_beacon_strobe),
        /* 23 */
        Data(TOTEXT(airplane_beacon_strobe_sp), "Airplane beacon strobe sp", ELightParams::airplane_beacon_strobe_sp),

        /* 24 */ Data(TOTEXT(airplane_strobe_omni), "Airplane strobe omni", ELightParams::airplane_strobe_omni),
        /* 25 */ Data(TOTEXT(airplane_strobe_dir), "Airplane strobe dir", ELightParams::airplane_strobe_dir),
        /* 26 */ Data(TOTEXT(airplane_strobe_sp), "Airplane strobe sp", ELightParams::airplane_strobe_sp),

        /* 27 */ Data(TOTEXT(airplane_nav_tail_size), "Airplane nav tail size", ELightParams::airplane_nav_tail_size),
        /* 28 */ Data(TOTEXT(airplane_nav_left_size), "Airplane nav left size", ELightParams::airplane_nav_left_size),
        /* 29 */ Data(TOTEXT(airplane_nav_right_size), "Airplane nav right size", ELightParams::airplane_nav_right_size),
        /* 30 */ Data(TOTEXT(airplane_nav_sp), "Airplane nav sp", ELightParams::airplane_nav_sp),

        /* 31 */ Data(TOTEXT(airplane_panel_sp), "Airplane panel sp", ELightParams::airplane_panel_sp),
        /* 32 */ Data(TOTEXT(airplane_inst_sp), "Airplane inst sp", ELightParams::airplane_inst_sp),
    };
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ELightParams::ELightParams()
    : mId(none) {}

ELightParams::ELightParams(const eId id)
    : mId(id) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool ELightParams::operator==(const ELightParams & other) const {
    return mId == other.mId;
}

bool ELightParams::operator==(const eId id) const {
    return mId == id;
}

bool ELightParams::operator!=(const ELightParams & other) const {
    return mId != other.mId;
}

bool ELightParams::operator!=(const eId id) const {
    return mId != id;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ELightParams ELightParams::fromUiString(const char * name) {
    if (name) {
        for (size_t i = 0; i < ARRAY_LENGTH(EObjLightParamsData::gList); ++i) {
            if (strcmp(name, EObjLightParamsData::gList[i].mUi) == 0) {
                return ELightParams(EObjLightParamsData::gList[i].mId);
            }
        }
        LError << TOTEXT(ELightParams) << " Does not contain ui name: \"" << name << "\"";
    }
    return ELightParams();
}

ELightParams ELightParams::fromString(const char * attrName) {
    if (attrName) {
        for (size_t i = 0; i < ARRAY_LENGTH(EObjLightParamsData::gList); ++i) {
            if (strcmp(attrName, EObjLightParamsData::gList[i].mAttr) == 0) {
                return ELightParams(EObjLightParamsData::gList[i].mId);
            }
        }
        LError << TOTEXT(ELightParams) << " Does not contain attribute name: \"" << attrName << "\"";
    }
    return ELightParams();
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void ELightParams::makeList(List & ouList) {
    if (!ouList.empty())
        return;
    for (size_t i = 0; i < ARRAY_LENGTH(EObjLightParamsData::gList); ++i) {
        ouList.emplace_back(ELightParams(EObjLightParamsData::gList[i].mId));
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ELightParams::isValid() const {
    return mId != none;
}

ELightParams::eId ELightParams::id() const {
    return mId;
}

const char * ELightParams::toUiString() const {
    return EObjLightParamsData::gList[static_cast<size_t>(mId)].mUi;
}

const char * ELightParams::toString() const {
    return EObjLightParamsData::gList[static_cast<size_t>(mId)].mAttr;
}

const ELightParams::List & ELightParams::list() {
    makeList(mList);
    return mList;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
