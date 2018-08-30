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

#include "xpln/enums/ESurface.h"
#include "common/ArrayLength.h"
#include "common/Logger.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

ESurface::List ESurface::mList;

namespace ESurfacesData {

    struct Data {
        const char * mUi;
        const char * mAttr;
        ESurface::eId mId;

        Data(const char * attr, const char * ui, const ESurface::eId id)
            : mUi(ui),
              mAttr(attr),
              mId(id) {}
    };

    const Data gList[] = {
        /* 00 */ Data(TOTEXT(none), "none", ESurface::none),
        /* 01 */ Data(TOTEXT(water), "Water", ESurface::water),
        /* 02 */ Data(TOTEXT(concrete), "Concrete", ESurface::concrete),
        /* 03 */ Data(TOTEXT(asphalt), "Asphalt", ESurface::asphalt),
        /* 04 */ Data(TOTEXT(grass), "Grass", ESurface::grass),
        /* 05 */ Data(TOTEXT(dirt), "Dirt", ESurface::dirt),
        /* 06 */ Data(TOTEXT(gravel), "Gravel", ESurface::gravel),
        /* 07 */ Data(TOTEXT(lakebad), "Lakebad", ESurface::lakebad),
        /* 08 */ Data(TOTEXT(snow), "Snow", ESurface::snow),
        /* 09 */ Data(TOTEXT(shoulder), "Shoulder", ESurface::shoulder),
        /* 10 */ Data(TOTEXT(blastpad), "Blastpad", ESurface::blastpad)
    };
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ESurface::ESurface()
    : mId(none) { }

ESurface::ESurface(const eId id)
    : mId(id) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool ESurface::operator==(const ESurface & other) const {
    return mId == other.mId;
}

bool ESurface::operator==(const eId id) const {
    return mId == id;
}

bool ESurface::operator!=(const ESurface & other) const {
    return mId != other.mId;
}

bool ESurface::operator!=(const eId id) const {
    return mId != id;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ESurface ESurface::fromUiString(const char * name) {
    if (name) {
        for (size_t i = 0; i < ARRAY_LENGTH(ESurfacesData::gList); ++i) {
            if (strcmp(name, ESurfacesData::gList[i].mUi) == 0) {
                return ESurface(ESurfacesData::gList[i].mId);
            }
        }
        LError << TOTEXT(ESurface) << " Does not contain ui name: \"" << name << "\"";
    }
    return ESurface();
}

ESurface ESurface::fromString(const char * attrName) {
    if (attrName) {
        for (size_t i = 0; i < ARRAY_LENGTH(ESurfacesData::gList); ++i) {
            if (strcmp(attrName, ESurfacesData::gList[i].mAttr) == 0) {
                return ESurface(ESurfacesData::gList[i].mId);
            }
        }
        LError << TOTEXT(ESurface) << " Does not contain attribute name: \"" << attrName << "\"";
    }
    return ESurface();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ESurface::makeList(List & outList) {
    if (!outList.empty())
        return;
    for (size_t i = 0; i < ARRAY_LENGTH(ESurfacesData::gList); ++i) {
        outList.emplace_back(ESurface(ESurfacesData::gList[i].mId));
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ESurface::isValid() const {
    return mId != none;
}

ESurface::eId ESurface::id() const {
    return mId;
}

const char * ESurface::toString() const {
    return ESurfacesData::gList[static_cast<size_t>(mId)].mAttr;
}

const char * ESurface::toUiString() const {
    return ESurfacesData::gList[static_cast<size_t>(mId)].mUi;
}

const ESurface::List & ESurface::list() {
    makeList(mList);
    return mList;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
