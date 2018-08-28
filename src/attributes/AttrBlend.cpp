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

#include "xpln/obj/attributes/AttrBlend.h"
#include <algorithm>
#include "sts/utilities/Compare.h"

namespace xobj {

	/**************************************************************************************************/
	//////////////////////////////////////////* Static area *///////////////////////////////////////////
	/**************************************************************************************************/

	AttrBlend::AttrBlend(eType type, float ratio)
		: mBlending(type),
		mRatio(ratio),
		mIsEnabled(true) {}

	AttrBlend::AttrBlend()
		: mBlending(blend),
		mRatio(0.5f),
		mIsEnabled(false) {}

	/**************************************************************************************************/
	///////////////////////////////////////////* Operators *////////////////////////////////////////////
	/**************************************************************************************************/

	AttrBlend::operator bool() const {
		return mIsEnabled;
	}

	void AttrBlend::setEnabled(bool state) {
		mIsEnabled = state;
	}

	bool AttrBlend::operator==(const AttrBlend & other) const {
		return (mIsEnabled == other.mIsEnabled &&
				sts::isEqual(mRatio, other.mRatio, 0.01f) &&
				mBlending == other.mBlending);
	}

	bool AttrBlend::operator!=(const AttrBlend & other) const {
		return !operator==(other);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	AttrBlend::eType AttrBlend::type() const {
		return mBlending;
	}

	void AttrBlend::setRatio(float inRatio) {
		inRatio = std::min(inRatio, 1.0f);
		inRatio = std::max(inRatio, 0.0f);
		mIsEnabled = true;
		mRatio = inRatio;
	}

	float AttrBlend::ratio() const {
		return mRatio;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
