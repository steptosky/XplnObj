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

#include "xpln/obj/attributes/AttrCockpit.h"
#include "common/AttributeNames.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrCockpit::operator==(const AttrCockpit & other) const {
    return mType == other.mType &&
           mDevName == other.mDevName &&
           mDevBus == other.mDevBus &&
           mDevLighting == other.mDevLighting &&
           mDevAutoAdjust == other.mDevAutoAdjust;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::string AttrCockpit::objDisableStr() {
    return ATTR_NO_COCKPIT;
}

std::string AttrCockpit::objStr() const {
    if (type() == cockpit) {
        return ATTR_COCKPIT;
    }
    StringStream outStr;
    if (type() == region_1) {
        outStr << ATTR_COCKPIT_REGION << " " << "0";
    }
    else if (type() == region_2) {
        outStr << ATTR_COCKPIT_REGION << " " << "1";
    }
    else if (type() == region_3) {
        outStr << ATTR_COCKPIT_REGION << " " << "2";
    }
    else if (type() == region_4) {
        outStr << ATTR_COCKPIT_REGION << " " << "3";
    }
    else if (type() == cockpit_device) {
        outStr << ATTR_COCKPIT_DEVICE
                << " " << name()
                << " " << bus()
                << " " << lightingChannel()
                << " " << autoAdjust();
    }
    return outStr.str();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
