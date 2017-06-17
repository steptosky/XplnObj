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

#pragma once

#include <string>
#include "xpln/XplnObjExport.h"

/*
* Why this functions are not the methods of the corresponding classes?
* For simplify the library interface.
*/

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	class AttrManipBase;
	class AttrManipNone;
	class AttrManipCmd;
	class AttrManipCmdAxis;
	class AttrManipDelta;
	class AttrManipDragAxis;
	class AttrManipDragAxisPix;
	class AttrManipDragXy;
	class AttrManipNoop;
	class AttrManipPanel;
	class AttrManipPush;
	class AttrManipRadio;
	class AttrManipToggle;
	class AttrManipWrap;
	class AttrManipAxisKnob;
	class AttrManipAxisSwitchLeftRight;
	class AttrManipAxisSwitchUpDown;
	class AttrManipCmdKnob;
	class AttrManipCmdSwitchLeftRight;
	class AttrManipCmdSwitchUpDown;
	class AttrManipWheel;

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	XpObjLib std::string toObjString(const AttrManipBase * inVal);
	XpObjLib std::string toObjString(const AttrManipNone & inVal);
	XpObjLib std::string toObjString(const AttrManipAxisKnob & inVal);
	XpObjLib std::string toObjString(const AttrManipAxisSwitchLeftRight & inVal);
	XpObjLib std::string toObjString(const AttrManipAxisSwitchUpDown & inVal);
	XpObjLib std::string toObjString(const AttrManipCmd & inVal);
	XpObjLib std::string toObjString(const AttrManipCmdAxis & inVal);
	XpObjLib std::string toObjString(const AttrManipCmdKnob & inVal);
	XpObjLib std::string toObjString(const AttrManipCmdSwitchLeftRight & inVal);
	XpObjLib std::string toObjString(const AttrManipCmdSwitchUpDown & inVal);
	XpObjLib std::string toObjString(const AttrManipDelta & inVal);
	XpObjLib std::string toObjString(const AttrManipDragAxis & inVal);
	XpObjLib std::string toObjString(const AttrManipDragAxisPix & inVal);
	XpObjLib std::string toObjString(const AttrManipDragXy & inVal);
	XpObjLib std::string toObjString(const AttrManipNoop & inVal);
	XpObjLib std::string toObjString(const AttrManipPanel & inVal);
	XpObjLib std::string toObjString(const AttrManipPush & inVal);
	XpObjLib std::string toObjString(const AttrManipRadio & inVal);
	XpObjLib std::string toObjString(const AttrManipToggle & inVal);
	XpObjLib std::string toObjString(const AttrManipWrap & inVal);
	XpObjLib std::string toObjString(const AttrManipWheel & inVal);

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
