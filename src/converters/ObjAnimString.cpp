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

#include "converters/StringStream.h"
#include "common/Logger.h"
#include "ObjAnimString.h"
#include "common/AttributeNames.h"
#include "xpln/obj/animation/AnimVisibilityKey.h"
#include "xpln/obj/animation/AnimTrans.h"
#include "xpln/obj/animation/AnimRotate.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void printObj(const AnimVisibilityKey & key, AbstractWriter & writer) {
    StringStream outStr;
    switch (key.mType) {
        case AnimVisibilityKey::SHOW:
            outStr << ATTR_ANIM_SHOW;
            break;
        case AnimVisibilityKey::HIDE:
            outStr << ATTR_ANIM_HIDE;
            break;
        case AnimVisibilityKey::UNDEFINED:
        default:
            LError << TOTEXT(AnimVisibilityKey) << " has undefined type";
            return;
    }
    outStr << " " << key.mValue1
            << " " << key.mValue2
            << " " << writer.actualDataref(key.mDrf);
    writer.writeLine(outStr.str());
}

bool fromObjString(AnimVisibilityKey & outVal, ObjReadParser & parser) {
    AnimVisibilityKey::eType type = AnimVisibilityKey::UNDEFINED;
    if (parser.isMatch(ATTR_ANIM_HIDE)) {
        type = AnimVisibilityKey::HIDE;
    }
    else if (parser.isMatch(ATTR_ANIM_SHOW)) {
        type = AnimVisibilityKey::SHOW;
    }
    if (type == AnimVisibilityKey::UNDEFINED) {
        return false;
    }
    parser.skipSpace();
    outVal.mValue1 = parser.extractFloat();
    parser.skipSpace();
    outVal.mValue2 = parser.extractFloat();
    parser.skipSpace();
    outVal.mDrf = parser.extractWord();
    return true;
}

//-------------------------------------------------------------------------

void printObj(const AnimTransKey & key, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_TRANS_KEY
            << " " << key.mDrfValue
            << " " << key.mPosition.toString(PRECISION);
    writer.writeLine(outStr.str());
}

bool fromObjString(AnimTransKey & outVal, ObjReadParser & parser) {
    if (!parser.isMatch(ATTR_TRANS_KEY)) {
        return false;
    }
    parser.skipSpace();
    outVal.mDrfValue = parser.extractFloat();
    parser.skipSpace();
    outVal.mPosition.x = parser.extractFloat();
    parser.skipSpace();
    outVal.mPosition.y = parser.extractFloat();
    parser.skipSpace();
    outVal.mPosition.z = parser.extractFloat();
    return true;
}

//-------------------------------------------------------------------------

void printObj(const AnimRotateKey & key, AbstractWriter & writer) {
    StringStream outStr;
    outStr << ATTR_ROTATE_KEY
            << " " << key.mDrfValue
            << " " << key.mAngleDegrees;
    writer.writeLine(outStr.str());
}

bool fromObjString(AnimRotateKey & outVal, ObjReadParser & parser) {
    if (!parser.isMatch(ATTR_ROTATE_KEY)) {
        return false;
    }
    parser.skipSpace();
    outVal.mDrfValue = parser.extractFloat();
    parser.skipSpace();
    outVal.mAngleDegrees = parser.extractFloat();
    return true;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
