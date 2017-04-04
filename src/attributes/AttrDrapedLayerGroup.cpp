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

#include "xpln/obj/attributes/AttrDrapedLayerGroup.h"
#include <algorithm>

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	AttrDrapedLayerGroup::AttrDrapedLayerGroup(ELayer inLayer, int32_t inOffset)
		: mOffset(static_cast<uint8_t>(inOffset)),
		mLayer(inLayer),
		mIsEnabled(true) { }

	AttrDrapedLayerGroup::AttrDrapedLayerGroup()
		: mOffset(0),
		mLayer(ELayer(ELayer::objects)),
		mIsEnabled(false) { }

	/**************************************************************************************************/
	///////////////////////////////////////////* Operators *////////////////////////////////////////////
	/**************************************************************************************************/

	AttrDrapedLayerGroup::operator bool() const {
		return mIsEnabled;
	}

	void AttrDrapedLayerGroup::setEnabled(bool inState) {
		mIsEnabled = inState;
	}

	bool AttrDrapedLayerGroup::operator==(const AttrDrapedLayerGroup & inRight) const {
		return (mIsEnabled == inRight.mIsEnabled && mOffset == inRight.mOffset && mLayer == inRight.mLayer);
	}

	bool AttrDrapedLayerGroup::operator!=(const AttrDrapedLayerGroup & inRight) const {
		return !operator==(inRight);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void AttrDrapedLayerGroup::setOffset(int32_t inOffset) {
		inOffset = std::min(inOffset, 5);
		inOffset = std::max(inOffset, -5);
		mOffset = static_cast<int8_t>(inOffset);
		mIsEnabled = true;
	}

	int32_t AttrDrapedLayerGroup::offset() const {
		return static_cast<int32_t>(mOffset);
	}

	void AttrDrapedLayerGroup::setLayer(ELayer inLayer) {
		mLayer = inLayer;
		mIsEnabled = true;
	}

	ELayer AttrDrapedLayerGroup::layer() const {
		return mLayer;
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
