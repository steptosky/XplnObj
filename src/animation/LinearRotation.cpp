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

#include <cassert>
#include <tuple>
#include "xpln/common/TMatrix.h"
#include "xpln/obj/animation/LinearRotation.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

inline std::tuple<Point3, Degrees> calculateAngleAxis(const Quat & q1, const Quat & q2, const Quat & offset) noexcept {
    Quat animVectorQuat = q1 * q2.inverse();
    animVectorQuat.rotate(offset);
    const auto animVector = animVectorQuat.axis();
    const auto animAngle = Degrees(animVectorQuat.angleDeg());
    return std::make_tuple(Point3(animVector.x, animVector.y, animVector.z).normalized(), animAngle);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::optional<std::size_t> LinearRotation::checkDatarefValuesOrder(const KeyList & keys) noexcept {
    if (keys.size() < 2) {
        return std::nullopt;
    }
    const bool negative = (keys[1].mDrfValue - keys[0].mDrfValue) < 0.0f;
    if (!negative) {
        for (std::size_t it = 1; it < keys.size(); ++it) {
            const auto & curr = keys[it - 1];
            const auto & next = keys[it];
            if (curr.mDrfValue > next.mDrfValue) {
                return it;
            }
        }
    }
    else {
        for (std::size_t it = 1; it < keys.size(); ++it) {
            const auto & curr = keys[it - 1];
            const auto & next = keys[it];
            if (curr.mDrfValue < next.mDrfValue) {
                return it;
            }
        }
    }
    return std::nullopt;
}

AxisSetRotation LinearRotation::retrieveAxes(const KeyList & keys, const Quat & offset) noexcept {
    AxisSetRotation out;

    const auto keysNum = keys.size();
    if (keysNum < 2) {
        return out;
    }
    assert(!checkDatarefValuesOrder(keys));
    out.mAxes.reserve(10);

    {
        // add the first
        auto & back = out.mAxes.emplace_back();
        const auto & currKey = keys[0];
        const auto & nextKey = keys[1];
        const auto [animVector, animAngle] = calculateAngleAxis(currKey.mQuat, nextKey.mQuat, offset);
        back.mVector = animVector;
        back.mKeys.reserve(keys.size());
        back.mKeys.emplace_back(RotationAxis::Key{Degrees(0), currKey.mDrfValue});
        back.mKeys.emplace_back(RotationAxis::Key{animAngle, nextKey.mDrfValue});
    }

    // we have already added the first keys and we do necessary offset
    std::size_t currI = 1;
    std::size_t nextI = 2;
    for (; nextI < keysNum; ++currI, ++nextI) {
        const auto & currKey = keys[currI];
        const auto & nextKey = keys[nextI];
        const auto [animVector, animAngle] = calculateAngleAxis(currKey.mQuat, nextKey.mQuat, offset);

        if (auto & back = out.mAxes.back(); back.mVector != animVector) {
            // correction keys count for current anim before creating a new one.
            assert(!back.mKeys.empty());
            back.mKeys.emplace_back(RotationAxis::Key{back.mKeys.back().mAngle, keys.back().mDrfValue});

            // create new
            RotationAxis & anim = out.mAxes.emplace_back();
            anim.mVector = animVector;
            anim.mKeys.reserve(keys.size());
            anim.mKeys.emplace_back(RotationAxis::Key{Degrees(), keys.front().mDrfValue});
            anim.mKeys.emplace_back(RotationAxis::Key{Degrees(), currKey.mDrfValue});
            anim.mKeys.emplace_back(RotationAxis::Key{animAngle, nextKey.mDrfValue});
        }
        else {
            assert(back.mKeys.back().mDrfValue == currKey.mDrfValue);
            back.mKeys.emplace_back(RotationAxis::Key{back.mKeys.back().mAngle + animAngle, nextKey.mDrfValue});
        }
    }

    return out;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
