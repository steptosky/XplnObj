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

#include "xpln/obj/ObjMesh.h"
#include "gtest/gtest.h"
#include <xpln/obj/ObjMain.h>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class TestUtils {
public:

    //-----------------------------------------------------

    static void setTestExportOptions(ObjMain & inOutMain) {
        inOutMain.pExportOptions.enable(XOBJ_EXP_MARK_VERTEX);
        inOutMain.pExportOptions.enable(XOBJ_EXP_MARK_TRANSFORM);
        inOutMain.pExportOptions.enable(XOBJ_EXP_MARK_TREE_HIERARCHY);
        inOutMain.pExportOptions.enable(XOBJ_EXP_MARK_MESH);
        inOutMain.pExportOptions.enable(XOBJ_EXP_DEBUG);
    }

    //-----------------------------------------------------

    static void extractLod(ObjMain & main, const size_t lodNum, ObjLodGroup *& outLod) {
        ASSERT_TRUE(main.lods().size() > lodNum) << " value is " << lodNum;
        outLod = &*main.lods().at(lodNum);
    }

    static void extractTransform(Transform & transform, const size_t numTransform, Transform *& outTrans) {
        ASSERT_TRUE(transform.childrenNum() > numTransform) << " value is " << numTransform;
        outTrans = static_cast<Transform*>(transform.childAt(numTransform));
    }

    static void extractMesh(Transform & transform, const size_t meshNum, ObjMesh *& outMesh) {
        ASSERT_TRUE(transform.objList().size() > meshNum) << " value is " << meshNum;
        auto it = transform.objList().begin();
        for (size_t i = 0; i < meshNum; ++i, ++it) {}
        ASSERT_EQ(eObjectType::OBJ_MESH, (*it)->objType());
        outMesh = static_cast<ObjMesh *>(it->get());
    }

    //-----------------------------------------------------

    static void createTestAnimTranslate(AnimTransList & outAnim, const Point3 & inVec, const TMatrix & inMtx, const char * inDrf = nullptr) {
        AnimTrans anim;
        if (!inDrf) {
            anim.pDrf = "test";
        }
        else {
            anim.pDrf = inDrf;
        }
        anim.pKeys.emplace_back(AnimTrans::Key(inVec * -1.0f, -10.0f));
        inMtx.transformPoint(anim.pKeys.back().pPosition);
        //			anim.pKeys.emplace_back(AnimTrans::Key(Point3(0.0), 0.0f));
        //			inMtx.transformPoint(anim.pKeys.back().pPosition);
        anim.pKeys.emplace_back(AnimTrans::Key(inVec, 10.0f));
        inMtx.transformPoint(anim.pKeys.back().pPosition);
        outAnim.emplace_back(anim);
    }

    static void createTestAnimTranslate(AnimTransList & outAnim, const AnimTransKey & inKey1, const AnimTransKey & inKey2, const char * inDrf = nullptr) {
        createTestAnimTranslate(outAnim, inKey1, inKey2, TMatrix(), inDrf);
    }

    static void createTestAnimTranslate(AnimTransList & outAnim, const AnimTransKey & inKey1, const AnimTransKey & inKey2, const TMatrix & inMtx = TMatrix(), const char * inDrf = nullptr) {
        AnimTrans anim;
        if (!inDrf) {
            anim.pDrf = "test";
        }
        else {
            anim.pDrf = inDrf;
        }
        anim.pKeys.emplace_back(inKey1);
        inMtx.transformPoint(anim.pKeys.back().pPosition);
        anim.pKeys.emplace_back(inKey2);
        inMtx.transformPoint(anim.pKeys.back().pPosition);
        outAnim.emplace_back(anim);
    }

    static void createTestAnimTranslate(AnimTransList & outAnim, const AnimTransKey * inKey, size_t inCount, const TMatrix & inMtx, const char * inDrf = nullptr) {
        AnimTrans anim;
        if (!inDrf) {
            anim.pDrf = "test";
        }
        else {
            anim.pDrf = inDrf;
        }
        for (size_t i = 0; i < inCount; ++i) {
            anim.pKeys.emplace_back(inKey[i]);
            inMtx.transformPoint(anim.pKeys.back().pPosition);
        }
        outAnim.emplace_back(anim);
    }

    static void createTestAnimTranslate(AnimTransList & outAnim, const TMatrix & inMtx, const char * inDrf = nullptr) {
        createTestAnimTranslate(outAnim, Point3(50.0f, 50.0f, 50.0f), inMtx, inDrf);
    }

    static void createTestAnimTranslate(AnimTransList & outAnim, const float inRotate, const char * inDrf = nullptr) {
        TMatrix tm;
        if (inRotate != 0.0f) {
            tm.rotateDegreesY(inRotate);
        }
        createTestAnimTranslate(outAnim, tm, inDrf);
    }

    static void createTestAnimTranslate(AnimTransList & outAnim, const Point3 & shift, const char * inDrf = nullptr) {
        TMatrix tm;
        tm.setPosition(shift);
        createTestAnimTranslate(outAnim, tm, inDrf);
    }

    //-----------------------------------------------------

    static void createTestAnimRotate(AnimRotateList & outAnim, const Point3 & onVec, const TMatrix & inMtx, const char * inDrf = nullptr) {
        AnimRotate anim;
        if (!inDrf) {
            anim.pDrf = "test";
        }
        else {
            anim.pDrf = inDrf;
        }
        anim.pVector = onVec.normalized();
        inMtx.transformVector(anim.pVector);

        anim.pKeys.emplace_back(AnimRotate::Key(-90.0f, -10.0f));
        //anim.pKeys.emplace_back(AnimRotate::Key(0.0f, 0.0f));
        anim.pKeys.emplace_back(AnimRotate::Key(90.0f, 10.0f));
        outAnim.emplace_back(anim);
    }

    static void createTestAnimRotate(AnimRotateList & outAnim, const Point3 & onVec, const char * inDrf = nullptr) {
        createTestAnimRotate(outAnim, onVec, TMatrix(), inDrf);
    }

    //-----------------------------------------------------
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
