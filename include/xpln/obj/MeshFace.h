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

		MeshFace(value_type v0, value_type v1, value_type v2)
			: pV0(v0),
			pV1(v1),
			pV2(v2) {}

		//--------------------------------------------------

		bool operator==(const MeshFace & other) const {
			return pV0 == other.pV0 &&
					pV1 == other.pV1 &&
					pV2 == other.pV2;
		}

		bool operator!=(const MeshFace & other) const {
			return !this->operator==(other);
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
