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

#include "xpln/obj/attributes/AttrTint.h"
#include "sts/utilities/Compare.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	AttrTint::AttrTint(float inAlbedoRatio, float inEmissiveRatio)
		: mAlbedo(inAlbedoRatio),
		mEmissive(inEmissiveRatio),
		mIsEnabled(true) { }

	AttrTint::AttrTint()
		: mAlbedo(0.0f),
		mEmissive(0.0f),
		mIsEnabled(false) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Operators *////////////////////////////////////////////
	/**************************************************************************************************/

	AttrTint::operator bool() const {
		return mIsEnabled;
	}

	void AttrTint::setEnabled(bool inState) {
		mIsEnabled = inState;
	}

	bool AttrTint::operator==(const AttrTint & inRight) const {
		return (mIsEnabled == inRight.mIsEnabled &&
				sts::isEqual(mAlbedo, inRight.mAlbedo, 0.01f) &&
				sts::isEqual(mEmissive, inRight.mEmissive, 0.01f));
	}

	bool AttrTint::operator!=(const AttrTint & inRight) const {
		return !operator==(inRight);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrTint::setAlbedo(float inRatio) {
		mAlbedo = inRatio;
		mIsEnabled = true;
	}

	void AttrTint::setEmissive(float inRatio) {
		mEmissive = inRatio;
		mIsEnabled = true;
	}

	float AttrTint::albedo() const {
		return mAlbedo;
	}

	float AttrTint::emissive() const {
		return mEmissive;
	}

	void AttrTint::set(float inAlbedoRatio, float inEmissiveRatio) {
		mAlbedo = inAlbedoRatio;
		mEmissive = inEmissiveRatio;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
