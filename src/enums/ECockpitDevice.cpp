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

#include <cstring>

#include "xpln/enums/ECockpitDevice.h"
#include "common/ArrayLength.h"
#include "common/Logger.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

ECockpitDevice::List ECockpitDevice::mList;

namespace ECockpitDeviceData {

    struct Data {
        const char * mUi;
        const char * mAttr;
        ECockpitDevice::eId mId;

        Data(const char * attr, const char * ui, const ECockpitDevice::eId id)
            : mUi(ui),
              mAttr(attr),
              mId(id) {}
    };

    // WARNING !!! Indexes are coordinated with the enum values !!!
    const Data gList[] = {
        /* 00 */ Data(TOTEXT(none), "none", ECockpitDevice::none),
        /* 01 */ Data(TOTEXT(GNS430_1), "GNS430_1", ECockpitDevice::GNS430_1),
        /* 02 */ Data(TOTEXT(GNS430_2), "GNS430_2", ECockpitDevice::GNS430_2),
        /* 03 */ Data(TOTEXT(GNS530_1), "GNS530_1", ECockpitDevice::GNS530_1),
        /* 04 */ Data(TOTEXT(GNS530_2), "GNS530_2", ECockpitDevice::GNS530_2),
        /* 05 */ Data(TOTEXT(CDU739_1), "CDU739_1", ECockpitDevice::CDU739_1),
        /* 06 */ Data(TOTEXT(CDU739_2), "CDU739_2", ECockpitDevice::CDU739_2),
        /* 07 */ Data(TOTEXT(G1000_PFD1), "G1000_PFD1", ECockpitDevice::G1000_PFD1),
        /* 08 */ Data(TOTEXT(G1000_MFD), "G1000_MFD", ECockpitDevice::G1000_MFD),
        /* 09 */ Data(TOTEXT(G1000_PFD2), "G1000_PFD2", ECockpitDevice::G1000_PFD2),
    };
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ECockpitDevice::ECockpitDevice()
    : mId(none) { }

ECockpitDevice::ECockpitDevice(const eId id)
    : mId(id) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool ECockpitDevice::operator==(const ECockpitDevice & other) const {
    return mId == other.mId;
}

bool ECockpitDevice::operator==(const eId id) const {
    return mId == id;
}

bool ECockpitDevice::operator!=(const ECockpitDevice & other) const {
    return mId != other.mId;
}

bool ECockpitDevice::operator!=(const eId id) const {
    return mId != id;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ECockpitDevice ECockpitDevice::fromUiString(const char * name) {
    if (name) {
        for (size_t i = 0; i < ARRAY_LENGTH(ECockpitDeviceData::gList); ++i) {
            if (strcmp(name, ECockpitDeviceData::gList[i].mUi) == 0) {
                return ECockpitDevice(ECockpitDeviceData::gList[i].mId);
            }
        }
        LError << TOTEXT(ECockpitDevice) << " Does not contain ui name: \"" << name << "\"";
    }
    return ECockpitDevice();
}

ECockpitDevice ECockpitDevice::fromString(const char * attrName) {
    if (attrName) {
        for (size_t i = 0; i < ARRAY_LENGTH(ECockpitDeviceData::gList); ++i) {
            if (strcmp(attrName, ECockpitDeviceData::gList[i].mAttr) == 0) {
                return ECockpitDevice(ECockpitDeviceData::gList[i].mId);
            }
        }
        LError << TOTEXT(ECockpitDevice) << " Does not contain attribute name: \"" << attrName << "\"";
    }
    return ECockpitDevice();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ECockpitDevice::makeList(List & outList) {
    if (!outList.empty())
        return;
    for (size_t i = 0; i < ARRAY_LENGTH(ECockpitDeviceData::gList); ++i) {
        outList.emplace_back(ECockpitDevice(ECockpitDeviceData::gList[i].mId));
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ECockpitDevice::isValid() const {
    return mId != none;
}

ECockpitDevice::eId ECockpitDevice::id() const {
    return mId;
}

const char * ECockpitDevice::toString() const {
    return ECockpitDeviceData::gList[static_cast<size_t>(mId)].mAttr;
}

const char * ECockpitDevice::toUiString() const {
    return ECockpitDeviceData::gList[static_cast<size_t>(mId)].mUi;
}

const ECockpitDevice::List & ECockpitDevice::list() {
    makeList(mList);
    return mList;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
