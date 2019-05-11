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

#include "xpln/common/EulerXyzHelper.h"
#include "xpln/obj/Transform.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void EulerXyzHelper::addToTransform(Transform & inOutTransform) {
    AnimRotateList anim = animation();
    for (auto & a : anim) {
        inOutTransform.mAnimRotate.push_back(a);
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool EulerXyzHelper::isAnimated(const AnimRotate & r) {
    return r.mKeys.size() > 1;
}

float EulerXyzHelper::value(const AnimRotate & r) {
    float v = 0.0f;
    if (!r.mKeys.empty()) {
        assert(r.mKeys.size() == 1);
        v = r.mKeys[0].mAngleDegrees;
    }
    return v;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

TMatrix EulerXyzHelper::prepareX() const {
    TMatrix mtx;
    if (!isAnimated(pY)) {
        mtx.rotateDegreesY(value(pY));
    }
    if (!isAnimated(pZ)) {
        mtx.rotateDegreesZ(value(pZ));
    }
    return mtx;
}

TMatrix EulerXyzHelper::prepareY() const {
    TMatrix mtx;
    if (!isAnimated(pZ)) {
        mtx.rotateDegreesZ(value(pZ));
    }
    return mtx;
}

//-------------------------------------------------------------------------

AnimRotateList EulerXyzHelper::animation() {
    pX.mVector.set(1.0f, 0.0f, 0.0f);
    pY.mVector.set(0.0f, 1.0f, 0.0f);
    pZ.mVector.set(0.0f, 0.0f, 1.0f);
    AnimRotateList outAnim;

    if (isAnimated(pZ)) {
        outAnim.emplace_back(pZ);
    }

    if (isAnimated(pY)) {
        outAnim.emplace_back(pY);
        AnimRotate & a = outAnim.back();
        TMatrix mtx = prepareY();
        mtx.transformVector(a.mVector);
    }

    if (isAnimated(pX)) {
        outAnim.emplace_back(pX);
        AnimRotate & a = outAnim.back();
        TMatrix mtx = prepareX();
        mtx.transformVector(a.mVector);
    }

    return outAnim;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
