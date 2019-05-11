/*
**  Copyright(C) 2018, StepToSky
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
#include "TransformAlg.h"

using namespace std::string_literals;

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void TransformAlg::applyTranslateKeysToTransform(Transform & inOutTrans, AnimTransList & inOutAnim) {
    for (auto animTr = inOutAnim.begin(); animTr != inOutAnim.end();) {
        if (animTr->mKeys.size() == 1) {
            const Point3 currPos = inOutTrans.mMatrix.position();
            inOutTrans.mMatrix.setPosition(currPos + animTr->mKeys[0].mPosition);
            animTr = inOutTrans.mAnimTrans.erase(animTr);
        }
        else {
            ++animTr;
        }
    }
}

void TransformAlg::applyRotateKeysToTransform(Transform & inOutTrans, AnimRotateList & inOutAnim) {
    for (auto animRot = inOutAnim.begin(); animRot != inOutAnim.end();) {
        if (animRot->mKeys.size() == 1) {
            TMatrix mtx;
            mtx.setRotate(animRot->mVector, animRot->mKeys[0].mAngleDegrees);
            inOutTrans.mMatrix *= mtx;
            animRot = inOutTrans.mAnimRotate.erase(animRot);
        }
        else {
            ++animRot;
        }
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void TransformAlg::applyMatrixToAnimTranslate(AnimTransList & inOutAnim, const TMatrix & tm) {
    for (auto & a : inOutAnim) {
        for (auto & k : a.mKeys) {
            tm.transformPoint(k.mPosition);
        }
    }
}

void TransformAlg::applyMatrixToAnimRotate(AnimRotateList & inOutAnim, const TMatrix & tm) {
    for (auto & a : inOutAnim) {
        tm.transformPoint(a.mVector);
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

const Transform * TransformAlg::animatedTranslateParent(const Transform * transform) {
    assert(transform);
    auto parent = transform->parent();
    do {
        if (parent == nullptr) {
            return nullptr;
        }
        if (parent->hasAnimTrans()) {
            return parent;
        }
        parent = parent->parent();
    } while (true);
}

const Transform * TransformAlg::animatedRotateParent(const Transform * transform) {
    assert(transform);
    auto parent = transform->parent();
    do {
        if (parent == nullptr) {
            return nullptr;
        }
        if (parent->hasAnimRotate()) {
            return parent;
        }
        parent = parent->parent();
    } while (true);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
