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

#include "Transform.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details Representation of the LOD object
	 * \note This class should not be created outside the library.
	 * \ingroup Objects
	 */
	class ObjLodGroup {

		ObjLodGroup(const ObjLodGroup &/*inCopy*/) = delete;
		ObjLodGroup & operator =(const ObjLodGroup &/*inCopy*/) = delete;

	protected:

		XpObjLib ObjLodGroup();

	public:

		virtual ~ObjLodGroup() = default;

		//--------------------------------------------------------

		XpObjLib void setNearVal(float val);
		XpObjLib void setFarVal(float val);

		XpObjLib float nearVal() const;
		XpObjLib float farVal() const;

		//--------------------------------------------------------

		XpObjLib void setObjectName(const std::string & inName);
		XpObjLib const std::string & objectName() const;

		//--------------------------------------------------------

		/*! \copydoc ObjAbstract::transform */
		XpObjLib Transform & transform();

		/*! \copydoc ObjAbstract::transform */
		XpObjLib const Transform & transform() const;

		//--------------------------------------------------------

	private:

		Transform mObjTransform;
		std::string mName;
		float mNear;
		float mFar;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/
}
