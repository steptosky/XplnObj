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

#include "ObjWriteAttr.h"
#include "../../common/Logger.h"

#include <cassert>
#include "AbstractWriter.h"
#include "common/AttributeNames.h"
#include "converters/ObjAttrString.h"
#include "xpln/obj/ObjMesh.h"

namespace xobj {

	/**************************************************************************************************/
	//////////////////////////////////////////* Static area *///////////////////////////////////////////
	/**************************************************************************************************/

	class Flags {
	public:

		enum eAttrTypes : uint32_t {
			no_draw = 1 << 1,
			draped = 1 << 2,
			no_shadow = 1 << 3,
			solid_camera = 1 << 4,
		};

		static void removeFlag(uint32_t & inOutFlags, const uint32_t inFlag) {
			inOutFlags -= (inOutFlags & inFlag);
		}

		static void addFlag(uint32_t & inOutFlags, const uint32_t inFlag) {
			inOutFlags |= inFlag;
		}

		static bool hasFlag(const uint32_t inFlags, const uint32_t inFlag) {
			return (inFlags & inFlag) != 0;
		}
	};

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void ObjWriteAttr::reset() {
		mFlags = 0;
		mCounter = 0;
	}

	size_t ObjWriteAttr::count() const {
		return mCounter;
	}

	void ObjWriteAttr::write(AbstractWriter * inWriter, const ObjAbstract * inObj) {
		assert(inObj);
		mIWriter = inWriter;
		if (inObj->objType() != OBJ_MESH) {
			return;
		}
		writeAttributes(static_cast<const ObjMesh*>(inObj)->pAttr);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	class AttrWriter {
	public:
		template<typename T>
		static void writeAttr(AbstractWriter * inWriter, const T & inAttr, T & inOutPrevAttr, const char * inOffStr, size_t & outCounter) {
			if (!inAttr) {
				if (inOutPrevAttr) {
					inWriter->printLine(inOffStr);
					++outCounter;
					inOutPrevAttr = T();
				}
			}
			else {
				if (!inOutPrevAttr) {
					inWriter->printLine(toObjString(inAttr));
					++outCounter;
					inOutPrevAttr = inAttr;
					return;
				}

				if (inOutPrevAttr != inAttr) {
					inWriter->printLine(toObjString(inAttr));
					++outCounter;
					inOutPrevAttr = inAttr;
					return;
				}

				inOutPrevAttr = inAttr;
			}
		}
	};

	void ObjWriteAttr::writeBool(bool currVal, uint32_t inFlag, const char * inOn, const char * inOff) {
		if (!currVal) {
			if (Flags::hasFlag(mFlags, inFlag)) {
				mIWriter->printLine(inOff);
				++mCounter;
				Flags::removeFlag(mFlags, inFlag);
			}
		}
		else {
			if (!Flags::hasFlag(mFlags, inFlag)) {
				mIWriter->printLine(inOn);
				++mCounter;
				Flags::addFlag(mFlags, inFlag);
			}
		}
	}

	void ObjWriteAttr::writeAttributes(const AttrSet & inObj) {
		writeBool(inObj.isDraped(), Flags::draped, ATTR_DRAPED, ATTR_NO_DRAPED);
		writeBool(inObj.isSolidForCamera(), Flags::solid_camera, ATTR_SOLID_CAMERA, ATTR_NO_SOLID_CAMERA);
		writeBool(!inObj.isDraw(), Flags::no_draw, ATTR_DRAW_DISABLE, ATTR_DRAW_ENABLE);
		writeBool(!inObj.isCastShadow(), Flags::no_shadow, ATTR_NO_SHADOW, ATTR_SHADOW);

		AttrWriter::writeAttr<AttrHard>(mIWriter, inObj.hard(), mPrevAttrHard, ATTR_NO_HARD, mCounter);
		AttrWriter::writeAttr<AttrShiny>(mIWriter, inObj.shiny(), mPrevAttrShiny, toObjString(AttrShiny()).c_str(), mCounter);
		AttrWriter::writeAttr<AttrBlend>(mIWriter, inObj.blend(), mPrevAttrBlend, toObjString(AttrBlend()).c_str(), mCounter);
		AttrWriter::writeAttr<AttrPolyOffset>(mIWriter, inObj.polyOffset(), mPrevAttrPolyOffset, toObjString(AttrPolyOffset(0.0f)).c_str(), mCounter);
		AttrWriter::writeAttr<AttrLightLevel>(mIWriter, inObj.lightLevel(), mPrevAttrLightLevel, ATTR_LIGHT_LEVEL_RESET, mCounter);
		AttrWriter::writeAttr<AttrCockpit>(mIWriter, inObj.cockpit(), mPrevAttrCockpit, ATTR_NO_COCKPIT, mCounter);
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
