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
#include "xpln/Export.h"
#include "xpln/common/Angle.h"
#include "xpln/common/String.h"
#include "xpln/common/Point3.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class RotationAxis final {
public:

    struct Key {
        Degrees angleDeg;
        float value = 0.0f;

        bool operator==(const Key & r) const { return angleDeg == r.angleDeg && value == r.value; }
        bool operator!=(const Key & r) const { return !(*this == r); }
    };

    typedef std::vector<Key> KeyList;

    //-------------------------------------------------------------------------
    ///@{

    RotationAxis() = default;

    explicit RotationAxis(const Point3 & vec)
        : mVector(vec) {}

    RotationAxis(const RotationAxis &) = default;
    RotationAxis(RotationAxis &&) = default;

    ~RotationAxis() = default;

    RotationAxis & operator=(const RotationAxis &) = default;
    RotationAxis & operator=(RotationAxis &&) = default;

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    XpObjLib bool operator==(const RotationAxis & r) const;
    bool operator!=(const RotationAxis & r) const { return !(*this == r); }

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    static RotationAxis makeX() { return RotationAxis(Point3(1.0f, 0.0f, 0.0f)); }
    static RotationAxis makeY() { return RotationAxis(Point3(0.0f, 1.0f, 0.0f)); }
    static RotationAxis makeZ() { return RotationAxis(Point3(0.0f, 0.0f, 1.0f)); }

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    bool isAnimated() const { return !mKeys.empty(); }

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    KeyList mKeys;
    Point3 mVector;
    String mDataRef;
    std::optional<float> mLoop;

    ///@}
    //-------------------------------------------------------------------------
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
