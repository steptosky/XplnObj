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

#include <optional>
#include <vector>
#include "xpln/common/String.h"
#include "xpln/common/Point3.h"
#include "xpln/common/TMatrix.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class Translate final {
public:

    struct Key {
        Point3 position;
        float value = 0.0f;

        bool operator==(const Key & r) const { return position == r.position && value == r.value; }
        bool operator!=(const Key & r) const { return !(*this == r); }
    };

    typedef std::vector<Key> KeyList;

    //-------------------------------------------------------------------------
    ///@{

    Translate() = default;
    Translate(const Translate &) = default;
    Translate(Translate &&) = default;

    ~Translate() = default;

    Translate & operator=(const Translate &) = default;
    Translate & operator=(Translate &&) = default;

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    bool operator==(const Translate & r) const {
        return mKeys == r.mKeys && mDataRef == r.mDataRef && mLoop == r.mLoop;
    }

    bool operator!=(const Translate & r) const { return !(*this == r); }

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    bool isAnimated() const noexcept { return !mKeys.empty(); }
    XpObjLib void applyTransform(const TMatrix & tmx) noexcept;

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    KeyList mKeys;
    String mDataRef;
    std::optional<float> mLoop;

    ///@}
    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
