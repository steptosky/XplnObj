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

#include <cstddef>
#include "xpln/XplnObjExport.h"

namespace xobj {

	class ObjReader;
	class ObjWriter;

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details Statistic of the 'obj' Reader/Writer.
	 */
	class IOStatistic {
	public:

		/*! \details Constructor default. */
		XpObjLib IOStatistic();

		//-----------------------------------

		size_t pMeshVerticesCount; //!< Mesh vertices count
		size_t pMeshFacesCount; //!< Mesh faces count (triangles)
		size_t pLineVerticesCount; //!< Line vertices count

		size_t pMeshObjCount; //!< Mesh objects count
		size_t pLineObjCount; //!< Line objects count
		size_t pLightObjPointCount; //!< Light named objects count
		size_t pLightObjNamedCount; //!< Light named objects count
		size_t pLightObjCustomCount; //!< Light custom objects count
		size_t pLightObjParamCount; //!< Light param objects count
		size_t pLightObjSpillCustCount; //!< Light spill custom objects count
		size_t pDummyObjCount; //!< Dummy objects count

		size_t pGlobAttrCount; //!< Global attributes count
		size_t pTrisManipCount; //!< Object manipulators count
		size_t pTrisAttrCount; //!< Object attributes count

		size_t pAnimAttrCount; //!< Animations rotation count

		//------------------------------------------------------------

		XpObjLib void reset();

		//------------------------------------------------------------

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
