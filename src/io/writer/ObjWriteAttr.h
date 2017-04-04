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

#include <cstdint>
#include <string>
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/attributes/AttrSet.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	class AbstractWriter;
	class ObjMesh;
	class ObjAbstract;

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	class ObjWriteAttr {

		ObjWriteAttr(const ObjWriteAttr &) = delete;
		ObjWriteAttr & operator =(const ObjWriteAttr &) = delete;

	public:

		ObjWriteAttr() = default;
		~ObjWriteAttr() = default;

		XpObjLib void write(AbstractWriter * inWriter, const ObjAbstract * inObj);
		XpObjLib void reset();
		XpObjLib size_t count() const;

	private:

		void writeAttributes(const AttrSet & inObj);
		void writeBool(bool currVal, uint32_t inFlag, const char * inOn, const char * inOff);

		AbstractWriter * mIWriter = nullptr;
		size_t mCounter = 0;
		uint32_t mFlags = 0;

		AttrLightLevel mPrevAttrLightLevel;
		AttrPolyOffset mPrevAttrPolyOffset;
		AttrBlend mPrevAttrBlend;
		AttrShiny mPrevAttrShiny;
		AttrHard mPrevAttrHard;
		AttrCockpit mPrevAttrCockpit;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
