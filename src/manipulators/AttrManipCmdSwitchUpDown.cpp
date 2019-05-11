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

#include "sts/utilities/Compare.h"
#include "converters/StringStream.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h"
#include "xpln/enums/EManipulator.h"
#include "common/AttributeNames.h"
#include "io/writer/AbstractWriter.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AttrManipCmdSwitchUpDown::AttrManipCmdSwitchUpDown()
    : AttrManipBase(EManipulator(EManipulator::command_switch_ud)) { }

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

const std::string & AttrManipCmdSwitchUpDown::cmdPositive() const {
    return mPosCommand;
}

void AttrManipCmdSwitchUpDown::setCmdPositive(const std::string & val) {
    mPosCommand = val;
}

const std::string & AttrManipCmdSwitchUpDown::cmdNegative() const {
    return mNegCommand;
}

void AttrManipCmdSwitchUpDown::setCmdNegative(const std::string & val) {
    mNegCommand = val;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool AttrManipCmdSwitchUpDown::equals(const AttrManipBase * manip) const {
    if (!manip)
        return false;

    if (!AttrManipBase::equals(manip))
        return false;

    const auto * right = dynamic_cast<const AttrManipCmdSwitchUpDown*>(manip);
    if (!right)
        return false;

    return (sts::isEqual(mPosCommand, right->mPosCommand) &&
            sts::isEqual(mNegCommand, right->mNegCommand));
}

AttrManipBase * AttrManipCmdSwitchUpDown::clone() const {
    return new AttrManipCmdSwitchUpDown(*this);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::size_t AttrManipCmdSwitchUpDown::printObj(AbstractWriter & writer) const {
    StringStream outStr;
    outStr << ATTR_MANIP_COMMAND_SWITCH_UP_DOWN;
    outStr << " " << cursor().toString();
    outStr << " " << writer.actualCommand(cmdPositive());
    outStr << " " << writer.actualCommand(cmdNegative());
    outStr << " " << toolTip();
    writer.writeLine(outStr.str());
    return 1;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
