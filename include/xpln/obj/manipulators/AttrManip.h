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

#include <variant>

#include "AttrManipAxisKnob.h"
#include "AttrManipAxisSwitchLeftRight.h"
#include "AttrManipAxisSwitchUpDown.h"
#include "AttrManipCmd.h"
#include "AttrManipCmdAxis.h"
#include "AttrManipCmdKnob.h"
#include "AttrManipCmdKnob2.h"
#include "AttrManipCmdSwitchLeftRight.h"
#include "AttrManipCmdSwitchLeftRight2.h"
#include "AttrManipCmdSwitchUpDown.h"
#include "AttrManipCmdSwitchUpDown2.h"
#include "AttrManipDelta.h"
#include "AttrManipDragAxis.h"
#include "AttrManipDragAxisPix.h"
#include "AttrManipDragRotate.h"
#include "AttrManipDragXy.h"
#include "AttrManipNone.h"
#include "AttrManipNoop.h"
#include "AttrManipPanel.h"
#include "AttrManipPush.h"
#include "AttrManipRadio.h"
#include "AttrManipToggle.h"
#include "AttrManipWrap.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Base type for all manipulators.
 * \ingroup Manipulators
 */
typedef std::variant<AttrManipAxisKnob,
                     AttrManipAxisSwitchLeftRight,
                     AttrManipAxisSwitchUpDown,
                     AttrManipCmd,
                     AttrManipCmdAxis,
                     AttrManipCmdKnob,
                     AttrManipCmdKnob2,
                     AttrManipCmdSwitchLeftRight,
                     AttrManipCmdSwitchLeftRight2,
                     AttrManipCmdSwitchUpDown,
                     AttrManipCmdSwitchUpDown2,
                     AttrManipDelta,
                     AttrManipDragAxis,
                     AttrManipDragAxisPix,
                     AttrManipDragRotate,
                     AttrManipDragXy,
                     AttrManipNone,
                     AttrManipNoop,
                     AttrManipPanel,
                     AttrManipPush,
                     AttrManipRadio,
                     AttrManipToggle,
                     AttrManipWrap> AttrManip;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
