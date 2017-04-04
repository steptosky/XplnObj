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

#include "xpln/obj/attributes/AttrLightLevel.h"
#include "sts/utilities/Compare.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	AttrLightLevel::AttrLightLevel(float inVal1, float inVal2, const std::string & inDataRef)
		: mVal1(inVal1),
		mVal2(inVal2),
		mDataref(inDataRef),
		mIsEnabled(true) { }

	AttrLightLevel::AttrLightLevel()
		: mVal1(0.0f),
		mVal2(1.0f),
		mDataref("none"),
		mIsEnabled(false) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Operators *////////////////////////////////////////////
	/**************************************************************************************************/

	AttrLightLevel::operator bool() const {
		return mIsEnabled;
	}

	void AttrLightLevel::setEnabled(bool inState) {
		mIsEnabled = inState;
	}

	bool AttrLightLevel::operator==(const AttrLightLevel & inRight) const {
		return (mIsEnabled == inRight.mIsEnabled &&
				mDataref == inRight.mDataref &&
				sts::isEqual(mVal1, inRight.mVal1, 0.01f) &&
				sts::isEqual(mVal2, inRight.mVal2, 0.01f));
	}

	bool AttrLightLevel::operator!=(const AttrLightLevel & inRight) const {
		return !operator==(inRight);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrLightLevel::setVal1(float inVal) {
		mIsEnabled = true;
		mVal1 = inVal;
	}

	void AttrLightLevel::setVal2(float inVal) {
		mIsEnabled = true;
		mVal2 = inVal;
	}

	void AttrLightLevel::setDataref(const std::string & inDataRef) {
		mIsEnabled = true;
		mDataref = inDataRef;
	}

	float AttrLightLevel::val1() const {
		return mVal1;
	}

	float AttrLightLevel::val2() const {
		return mVal2;
	}

	const std::string & AttrLightLevel::dataref() const {
		return mDataref;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
