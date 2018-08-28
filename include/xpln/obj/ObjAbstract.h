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

#include <string>
#include "xpln/XplnObjExport.h"
#include "xpln/enums/eObjectType.h"
#include "xpln/common/TMatrix.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	class Transform;
	class AttrSet;

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details Base class for all 'obj' objects
	 * \ingroup Objects
	 */
	class ObjAbstract {

		friend Transform;
		ObjAbstract & operator =(const ObjAbstract &) = delete;

	protected:

		//-----------------------------------------------------

		XpObjLib ObjAbstract();

		/*!
		 * \details Constructor copy.
		 * \note It does not copy the transform linkage.
		 */
		XpObjLib ObjAbstract(const ObjAbstract & copy);

		//-----------------------------------------------------

	public:

		//-----------------------------------------------------

		XpObjLib virtual ~ObjAbstract();

		//--------------------------------------------------------

		XpObjLib virtual eObjectType objType() const;

		//--------------------------------------------------------

		/*
		 * \details Access to the object transformation node.
		 * \return Nullptr if the object doesn't have a transformation node, otherwise pointer to the linked transformation node.
		 */
		XpObjLib Transform * transform();

		/*
		 * \details Access to the object transformation node.
		 * \return Nullptr if the object doesn't have a transformation node, otherwise pointer to the linked transformation node.
		 */
		XpObjLib const Transform * transform() const;

		//--------------------------------------------------------

		XpObjLib void setObjectName(const std::string & name);
		XpObjLib const std::string & objectName() const;

		//--------------------------------------------------------

		/*!
		 * \details Applies specified transformation matrix to the object.
		 * \param [in] tm transform matrix.
		 * \param [in] useParity \see \link TMatrix::parity \endlink
		 */
		virtual void applyTransform(const TMatrix & tm, const bool useParity = false) = 0;

		/*!
		 * \return Cloned object.
		 */
		virtual ObjAbstract * clone() const = 0;

		//--------------------------------------------------------

	private:

		Transform * mObjTransform = nullptr;
		std::string mName;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
