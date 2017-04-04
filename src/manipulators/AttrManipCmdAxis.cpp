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

#include "xpln/obj/manipulators/AttrManipCmdAxis.h"
#include "xpln/enums//EManipulator.h"
#include "sts/string/StringConverters.h"
#include "sts/utilities/Compare.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	AttrManipCmdAxis::AttrManipCmdAxis()
		: AttrManipBase(EManipulator(EManipulator::command_axis)) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrManipCmdAxis::setX(float val) {
		mX = val;
	}

	void AttrManipCmdAxis::setY(float val) {
		mY = val;
	}

	void AttrManipCmdAxis::setZ(float val) {
		mZ = val;
	}

	float AttrManipCmdAxis::x() const {
		return mX;
	}

	float AttrManipCmdAxis::y() const {
		return mY;
	}

	float AttrManipCmdAxis::z() const {
		return mZ;
	}

	const std::string & AttrManipCmdAxis::cmdPositive() const {
		return mPosCommand;
	}

	void AttrManipCmdAxis::setCmdPositive(const std::string & val) {
		mPosCommand = val;
	}

	const std::string & AttrManipCmdAxis::cmdNegative() const {
		return mNegCommand;
	}

	void AttrManipCmdAxis::setCmdNegative(const std::string & val) {
		mNegCommand = val;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool AttrManipCmdAxis::equals(const AttrManipBase * inMainp) const {
		if (!inMainp)
			return false;

		if (!AttrManipBase::equals(inMainp))
			return false;

		const AttrManipCmdAxis * right = dynamic_cast<const AttrManipCmdAxis*>(inMainp);
		if (!right)
			return false;

		return (sts::isEqual(mX, right->mX) &&
				sts::isEqual(mY, right->mY) &&
				sts::isEqual(mZ, right->mZ) &&
				sts::isEqual(mPosCommand, right->mPosCommand) &&
				sts::isEqual(mNegCommand, right->mNegCommand));
	}

	AttrManipBase * AttrManipCmdAxis::clone() const {
		return new AttrManipCmdAxis(*this);
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
