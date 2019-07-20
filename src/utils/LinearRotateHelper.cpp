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
#include <algorithm>
#include "xpln/utils/LinearRotateHelper.h"
#include "xpln/common/TMatrix.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

inline void correctKeysNumBefore(AnimRotate::KeyList & inOutKeys, const LinearRotateHelper::Input & input,
                                 const float angle, const std::size_t until) {

    const auto inputCount = std::min(input.size(), until);
    for (std::size_t i = 0; i < inputCount; ++i) {
        inOutKeys.emplace_back(AnimRotateKey(angle, input[i].mDrfValue));
    }
}

inline void correctKeysNumAfter(AnimRotate::KeyList & inOutKeys, const LinearRotateHelper::Input & input,
                                const float angle, const std::size_t from) {

    const auto inputCount = input.size();
    for (std::size_t i = from; i < inputCount; ++i) {
        inOutKeys.emplace_back(AnimRotateKey(angle, input[i].mDrfValue));
    }
}

inline std::tuple<Point3, float> calculateAngleAxis(const Quat & q1, const Quat & q2) {
    const auto animVectorQuat = q1 * glm::inverse(q2);
    const auto animVector = glm::axis(animVectorQuat);
    const auto animAngle = glm::degrees(glm::angle(animVectorQuat));
    return std::make_tuple(Point3(animVector.x, animVector.y, animVector.z).normalized(), animAngle);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

AnimRotateList LinearRotateHelper::makeAnimations(const Input & input, const TMatrix & matrix) {
    AnimRotateList out;

    const auto keysNum = input.size();
    if (keysNum < 2) {
        return out;
    }

    out.reserve(10);

    {
        // add the first
        auto & back = out.emplace_back();
        const auto & currKey = input[0];
        const auto & nextKey = input[1];
        const auto [animVector, animAngle] = calculateAngleAxis(currKey.mQuat, nextKey.mQuat);
        back.mVector = animVector;
        matrix.transformVector(back.mVector);
        back.mKeys.reserve(input.size());
        back.mKeys.emplace_back(AnimRotateKey(0, currKey.mDrfValue));
        back.mKeys.emplace_back(AnimRotateKey(animAngle, nextKey.mDrfValue));
    }

    // we have already added the first keys and we do necessary offset
    std::size_t currI = 1;
    std::size_t nextI = 2;
    for (; nextI < keysNum; ++currI, ++nextI) {
        const auto & currKey = input[currI];
        const auto & nextKey = input[nextI];
        const auto [animVector, animAngle] = calculateAngleAxis(currKey.mQuat, nextKey.mQuat);

        if (auto & back = out.back(); back.mVector != animVector) {
            // correction keys count for current anim before creating a new one.
            assert(!back.mKeys.empty());
            correctKeysNumAfter(back.mKeys, input, back.mKeys.back().mAngleDegrees, nextI);

            // create new
            AnimRotate & anim = out.emplace_back();
            anim.mVector = animVector;
            matrix.transformVector(anim.mVector);
            anim.mKeys.reserve(input.size());
            correctKeysNumBefore(anim.mKeys, input, 0, currI);
            anim.mKeys.emplace_back(AnimRotateKey(0, currKey.mDrfValue));
            anim.mKeys.emplace_back(AnimRotateKey(animAngle, nextKey.mDrfValue));
        }
        else {
            assert(back.mKeys.back().mDrfValue == currKey.mDrfValue);
            back.mKeys.emplace_back(AnimRotateKey(back.mKeys.back().mAngleDegrees + animAngle, nextKey.mDrfValue));
        }
    }

    return out;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
