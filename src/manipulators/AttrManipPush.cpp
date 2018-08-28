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

#include "xpln/obj/manipulators/AttrManipPush.h"
#include "xpln/enums//EManipulator.h"
#include "sts/string/StringConverters.h"
#include "sts/utilities/Compare.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	AttrManipPush::AttrManipPush()
		: AttrManipBase(EManipulator(EManipulator::push)) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrManipPush::setDown(float val) {
		mDown = val;
	}

	void AttrManipPush::setUp(float val) {
		mUp = val;
	}

	float AttrManipPush::down() const {
		return mDown;
	}

	float AttrManipPush::up() const {
		return mUp;
	}

	const std::string & AttrManipPush::dataref() const {
		return mDataref;
	}

	void AttrManipPush::setDataref(const std::string & val) {
		mDataref = val;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool AttrManipPush::equals(const AttrManipBase * manip) const {
		if (!manip)
			return false;

		if (!AttrManipBase::equals(manip))
			return false;

		const AttrManipPush * right = dynamic_cast<const AttrManipPush*>(manip);
		if (!right)
			return false;

		const AttrManipWheel * rightWheel = static_cast<const AttrManipWheel*>(right);
		if (*static_cast<const AttrManipWheel*>(this) != *rightWheel)
			return false;

		return (sts::isEqual(mDown, right->mDown) &&
				sts::isEqual(mUp, right->mUp) &&
				sts::isEqual(mDataref, right->mDataref));
	}

	AttrManipBase * AttrManipPush::clone() const {
		return new AttrManipPush(*this);
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
