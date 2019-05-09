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

#include "ObjWriteAttr.h"
#include "ObjWriteManip.h"

#include "AbstractWriter.h"
#include "common/AttributeNames.h"
#include "xpln/obj/ObjMesh.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteAttr::reset() {
    mAttributes.reset();
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

    const auto writeAttr = [&](const std::string & attr) {
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

    writeAttr(ObjWriteState::processAttr(attrSet.mAttrHard, mAttributes.mObject.mAttrHard,
                                         [&]() {
                                             return attrSet.mAttrHard ? attrSet.mAttrHard->objStr() : std::string();
                                         },
                                         []() {
                                             return AttrHard::objDisableStr();
                                         }));

    writeAttr(ObjWriteState::processAttr(attrSet.mAttrShiny, mAttributes.mObject.mAttrShiny,
                                         [&]() {
                                             return attrSet.mAttrShiny ? attrSet.mAttrShiny->objStr() : std::string();
                                         },
                                         []() {
                                             return AttrShiny::objDisableStr();
                                         }));

    writeAttr(ObjWriteState::processAttr(attrSet.mAttrBlend, mAttributes.mObject.mAttrBlend,
                                         [&]() {
                                             return attrSet.mAttrBlend ? attrSet.mAttrBlend->objStr() : std::string();
                                         },
                                         []() {
                                             return AttrBlend::objDisableStr();
                                         }));

    writeAttr(ObjWriteState::processAttr(attrSet.mAttrPolyOffset, mAttributes.mObject.mAttrPolyOffset,
                                         [&]() {
                                             return attrSet.mAttrPolyOffset ? attrSet.mAttrPolyOffset->objStr() : std::string();
                                         },
                                         []() {
                                             return AttrPolyOffset::objDisableStr();
                                         }));

    writeAttr(ObjWriteState::processAttr(attrSet.mAttrLightLevel, mAttributes.mObject.mAttrLightLevel,
                                         [&]() {
                                             if (!attrSet.mAttrLightLevel) {
                                                 return std::string();
                                             }
                                             auto copy = *attrSet.mAttrLightLevel;
                                             copy.setDataref(mWriter->actualDataref(copy.dataref()));
                                             return copy.objStr();
                                         },
                                         []() {
                                             return AttrLightLevel::objDisableStr();
                                         }));

    writeAttr(ObjWriteState::processAttr(attrSet.mAttrCockpit, mAttributes.mObject.mAttrCockpit,
                                         [&]() {
                                             manipPanelEnabled(*attrSet.mAttrCockpit);
                                             return attrSet.mAttrCockpit->objStr();
                                         },
                                         [&]() {
                                             manipPanelDisabled();
                                             return AttrCockpit::objDisableStr();
                                         }));
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
