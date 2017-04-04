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

#include "xpln/obj/manipulators/AttrManipCmd.h"
#include "xpln/enums//EManipulator.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	AttrManipCmd::AttrManipCmd()
		: AttrManipBase(EManipulator(EManipulator::command)) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrManipCmd::setCommand(const std::string & inCmd) {
		mCommand = inCmd.empty() ? "none" : inCmd;
	}

	const std::string & AttrManipCmd::command() const {
		return mCommand;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool AttrManipCmd::equals(const AttrManipBase * inMainp) const {
		if (!inMainp)
			return false;

		if (!AttrManipBase::equals(inMainp))
			return false;

		const AttrManipCmd * right = dynamic_cast<const AttrManipCmd*>(inMainp);
		if (!right)
			return false;

		return mCommand == right->mCommand;
	}

	AttrManipBase * AttrManipCmd::clone() const {
		return new AttrManipCmd(*this);
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
