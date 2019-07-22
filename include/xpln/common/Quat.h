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

#include "xpln/Export.h"
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/gtc/quaternion.hpp>
#include "xpln/common/Point3.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class Quat final : public glm::quat {
public:

    //-------------------------------------------------------------------------
    ///@{

    Quat()
        : glm::quat(1.0f, 0.0f, 0.0f, 0.0f) {}

    explicit Quat(const glm::quat & q)
        : glm::quat(q) {}

    Quat(const Quat &) = default;

    explicit Quat(glm::quat && q)
        : glm::quat(q) {}

    Quat(Quat &&) = default;

    ~Quat() = default;

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    Quat & operator=(const Quat &) = default;
    Quat & operator=(Quat &&) = default;

    using glm::quat::quat;
    using glm::quat::operator[];
    using glm::quat::operator=;
    using glm::quat::operator+=;
    using glm::quat::operator-=;
    using glm::quat::operator*=;
    using glm::quat::operator/=;

    ///@}
    //-------------------------------------------------------------------------
    ///@{

    Quat inverse() const {
        return glm::inverse(*this);
    }

    Point3 axis() const {
        const auto vec = glm::axis(*this);
        return Point3(vec.x, vec.y, vec.z);
    }

    float angleDeg() const {
        return glm::degrees(angleRad());
    }

    float angleRad() const {
        return glm::angle(*this);
    }

    // Modifies this quat so it is on same side of hypersphere as quat arg.
    XpObjLib void makeClosest(const Quat & q);

    ///@}
    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
