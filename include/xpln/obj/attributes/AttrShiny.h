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

#include "xpln/XplnObjExport.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details ATTR_shiny_rat
	 * \ingroup Attributes
	 */
	class AttrShiny {
	public:

		//-------------------------------------------------------------------------

		/*!
		 * \details Constructor default.
		 * \note Makes the disabled attribute.
		 */
		XpObjLib AttrShiny();

		/*!
		 * \details Constructor init.
		 * \note Makes the enabled attribute.
		 * \param [in] ratio 
		 */
		XpObjLib AttrShiny(float ratio);

		~AttrShiny() = default;

		//-------------------------------------------------------------------------

		/*!
		 * \details Check whether the attribute is enabled. 
		 * \note All class's setters will enable this attribute.
		 */
		XpObjLib operator bool() const;

		/*!
		 * \details Sets the attribute enabled/disabled.
		 * \note All class's setters will enable this attribute.
		 * \param [in] state 
		 */
		XpObjLib void setEnabled(bool state);

		//-------------------------------------------------------------------------

		XpObjLib bool operator==(const AttrShiny & other) const;
		XpObjLib bool operator!=(const AttrShiny & other) const;

		//-------------------------------------------------------------------------

		XpObjLib void setRatio(float ratio);
		XpObjLib float ratio() const;

		//-------------------------------------------------------------------------

	private:

		float mRatio;
		bool mIsEnabled : 1;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
