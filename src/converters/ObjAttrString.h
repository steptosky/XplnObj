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

#include <string>
#include "xpln/Export.h"

/*
* Why this functions are not the methods of the corresponding classes?
* For simplify the library interface.
*/

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class AttrBlend;
class AttrHard;
class AttrDrapedLayerGroup;
class AttrLayerGroup;
class AttrLightLevel;
class AttrDrapedLod;
class AttrPolyOffset;
class AttrShiny;
class AttrSlungLoadWeight;
class AttrSpecular;
class AttrTint;
class AttrWetDry;
class AttrSlopeLimit;
class AttrCockpitRegion;
class AttrCockpit;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

XpObjLib std::string toObjGlobString(const AttrBlend & globAttr);
XpObjLib std::string toObjGlobString(const AttrLayerGroup & globAttr);
XpObjLib std::string toObjGlobString(const AttrDrapedLayerGroup & globAttr);
XpObjLib std::string toObjGlobString(const AttrDrapedLod & globAttr);
XpObjLib std::string toObjGlobString(const AttrSlungLoadWeight & globAttr);
XpObjLib std::string toObjGlobString(const AttrSpecular & globAttr);
XpObjLib std::string toObjGlobString(const AttrTint & globAttr);
XpObjLib std::string toObjGlobString(const AttrWetDry & globAttr);
XpObjLib std::string toObjGlobString(const AttrSlopeLimit & globAttr);
XpObjLib std::string toObjGlobString(const AttrCockpitRegion & globAttr);

XpObjLib std::string toObjString(const AttrBlend & attr);
XpObjLib std::string toObjString(const AttrHard & attr);
XpObjLib std::string toObjString(const AttrLightLevel & attr);
XpObjLib std::string toObjString(const AttrPolyOffset & attr);
XpObjLib std::string toObjString(const AttrShiny & attr);
XpObjLib std::string toObjString(const AttrCockpit & attr);

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
