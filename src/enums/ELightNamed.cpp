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

#include "xpln/enums/ELightNamed.h"
#include <utility>
#include "common/Logger.h"
#include "common/ArrayLength.h"

namespace xobj {

	/**************************************************************************************************/
	//////////////////////////////////////////* Static area *///////////////////////////////////////////
	/**************************************************************************************************/

	ELightNamed::List ELightNamed::mList;

	namespace EObjLightNamedData {

		struct Data {
			const char * mUi;
			const char * mAttr;
			ELightNamed::eId mId;

			Data(const char * attr, const char * ui, ELightNamed::eId id)
				: mUi(ui),
				mAttr(attr),
				mId(id) {}
		};

		const Data gList[] = {
				/* 00 */ Data(TOTEXT(none), "none", ELightNamed::none),
				/* 01 */ Data(TOTEXT(airplane_nav_left), "Airplane nav left", ELightNamed::airplane_nav_left),
				/* 02 */ Data(TOTEXT(airplane_nav_right), "Airplane nav right", ELightNamed::airplane_nav_right),
				/* 03 */ Data(TOTEXT(airplane_nav_tail), "Airplane nav tail", ELightNamed::airplane_nav_tail),
				/* 04 */ Data(TOTEXT(airplane_beacon), "Airplane beacon", ELightNamed::airplane_beacon),
				/* 05 */ Data(TOTEXT(airplane_taxi), "Airplane taxi", ELightNamed::airplane_taxi),
				/* 06 */ Data(TOTEXT(airplane_landing), "Airplane landing", ELightNamed::airplane_landing),
				/* 07 */ Data(TOTEXT(airplane_strobe), "Airplane strobe", ELightNamed::airplane_strobe),
				/* 08 */ Data(TOTEXT(taillight), "Tail-light", ELightNamed::taillight),
				/* 09 */ Data(TOTEXT(headlight), "Head-light", ELightNamed::headlight),
				/* 10 */ Data(TOTEXT(carrier_meatball1), "Carrier meatball1", ELightNamed::carrier_meatball1),
				/* 11 */ Data(TOTEXT(carrier_meatball2), "Carrier meatball2", ELightNamed::carrier_meatball2),
				/* 12 */ Data(TOTEXT(carrier_meatball3), "Carrier meatball3", ELightNamed::carrier_meatball3),
				/* 13 */ Data(TOTEXT(carrier_meatball4), "Carrier meatball4", ELightNamed::carrier_meatball4),
				/* 14 */ Data(TOTEXT(carrier_meatball5), "Carrier meatball5", ELightNamed::carrier_meatball5),
				/* 15 */ Data(TOTEXT(carrier_deck_blue_e), "Carrier deck blue e", ELightNamed::carrier_deck_blue_e),
				/* 16 */ Data(TOTEXT(carrier_deck_blue_n), "Carrier deck blue n", ELightNamed::carrier_deck_blue_n),
				/* 17 */ Data(TOTEXT(carrier_deck_blue_w), "Carrier deck blue w", ELightNamed::carrier_deck_blue_w),
				/* 18 */ Data(TOTEXT(carrier_deck_blue_s), "Carrier deck blue s", ELightNamed::carrier_deck_blue_s),
				/* 19 */ Data(TOTEXT(carrier_thresh_white), "Carrier thresh white", ELightNamed::carrier_thresh_white),
				/* 20 */ Data(TOTEXT(carrier_edge_white), "Carrier edge white", ELightNamed::carrier_edge_white),
				/* 21 */ Data(TOTEXT(carrier_center_white), "Carrier center white", ELightNamed::carrier_center_white),
				/* 22 */ Data(TOTEXT(carrier_foul_line_white), "Carrier oul ine white", ELightNamed::carrier_foul_line_white),
				/* 23 */ Data(TOTEXT(carrier_mast_strobe), "Carrier mast strobe", ELightNamed::carrier_mast_strobe),
				/* 24 */ Data(TOTEXT(carrier_waveoff), "Carrier waveoff", ELightNamed::carrier_waveoff),
				/* 25 */ Data(TOTEXT(carrier_datum), "Carrier datum", ELightNamed::carrier_datum),
				/* 26 */ Data(TOTEXT(carrier_foul_line_red), "Carrier foul line red", ELightNamed::carrier_foul_line_red),
				/* 27 */ Data(TOTEXT(carrier_pitch_lights), "Carrier pitch lights", ELightNamed::carrier_pitch_lights),
				/* 28 */ Data(TOTEXT(ship_mast_powered), "Ship mast powered", ELightNamed::ship_mast_powered),
				/* 29 */ Data(TOTEXT(ship_mast_grn), "Ship mast grn", ELightNamed::ship_mast_grn),
				/* 30 */ Data(TOTEXT(ship_mast_obs), "Ship mast obs", ELightNamed::ship_mast_obs),
				/* 31 */ Data(TOTEXT(ship_nav_right), "Ship nav right", ELightNamed::ship_nav_right),
				/* 32 */ Data(TOTEXT(ship_nav_left), "Ship nav left", ELightNamed::ship_nav_left),
				/* 33 */ Data(TOTEXT(ship_nav_tail), "Ship nav tail", ELightNamed::ship_nav_tail),
				/* 34 */ Data(TOTEXT(obs_red_night), "Obs red night", ELightNamed::obs_red_night),
				/* 35 */ Data(TOTEXT(obs_red_day), "Obs red day", ELightNamed::obs_red_day),
				/* 36 */ Data(TOTEXT(obs_strobe_night), "Obs strobe night", ELightNamed::obs_strobe_night),
				/* 37 */ Data(TOTEXT(obs_strobe_day), "Obs strobe day", ELightNamed::obs_strobe_day),
				/* 38 */ Data(TOTEXT(frigate_deck_green), "Frigate deck green", ELightNamed::frigate_deck_green),
				/* 39 */ Data(TOTEXT(frigate_SGSI_hi), "Frigate SGSI hi", ELightNamed::frigate_SGSI_hi),
				/* 40 */ Data(TOTEXT(frigate_SGSI_on), "Frigate SGSI on", ELightNamed::frigate_SGSI_on),
				/* 41 */ Data(TOTEXT(frigate_SGSI_lo), "Frigate SGSI lo", ELightNamed::frigate_SGSI_lo),
				/* 42 */ Data(TOTEXT(oilrig_deck_blue), "Oilrig deck blue", ELightNamed::oilrig_deck_blue),
				/* 43 */ Data(TOTEXT(town_tiny_light_omni), "Town tiny light omni", ELightNamed::town_tiny_light_omni),
				/* 44 */ Data(TOTEXT(town_tiny_light_60), "Town tiny light 60", ELightNamed::town_tiny_light_60),
				/* 45 */ Data(TOTEXT(town_tiny_light_90), "Town tiny light 90", ELightNamed::town_tiny_light_90),
				/* 46 */ Data(TOTEXT(town_tiny_light_150), "Town tiny light 150", ELightNamed::town_tiny_light_150),
				/* 47 */ Data(TOTEXT(town_tiny_light_180), "Town tiny light 180", ELightNamed::town_tiny_light_180),
				/* 48 */ Data(TOTEXT(town_tiny_light_220), "Town tiny light 220", ELightNamed::town_tiny_light_220),
				/* 49 */ Data(TOTEXT(town_tiny_light_280), "Town tiny light 280", ELightNamed::town_tiny_light_280),
				/* 50 */ Data(TOTEXT(town_tiny_light_330), "Town tiny light 330", ELightNamed::town_tiny_light_330),
				/* 51 */ Data(TOTEXT(town_tiny_light_350), "Town tiny light 350", ELightNamed::town_tiny_light_350),
				/* 52 */ Data(TOTEXT(town_light_omni), "Town light omni", ELightNamed::town_light_omni),
				/* 53 */ Data(TOTEXT(town_light_60), "Town light 60", ELightNamed::town_light_60),
				/* 54 */ Data(TOTEXT(town_light_90), "Town light 90", ELightNamed::town_light_90),
				/* 55 */ Data(TOTEXT(town_light_150), "Town light 150", ELightNamed::town_light_150),
				/* 56 */ Data(TOTEXT(town_light_180), "Town light 180", ELightNamed::town_light_180),
				/* 57 */ Data(TOTEXT(town_light_220), "Town light 220", ELightNamed::town_light_220),
				/* 58 */ Data(TOTEXT(town_light_280), "Town light 280", ELightNamed::town_light_280),
				/* 59 */ Data(TOTEXT(town_light_330), "Town light 330", ELightNamed::town_light_330),
				/* 60 */ Data(TOTEXT(town_light_350), "Town light 350", ELightNamed::town_light_350),
			};

	}

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	ELightNamed::ELightNamed()
		: mId(none) {}

	ELightNamed::ELightNamed(eId inId)
		: mId(inId) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Operators *////////////////////////////////////////////
	/**************************************************************************************************/

	bool ELightNamed::operator==(const ELightNamed & inRight) const {
		return mId == inRight.mId;
	}

	bool ELightNamed::operator==(eId inId) const {
		return mId == inId;
	}

	bool ELightNamed::operator!=(const ELightNamed & inRight) const {
		return mId != inRight.mId;
	}

	bool ELightNamed::operator!=(eId inId) const {
		return mId != inId;
	}

	/**************************************************************************************************/
	//////////////////////////////////////////* Functions */////////////////////////////////////////////
	/**************************************************************************************************/

	ELightNamed ELightNamed::fromUiString(const char * inName) {
		if (inName) {
			for (size_t i = 0; i < ARRAY_LENGTH(EObjLightNamedData::gList); ++i) {
				if (strcmp(inName, EObjLightNamedData::gList[i].mUi) == 0) {
					return ELightNamed(EObjLightNamedData::gList[i].mId);
				}
			}
			LError << TOTEXT(ELightNamed) << " Does not contain ui name: \"" << inName << "\"";
		}
		return ELightNamed();
	}

	ELightNamed ELightNamed::fromString(const char * inAttrName) {
		if (inAttrName) {
			for (size_t i = 0; i < ARRAY_LENGTH(EObjLightNamedData::gList); ++i) {
				if (strcmp(inAttrName, EObjLightNamedData::gList[i].mAttr) == 0) {
					return ELightNamed(EObjLightNamedData::gList[i].mId);
				}
			}
			LError << TOTEXT(ELightNamed) << " Does not contain attribute name: \"" << inAttrName << "\"";
		}
		return ELightNamed();
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ELightNamed::makeList(List & ouList) {
		if (!ouList.empty())
			return;
		for (size_t i = 0; i < ARRAY_LENGTH(EObjLightNamedData::gList); ++i) {
			ouList.emplace_back(ELightNamed(EObjLightNamedData::gList[i].mId));
		}
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool ELightNamed::isValid() const {
		return mId != none;
	}

	ELightNamed::eId ELightNamed::id() const {
		return mId;
	}

	const char * ELightNamed::toUiString() const {
		return EObjLightNamedData::gList[static_cast<size_t>(mId)].mUi;
	}

	const char * ELightNamed::toString() const {
		return EObjLightNamedData::gList[static_cast<size_t>(mId)].mAttr;
	}

	const ELightNamed::List & ELightNamed::list() {
		makeList(mList);
		return mList;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
