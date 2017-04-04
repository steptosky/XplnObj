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

#pragma once

#include <stdint.h>
#include <string>
#include "xpln/XplnObjExport.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details Color (red, green, blue, alpha)
	 */
	class XpObjLib Color {
	public:

		Color();
		Color(float inRed, float inGreen, float inBlue, float inAlpha = 1.0f);
		Color(const Color & p);
		~Color() = default;

		//-------------------------------------------------------------------------

		/*! Operator copy */
		Color & operator =(const Color & p);

		bool operator ==(const Color & c) const;
		bool operator !=(const Color & c) const;

		//-------------------------------------------------------------------------

		float red() const;
		float green() const;
		float blue() const;
		float alpha() const;

		void setRed(float inValue);
		void setGreen(float inValue);
		void setBlue(float inValue);
		void setAlpha(float inValue);

		void setValues(float inRed, float inGreen, float inBlue, float inAlpha) {
			setRed(inRed);
			setGreen(inGreen);
			setBlue(inBlue);
			setAlpha(inAlpha);
		}

		//-------------------------------------------------------------------------

		std::string toString(uint8_t precision = 4) const;

	private:

		float mColor[4];

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
