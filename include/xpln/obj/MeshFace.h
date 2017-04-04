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

namespace xobj {

	/**********************************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************************************************************/

	/*!
	 * \details Representation Face of the mesh object
	 * \ingroup Objects
	 */
	class MeshFace {
	public:

		typedef size_t value_type;

		MeshFace() = default;

		MeshFace(value_type inV0, value_type inV1, value_type inV2)
			: pV0(inV0),
			pV1(inV1),
			pV2(inV2) {}

		//--------------------------------------------------

		bool operator==(const MeshFace & inOther) const {
			return pV0 == inOther.pV0 &&
					pV1 == inOther.pV1 &&
					pV2 == inOther.pV2;
		}

		bool operator!=(const MeshFace & inOther) const {
			return !this->operator==(inOther);
		}

		//--------------------------------------------------

		value_type pV0 = 0;
		value_type pV1 = 0;
		value_type pV2 = 0;

		//--------------------------------------------------
	};

	/**********************************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************************************************************/
}
