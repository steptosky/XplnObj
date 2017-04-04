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

#include "xpln/common/Color.h"
#include "sts/string/StringConverters.h"
#include "sts/utilities/Compare.h"
#include "converters/StringStream.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	Color::Color()
		: Color(0.0, 0.0, 0.0, 1.0) { }

	Color::Color(float inRed, float inGreen, float inBlue, float inAlpha) {
		mColor[0] = inRed;
		mColor[1] = inGreen;
		mColor[2] = inBlue;
		mColor[3] = inAlpha;
	}

	Color::Color(const Color & p) {
		*this = p;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Operators *////////////////////////////////////////////
	/**************************************************************************************************/

	Color & Color::operator=(const Color & p) {
		setRed(p.red());
		setGreen(p.green());
		setBlue(p.blue());
		setAlpha(p.alpha());
		return *this;
	}

	bool Color::operator==(const Color & c) const {
		return (sts::isEqual(mColor[0], c.mColor[0]) &&
				sts::isEqual(mColor[1], c.mColor[1]) &&
				sts::isEqual(mColor[2], c.mColor[2]) &&
				sts::isEqual(mColor[3], c.mColor[3]));
	}

	bool Color::operator!=(const Color & c) const {
		return (sts::isNotEqual(mColor[0], c.mColor[0]) ||
				sts::isNotEqual(mColor[1], c.mColor[1]) ||
				sts::isNotEqual(mColor[2], c.mColor[2]) ||
				sts::isNotEqual(mColor[3], c.mColor[3]));
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	float Color::red() const {
		return mColor[0];
	}

	float Color::green() const {
		return mColor[1];
	}

	float Color::blue() const {
		return mColor[2];
	}

	float Color::alpha() const {
		return mColor[3];
	}

	void Color::setRed(float inValue) {
		mColor[0] = inValue;
	}

	void Color::setGreen(float inValue) {
		mColor[1] = inValue;
	}

	void Color::setBlue(float inValue) {
		mColor[2] = inValue;
	}

	void Color::setAlpha(float inValue) {
		mColor[3] = inValue;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	std::string Color::toString(uint8_t precision /*= 4*/) const {
		StringStream outStr(precision);
		outStr << red() << " " << green() << " " << blue() << " " << alpha();
		return outStr.str();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
