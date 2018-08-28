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

#include <vector>
#include <cstdint>
#include "xpln/XplnObjExport.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details Names of the named lights
	 * \ingroup Enumerations
	 */
	class ECursor {
	public:

		/*!
		 * \note It is NOT guaranteed that the existing indexes will be constant when new data is added.
		 *       So you can consider it when you design your serialization solution. You can use obj string (toString()).
		 */
		enum eId : int32_t {
			none = 0,
			four_arrows,
			hand,
			button,
			rotate_small,
			rotate_small_left,
			rotate_small_right,
			rotate_medium,
			rotate_medium_left,
			rotate_medium_right,
			rotate_large,
			rotate_large_left,
			rotate_large_right,
			up_down,
			down,
			up,
			left_right,
			right,
			left,
			arrow,
		};

		//-------------------------------------------------------------------------

		typedef std::vector<ECursor> List;

		//-------------------------------------------------------------------------

		/*!
		 * \details Constructor default.
		 */
		XpObjLib ECursor();

		/*!
		 * \details Constructor init from Id.
		 * \param [in] id
		 */
		XpObjLib explicit ECursor(eId id);

		~ECursor() = default;

		//-------------------------------------------------------------------------

		XpObjLib bool operator ==(const ECursor & other) const;
		XpObjLib bool operator ==(eId id) const;

		XpObjLib bool operator !=(const ECursor & other) const;
		XpObjLib bool operator !=(eId id) const;

		//-------------------------------------------------------------------------

		/*!
		 * \details Makes from string which is used in the ui.
		 * \param [in] name
		 */
		XpObjLib static ECursor fromUiString(const char * name);

		/*!
		 * \details Makes from string which is used in the obj files.
		 * \param [in] attrName
		 */
		XpObjLib static ECursor fromString(const char * attrName);

		//-------------------------------------------------------------------------

		/*!
		 * \details Checks whether this instance is valid.
		 * \return True if valid otherwise false.
		 */
		XpObjLib bool isValid() const;

		/*!
		 * \details Gets id.
		 */
		XpObjLib eId id() const;

		/*!
		 * \details Gets string which is used in obj files.
		 */
		XpObjLib const char * toString() const;

		/*!
		 * \details Gets string which can be used for UI.
		 */
		XpObjLib const char * toUiString() const;

		/*!
		 * \details Gets list of all id.
		 */
		XpObjLib static const List & list();

		//-------------------------------------------------------------------------

	private:

		eId mId;
		static void makeList(List &);
		static List mList;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
