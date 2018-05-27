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

#include "xpln/obj/manipulators/AttrManipWrap.h"
#include "xpln/enums/EManipulator.h"
#include "sts/string/StringUtils.h"
#include "sts/utilities/Compare.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	AttrManipWrap::AttrManipWrap()
		: AttrManipBase(EManipulator(EManipulator::wrap)) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrManipWrap::setDown(float val) {
		mDown = val;
	}

	void AttrManipWrap::setHold(float val) {
		mHold = val;
	}

	void AttrManipWrap::setMinimum(float val) {
		mMin = val;
	}

	void AttrManipWrap::setMaximum(float val) {
		mMax = val;
	}

	float AttrManipWrap::down() const {
		return mDown;
	}

	float AttrManipWrap::hold() const {
		return mHold;
	}

	float AttrManipWrap::minimum() const {
		return mMin;
	}

	float AttrManipWrap::maximum() const {
		return mMax;
	}

	void AttrManipWrap::setDataref(const std::string & val) {
		mDataref = val;
	}

	const std::string & AttrManipWrap::dataref() const {
		return mDataref;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool AttrManipWrap::equals(const AttrManipBase * manip) const {
		if (!manip)
			return false;

		if (!AttrManipBase::equals(manip))
			return false;

		const AttrManipWrap * right = dynamic_cast<const AttrManipWrap*>(manip);
		if (!right)
			return false;

		const AttrManipWheel * rightWheel = static_cast<const AttrManipWheel*>(right);
		if (*static_cast<const AttrManipWheel*>(this) != *rightWheel)
			return false;

		return (sts::isEqual(mDown, right->mDown) &&
				sts::isEqual(mHold, right->mHold) &&
				sts::isEqual(mMin, right->mMin) &&
				sts::isEqual(mMax, right->mMax) &&
				sts::isEqual(mDataref, right->mDataref));
	}

	AttrManipBase * AttrManipWrap::clone() const {
		return new AttrManipWrap(*this);
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
