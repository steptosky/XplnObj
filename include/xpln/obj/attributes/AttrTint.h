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
	 * \details GLOBAL_tint
	 * \ingroup Attributes
	 */
	class AttrTint {
	public:

		/*!
		 * \details Constructor default.
		 * \note Makes the disabled attribute.
		 */
		XpObjLib AttrTint();

		/*!
		 * \details Constructor init.
		 * \note Makes the enabled attribute.
		 * \param inAlbedoRatio 
		 * \param inEmissiveRatio 
		 */
		XpObjLib AttrTint(float inAlbedoRatio, float inEmissiveRatio);

		~AttrTint() = default;

		//-------------------------------------------------------------------------

		/*!
		 * \details Check whether the attribute is enabled. 
		 * \note All class's seters will enable this attribute.
		 */
		XpObjLib operator bool() const;

		/*!
		 * \details Sets the attribute enabled/desabled.
		 * \note All class's seters will enable this attribute.
		 * \param inState 
		 */
		XpObjLib void setEnabled(bool inState);

		//-------------------------------------------------------------------------

		XpObjLib bool operator==(const AttrTint & inRight) const;
		XpObjLib bool operator!=(const AttrTint & inRight) const;

		//-------------------------------------------------------------------------

		XpObjLib void set(float inAlbedoRatio, float inEmissiveRatio);
		XpObjLib void setAlbedo(float inRatio);
		XpObjLib void setEmissive(float inRatio);

		XpObjLib float albedo() const;
		XpObjLib float emissive() const;

		//-------------------------------------------------------------------------

	private:

		float mAlbedo;
		float mEmissive;
		bool mIsEnabled : 1;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
