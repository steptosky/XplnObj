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

#include "xpln/obj/attributes/AttrHard.h"
#include <algorithm>

namespace xobj {

	/**************************************************************************************************/
	//////////////////////////////////////////* Static area *///////////////////////////////////////////
	/**************************************************************************************************/

	AttrHard::AttrHard(ESurface inSurface, bool inDeck)
		: mESurface(inSurface),
		mIsDeck(inDeck),
		mIsEnabled(true) { }

	AttrHard::AttrHard()
		: mESurface(ESurface::eId::none),
		mIsDeck(false),
		mIsEnabled(false) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Operators *////////////////////////////////////////////
	/**************************************************************************************************/

	AttrHard::operator bool() const {
		return mIsEnabled;
	}

	void AttrHard::setEnabled(bool inState) {
		mIsEnabled = inState;
	}

	bool AttrHard::operator==(const AttrHard & inRight) const {
		return (mIsEnabled == inRight.mIsEnabled &&
				mIsDeck == inRight.mIsDeck &&
				mESurface == inRight.mESurface);
	}

	bool AttrHard::operator!=(const AttrHard & inRight) const {
		return !operator==(inRight);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrHard::setESurface(const ESurface & inVal, bool inDeck /*= false*/) {
		mIsEnabled = true;
		mESurface = inVal;
		mIsDeck = inDeck;
	}

	const xobj::ESurface & AttrHard::surface() const {
		return mESurface;
	}

	bool AttrHard::isDeck() const {
		return mIsDeck;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
