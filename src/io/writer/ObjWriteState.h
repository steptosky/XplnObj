#pragma once

/*
**  Copyright(C) 2019, StepToSky
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

#include <functional>
#include "xpln/Export.h"
#include "xpln/obj/attributes/AttrGlobSet.h"
#include "xpln/obj/attributes/AttrDrapedSet.h"
#include "xpln/obj/attributes/AttrSet.h"

namespace xobj {

/**********************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************/

class ObjWriteState final {
public:

    //-------------------------------------------------------------------------
    /// @{

    ObjWriteState() = default;
    ObjWriteState(const ObjWriteState &) = default;
    ObjWriteState(ObjWriteState &&) = delete;

    ~ObjWriteState() = default;

    ObjWriteState & operator=(const ObjWriteState &) = default;
    ObjWriteState & operator=(ObjWriteState &&) = delete;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib static void processBool(bool newValue, bool & inOutStateValue,
                                     const std::function<void(bool enable)> & switchFn);

    template<typename T>
    static void processAttr(const T & newValue, T & inOutStateValue,
                            const std::function<void(bool enable)> & switchFn) {
        if (newValue == inOutStateValue) {
            return;
        }

        if (!inOutStateValue && newValue) {
            inOutStateValue = newValue;
            switchFn(true);
            return;
        }

        if (inOutStateValue && !newValue) {
            inOutStateValue = newValue;
            switchFn(false);
            return;
        }

        inOutStateValue = newValue;
        switchFn(true);
    }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void reset() {
        mGlobal.reset();
        mDraped.reset();
        mObject.reset();
    }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    AttrGlobSet mGlobal;
    AttrDrapedSet mDraped;
    AttrSet mObject;

    /// @}
    //-------------------------------------------------------------------------

};

/**********************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************/
}
