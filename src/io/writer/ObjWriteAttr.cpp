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
        ++mCounter;
        mWriter->printLine(attr);
    };

    const auto writeAttr = [&](const std::string & attr) {
        ++mCounter;
        mWriter->printLine(attr);
    };

    //-------------------------------------------------------------------------

    ObjWriteState::processBool(attrSet.mIsDraped, mAttributes.mObject.mIsDraped,
                               [&]() { writeBool(ATTR_DRAPED); }, [&]() { writeBool(ATTR_NO_DRAPED); });

    ObjWriteState::processBool(attrSet.mIsSolidForCamera, mAttributes.mObject.mIsSolidForCamera,
                               [&]() { writeBool(ATTR_SOLID_CAMERA); }, [&]() { writeBool(ATTR_NO_SOLID_CAMERA); });

    ObjWriteState::processBool(attrSet.mIsDraw, mAttributes.mObject.mIsDraw,
                               [&]() { writeBool(ATTR_DRAW_ENABLE); }, [&]() { writeBool(ATTR_DRAW_DISABLE); });

    ObjWriteState::processBool(attrSet.mIsCastShadow, mAttributes.mObject.mIsCastShadow,
                               [&]() { writeBool(ATTR_SHADOW); }, [&]() { writeBool(ATTR_NO_SHADOW); });

    //-------------------------------------------------------------------------

    ObjWriteState::processAttr(attrSet.mAttrHard, mAttributes.mObject.mAttrHard,
                               [&]() {
                                   if (attrSet.mAttrHard) {
                                       writeAttr(attrSet.mAttrHard->objStr());
                                   }
                               },
                               [&]() {
                                   writeAttr(AttrHard::objDisableStr());
                               });

    ObjWriteState::processAttr(attrSet.mAttrShiny, mAttributes.mObject.mAttrShiny,
                               [&]() {
                                   if (attrSet.mAttrShiny) {
                                       writeAttr(attrSet.mAttrShiny->objStr());
                                   }
                               },
                               [&]() {
                                   writeAttr(AttrShiny::objDisableStr());
                               });

    ObjWriteState::processAttr(attrSet.mAttrBlend, mAttributes.mObject.mAttrBlend,
                               [&]() {
                                   if (attrSet.mAttrBlend) {
                                       writeAttr(attrSet.mAttrBlend->objStr());
                                   }
                               },
                               [&]() {
                                   writeAttr(AttrBlend::objDisableStr());
                               });

    ObjWriteState::processAttr(attrSet.mAttrPolyOffset, mAttributes.mObject.mAttrPolyOffset,
                               [&]() {
                                   if (attrSet.mAttrPolyOffset) {
                                       writeAttr(attrSet.mAttrPolyOffset->objStr());
                                   }
                               },
                               [&]() {
                                   writeAttr(AttrPolyOffset::objDisableStr());
                               });

    ObjWriteState::processAttr(attrSet.mAttrLightLevel, mAttributes.mObject.mAttrLightLevel,
                               [&]() {
                                   if (attrSet.mAttrLightLevel) {
                                       writeAttr(attrSet.mAttrLightLevel->objStr());
                                   }
                               },
                               [&]() {
                                   writeAttr(AttrLightLevel::objDisableStr());
                               });

    ObjWriteState::processAttr(attrSet.mAttrCockpit, mAttributes.mObject.mAttrCockpit,
                               [&]() {
                                   if (attrSet.mAttrCockpit) {
                                       manipPanelEnabled(*attrSet.mAttrCockpit);
                                       writeAttr(attrSet.mAttrCockpit->objStr());
                                   }
                               },
                               [&]() {
                                   manipPanelDisabled();
                                   writeAttr(AttrCockpit::objDisableStr());
                               });

}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
