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

namespace xobj {

	/**************************************************************************************************/
	//////////////////////////////////////////* Static area *///////////////////////////////////////////
	/**************************************************************************************************/

	AttrHard::AttrHard(ESurface surface, bool deck)
		: mESurface(surface),
		mIsDeck(deck),
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

	void AttrHard::setEnabled(bool state) {
		mIsEnabled = state;
	}

	bool AttrHard::operator==(const AttrHard & other) const {
		return (mIsEnabled == other.mIsEnabled &&
				mIsDeck == other.mIsDeck &&
				mESurface == other.mESurface);
	}

	bool AttrHard::operator!=(const AttrHard & other) const {
		return !operator==(other);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrHard::setESurface(const ESurface & surface, bool deck) {
		mIsEnabled = true;
		mESurface = surface;
		mIsDeck = deck;
	}

	const ESurface & AttrHard::surface() const {
		return mESurface;
	}

	bool AttrHard::isDeck() const {
		return mIsDeck;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
