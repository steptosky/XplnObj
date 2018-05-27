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

#include "xpln/enums/ECursor.h"
#include <utility>
#include "common/Logger.h"
#include "common/ArrayLength.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

ECursor::List ECursor::mList;

namespace EObjCursorsData {

    struct Data {
        const char * mUi;
        const char * mAttr;
        ECursor::eId mId;

        Data(const char * attr, const char * ui, ECursor::eId id)
            : mUi(ui),
              mAttr(attr),
              mId(id) {}
    };

    const Data gList[] = {
        /* 00 */ Data(TOTEXT(none), "none", ECursor::none),
        /* 01 */ Data(TOTEXT(four_arrows), "Four arrows", ECursor::four_arrows),
        /* 02 */ Data(TOTEXT(hand), "Hand", ECursor::hand),
        /* 03 */ Data(TOTEXT(button), "Button", ECursor::button),
        /* 04 */ Data(TOTEXT(rotate_small), "Rotate small", ECursor::rotate_small),
        /* 05 */ Data(TOTEXT(rotate_small_left), "Rotate small left", ECursor::rotate_small_left),
        /* 06 */ Data(TOTEXT(rotate_small_right), "Rotate small right", ECursor::rotate_small_right),
        /* 07 */ Data(TOTEXT(rotate_medium), "Rotate medium", ECursor::rotate_medium),
        /* 08 */ Data(TOTEXT(rotate_medium_left), "Rotate medium left", ECursor::rotate_medium_left),
        /* 09 */ Data(TOTEXT(rotate_medium_right), "Rotate medium right", ECursor::rotate_medium_right),
        /* 10 */ Data(TOTEXT(rotate_large), "Rotate large", ECursor::rotate_large),
        /* 11 */ Data(TOTEXT(rotate_large_left), "Rotate large left", ECursor::rotate_large_left),
        /* 12 */ Data(TOTEXT(rotate_large_right), "Rotate large right", ECursor::rotate_large_right),
        /* 13 */ Data(TOTEXT(up_down), "Up-Down", ECursor::up_down),
        /* 14 */ Data(TOTEXT(down), "Down", ECursor::down),
        /* 15 */ Data(TOTEXT(up), "Up", ECursor::up),
        /* 16 */ Data(TOTEXT(left_right), "Left-Right", ECursor::left_right),
        /* 17 */ Data(TOTEXT(right), "Right", ECursor::right),
        /* 18 */ Data(TOTEXT(left), "Left", ECursor::left),
        /* 19 */ Data(TOTEXT(arrow), "Arrow", ECursor::arrow),
    };
}

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ECursor::ECursor()
    : mId(none) { }

ECursor::ECursor(eId id)
    : mId(id) { }

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool ECursor::operator==(const ECursor & other) const {
    return mId == other.mId;
}

bool ECursor::operator==(eId id) const {
    return mId == id;
}

bool ECursor::operator!=(const ECursor & other) const {
    return mId != other.mId;
}

bool ECursor::operator!=(eId id) const {
    return mId != id;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ECursor ECursor::fromUiString(const char * name) {
    if (name) {
        for (size_t i = 0; i < ARRAY_LENGTH(EObjCursorsData::gList); ++i) {
            if (strcmp(name, EObjCursorsData::gList[i].mUi) == 0) {
                return ECursor(EObjCursorsData::gList[i].mId);
            }
        }
        LError << TOTEXT(ECursor) << " Does not contain ui name: \"" << name << "\"";
    }
    return ECursor();
}

ECursor ECursor::fromString(const char * attrName) {
    if (attrName) {
        for (size_t i = 0; i < ARRAY_LENGTH(EObjCursorsData::gList); ++i) {
            if (strcmp(attrName, EObjCursorsData::gList[i].mAttr) == 0) {
                return ECursor(EObjCursorsData::gList[i].mId);
            }
        }
        LError << TOTEXT(ECursor) << " Does not contain attribute name: \"" << attrName << "\"";
    }
    return ECursor();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ECursor::makeList(List & outList) {
    if (!outList.empty())
        return;
    for (size_t i = 0; i < ARRAY_LENGTH(EObjCursorsData::gList); ++i) {
        outList.emplace_back(ECursor(EObjCursorsData::gList[i].mId));
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ECursor::isValid() const {
    return mId != none;
}

ECursor::eId ECursor::id() const {
    return mId;
}

const char * ECursor::toString() const {
    return EObjCursorsData::gList[static_cast<size_t>(mId)].mAttr;
}

const char * ECursor::toUiString() const {
    return EObjCursorsData::gList[static_cast<size_t>(mId)].mUi;
}

const ECursor::List & ECursor::list() {
    makeList(mList);
    return mList;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
