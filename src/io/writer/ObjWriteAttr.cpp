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

#include <cassert>
#include <functional>

#include "ObjWriteAttr.h"
#include "ObjWriteManip.h"

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

std::size_t ObjWriteAttr::count() const {
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
    static void writeAttr(AbstractWriter * writer, const std::optional<T> & attr, std::optional<T> & inOutActiveAttr, size_t & outCounter,
                          std::function<void(const T &)> attrEnable = nullptr, const std::function<void()> & attrDisable = nullptr) {
        if (!attr) {
            if (inOutActiveAttr) {
                writer->printLine(T::objDisableStr());
                if (attrDisable) {
                    attrDisable();
                }
                ++outCounter;
                inOutActiveAttr = std::nullopt;
            }
        }
        else {
            if (!inOutActiveAttr) {
                printObjAttr(*attr, *writer);
                if (attrEnable) {
                    attrEnable(*attr);
                }
                ++outCounter;
                inOutActiveAttr = *attr;
                return;
            }

            if (inOutActiveAttr != *attr) {
                printObjAttr(*attr, *writer);
                if (attrEnable) {
                    attrEnable(*attr);
                }
                ++outCounter;
                inOutActiveAttr = *attr;
                return;
            }

            inOutActiveAttr = *attr;
        }
    }
};

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAttr::writeAttributes(const AttrSet & attrSet) {
    const auto manipPanelEnabled = [&](const AttrCockpit & cockpit) {
        if (mManipWriter) {
            mManipWriter->setPanelEnabled(cockpit);
        }
    };
    const auto manipPanelDisabled = [&]() {
        if (mManipWriter) {
            mManipWriter->setPanelDisabled();
        }
    };

	//-------------------------------------------------------------------------

    const auto writeBool = [&](const char * attr) {
        if (attr) {
            ++mCounter;
            mWriter->printLine(attr);
        }
    };

	const auto writeAttr= [&](const std::string & attr) {
		if (!attr.empty()) {
			++mCounter;
			mWriter->printLine(attr);
		}
	};

    //-------------------------------------------------------------------------

    writeBool(ObjWriteState::processBool(attrSet.mIsDraped, mAttributes.mObject.mIsDraped, ATTR_DRAPED, ATTR_NO_DRAPED));
    writeBool(ObjWriteState::processBool(attrSet.mIsSolidForCamera, mAttributes.mObject.mIsSolidForCamera, ATTR_SOLID_CAMERA, ATTR_NO_SOLID_CAMERA));
    writeBool(ObjWriteState::processBool(attrSet.mIsDraw, mAttributes.mObject.mIsDraw, ATTR_DRAW_ENABLE, ATTR_DRAW_DISABLE));
    writeBool(ObjWriteState::processBool(attrSet.mIsCastShadow, mAttributes.mObject.mIsCastShadow, ATTR_SHADOW, ATTR_NO_SHADOW));

    AttrWriter::writeAttr<AttrHard>(mWriter, attrSet.mAttrHard, mActiveAttrHard, mCounter);
    AttrWriter::writeAttr<AttrShiny>(mWriter, attrSet.mAttrShiny, mActiveAttrShiny, mCounter);
    AttrWriter::writeAttr<AttrBlend>(mWriter, attrSet.mAttrBlend, mActiveAttrBlend, mCounter);
    AttrWriter::writeAttr<AttrPolyOffset>(mWriter, attrSet.mAttrPolyOffset, mActiveAttrPolyOffset, mCounter);
    AttrWriter::writeAttr<AttrLightLevel>(mWriter, attrSet.mAttrLightLevel, mActiveAttrLightLevel, mCounter);
    AttrWriter::writeAttr<AttrCockpit>(mWriter, attrSet.mAttrCockpit, mActiveAttrCockpit, mCounter, manipPanelEnabled, manipPanelDisabled);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
