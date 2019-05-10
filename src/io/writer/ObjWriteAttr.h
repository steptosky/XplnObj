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

#include <cstdint>
#include <tuple>
#include "xpln/obj/attributes/AttrSet.h"
#include "xpln/obj/ObjMesh.h"
#include "io/ObjState.h"
#include "xpln/obj/ObjMain.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class AbstractWriter;
class ObjMesh;
class ObjAbstract;

class ObjWriteManip;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ObjWriteAttr {
public:

    explicit ObjWriteAttr(ObjState::Ptr state)
        : mState(std::move(state)) {
        assert(mState);
    }

    ObjWriteAttr(const ObjWriteAttr &) = delete;
    ObjWriteAttr & operator =(const ObjWriteAttr &) = delete;

    ~ObjWriteAttr() = default;

    XpObjLib void writeGlobAttr(AbstractWriter * writer, const ObjMain * obj);
    XpObjLib void writeObjAttr(AbstractWriter * writer, const ObjAbstract * obj);
    XpObjLib void reset(ObjState::Ptr state);
    XpObjLib std::tuple<std::size_t, std::size_t, std::size_t> count() const;

private:

    void writeAttr();
    void writeManip();
    bool checkManip(AttrManipBase * manip) const;

    const ObjMesh * mObj = nullptr;
    AbstractWriter * mWriter = nullptr;
    ObjState::Ptr mState;
    bool mIsPanelManip = false;

    std::size_t mGlobNum = 0;
    std::size_t mAttrNum = 0;
    std::size_t mManipNum = 0;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
