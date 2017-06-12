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
#include "ObjWriteManip.h"

#include <cassert>
#include "AbstractWriter.h"
#include "common/AttributeNames.h"
#include "converters/ObjAttrString.h"
#include "xpln/obj/ObjMesh.h"
#include <functional>

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

	void ObjWriteAttr::write(AbstractWriter * writer, const ObjAbstract * obj) {
		assert(obj);
		mWriter = writer;
		if (obj->objType() != OBJ_MESH) {
			return;
		}
		writeAttributes(static_cast<const ObjMesh*>(obj)->pAttr);
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	class AttrWriter {
	public:
		template<typename T>
		static void writeAttr(AbstractWriter * writer, const T & attr, T & inOutActiveAttr, const char * OffStr, size_t & outCounter,
							std::function<void(const T &)> attrEnable = nullptr, std::function<void()> attrDisable = nullptr) {
			if (!attr) {
				if (inOutActiveAttr) {
					writer->printLine(OffStr);
					if (attrDisable) {
						attrDisable();
					}
					++outCounter;
					inOutActiveAttr = T();
				}
			}
			else {
				if (!inOutActiveAttr) {
					writer->printLine(toObjString(attr));
					if (attrEnable) {
						attrEnable(attr);
					}
					++outCounter;
					inOutActiveAttr = attr;
					return;
				}

				if (inOutActiveAttr != attr) {
					writer->printLine(toObjString(attr));
					if (attrEnable) {
						attrEnable(attr);
					}
					++outCounter;
					inOutActiveAttr = attr;
					return;
				}

				inOutActiveAttr = attr;
			}
		}
	};

	void ObjWriteAttr::writeBool(bool currVal, uint32_t flag, const char * attrOn, const char * attrOff) {
		if (!currVal) {
			if (Flags::hasFlag(mFlags, flag)) {
				mWriter->printLine(attrOff);
				Flags::removeFlag(mFlags, flag);
				++mCounter;
			}
		}
		else {
			if (!Flags::hasFlag(mFlags, flag)) {
				mWriter->printLine(attrOn);
				Flags::addFlag(mFlags, flag);
				++mCounter;
			}
		}
	}

	void ObjWriteAttr::writeAttributes(const AttrSet & obj) {

		std::function<void(const AttrCockpit &)> manipPanelEnabled = [&](const AttrCockpit & cockpit) {
			if (mManipWriter) {
				mManipWriter->setPanelEnabled(cockpit);
			}
		};
		std::function<void()> manipPanelDisabled = [&]() {
			if (mManipWriter) {
				mManipWriter->setPanelDisabled();
			}
		};

		//-------------------------------------------------------------------------

		writeBool(obj.isDraped(), Flags::draped, ATTR_DRAPED, ATTR_NO_DRAPED);
		writeBool(obj.isSolidForCamera(), Flags::solid_camera, ATTR_SOLID_CAMERA, ATTR_NO_SOLID_CAMERA);
		writeBool(!obj.isDraw(), Flags::no_draw, ATTR_DRAW_DISABLE, ATTR_DRAW_ENABLE);
		writeBool(!obj.isCastShadow(), Flags::no_shadow, ATTR_NO_SHADOW, ATTR_SHADOW);

		AttrWriter::writeAttr<AttrHard>(mWriter, obj.hard(), mActiveAttrHard, ATTR_NO_HARD, mCounter);
		AttrWriter::writeAttr<AttrShiny>(mWriter, obj.shiny(), mActiveAttrShiny, toObjString(AttrShiny()).c_str(), mCounter);
		AttrWriter::writeAttr<AttrBlend>(mWriter, obj.blend(), mActiveAttrBlend, toObjString(AttrBlend()).c_str(), mCounter);
		AttrWriter::writeAttr<AttrPolyOffset>(mWriter, obj.polyOffset(), mActiveAttrPolyOffset, toObjString(AttrPolyOffset(0.0f)).c_str(), mCounter);
		AttrWriter::writeAttr<AttrLightLevel>(mWriter, obj.lightLevel(), mActiveAttrLightLevel, ATTR_LIGHT_LEVEL_RESET, mCounter);
		AttrWriter::writeAttr<AttrCockpit>(mWriter, obj.cockpit(), mActiveAttrCockpit, ATTR_NO_COCKPIT, mCounter,
											manipPanelEnabled, manipPanelDisabled);
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
