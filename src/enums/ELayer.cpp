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

#include "xpln/enums/ELayer.h"
#include "common/ArrayLength.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

ELayer::List ELayer::mList;

namespace ELayersData {

    struct Data {
        const char * mUi;
        const char * mAttr;
        ELayer::eId mId;

        Data(const char * attr, const char * ui, ELayer::eId id)
            : mUi(ui),
              mAttr(attr),
              mId(id) {}
    };

    const Data gList[] = {
        /*  0 */ Data(TOTEXT(none), "none", ELayer::none),
        /*  1 */ Data(TOTEXT(terrain), "Terrain", ELayer::terrain),
        /*  2 */ Data(TOTEXT(beaches), "Beaches", ELayer::beaches),
        /*  3 */ Data(TOTEXT(shoulders), "Shoulders", ELayer::shoulders),
        /*  4 */ Data(TOTEXT(taxiways), "Taxiways", ELayer::taxiways),
        /*  5 */ Data(TOTEXT(runways), "Runways", ELayer::ranways),
        /*  6 */ Data(TOTEXT(markings), "Markings", ELayer::markings),
        /*  7 */ Data(TOTEXT(airports), "Airports", ELayer::airports),
        /*  8 */ Data(TOTEXT(roads), "Roads", ELayer::roads),
        /*  9 */ Data(TOTEXT(objects), "Objects", ELayer::objects),
        /* 10 */ Data(TOTEXT(light_objects), "Light objects", ELayer::light_objects),
        /* 11 */ Data(TOTEXT(cars), "Cars", ELayer::cars)
    };
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ELayer::ELayer()
    : mId(none) {}

ELayer::ELayer(eId id)
    : mId(id) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool ELayer::operator==(const ELayer & other) const {
    return mId == other.mId;
}

bool ELayer::operator==(eId id) const {
    return mId == id;
}

bool ELayer::operator!=(const ELayer & other) const {
    return mId != other.mId;
}

bool ELayer::operator!=(eId id) const {
    return mId != id;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ELayer ELayer::fromUiString(const char * name) {
    if (name) {
        for (size_t i = 0; i < ARRAY_LENGTH(ELayersData::gList); ++i) {
            if (strcmp(name, ELayersData::gList[i].mUi) == 0) {
                return ELayer(ELayersData::gList[i].mId);
            }
        }
        LError << TOTEXT(ELayer) << " Does not contain ui name: \"" << name << "\"";
    }
    return ELayer();
}

ELayer ELayer::fromString(const char * attrName) {
    if (attrName) {
        for (size_t i = 0; i < ARRAY_LENGTH(ELayersData::gList); ++i) {
            if (strcmp(attrName, ELayersData::gList[i].mAttr) == 0) {
                return ELayer(ELayersData::gList[i].mId);
            }
        }
        LError << TOTEXT(ELayer) << " Does not contain attribute name: \"" << attrName << "\"";
    }
    return ELayer();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ELayer::makeList(List & outList) {
    if (!outList.empty())
        return;
    for (size_t i = 0; i < ARRAY_LENGTH(ELayersData::gList); ++i) {
        outList.emplace_back(ELayer(ELayersData::gList[i].mId));
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ELayer::isValid() const {
    return mId != none;
}

ELayer::eId ELayer::id() const {
    return mId;
}

const char * ELayer::toString() const {
    return ELayersData::gList[static_cast<size_t>(mId)].mAttr;
}

const char * ELayer::toUiString() const {
    return ELayersData::gList[static_cast<size_t>(mId)].mUi;
}

const ELayer::List & ELayer::list() {
    makeList(mList);
    return mList;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
