#pragma once

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

#include "xpln/XplnObjExport.h"
#include "xpln/obj/attributes/AttrCockpit.h"
#include "xpln/obj/manipulators/AttrManipPanel.h"

namespace xobj {

/**********************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************/

class AbstractWriter;
class AttrManipBase;
class ObjAbstract;
class ObjMesh;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Manipulators' state machine.
 * \remark This algorithm auto-disables the panel manipulator, 
 *         so you have to explicitly set the manipulator to each object that needs it.
 *         
 * \warning Don't delete \link ObjWriteManip::mActiveManip \endlink 
 *          because it will be deleted with the object which is owner 
 *          of the pointer to the manipulator. 
 *          This class just uses the manipulators and does not take ownership.
 */
class ObjWriteManip {
public:

    ObjWriteManip() = default;
    ObjWriteManip(const ObjWriteManip &) = delete;
    ObjWriteManip & operator =(const ObjWriteManip &) = delete;
    ~ObjWriteManip() = default;

    XpObjLib void write(AbstractWriter * writer, const ObjAbstract * obj);
    XpObjLib void reset();
    XpObjLib size_t count() const;

    XpObjLib void setPanelEnabled(const AttrCockpit & cockpit);
    XpObjLib void setPanelDisabled();

private:

    const AttrManipBase * prepareManip(const AttrManipBase * manip) const;

    void write(AbstractWriter * writer, const AttrManipBase * manip);
    void print(AbstractWriter * writer, const AttrManipBase * manip);

    const ObjMesh * mObj = nullptr;
    const AttrManipBase * mActiveManip = nullptr;
    size_t mManipCounter = 0;
    bool mIsPanelManip = false;

    AttrManipPanel mAttrManipPanel;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
