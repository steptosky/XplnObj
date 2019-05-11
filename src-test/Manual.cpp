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

#include <gtest/gtest.h>
#include "xpln/obj/ObjMain.h"
#include <xpln/obj/ObjEmitter.h>

using namespace xobj;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*
 * This tests are for manual checking.
 * Sometime you want to see result yourself and to analyze it.
 * this section is for code that create such a results.
 * In normal way it is disabled and can be enable when it is needed.
 * 
 * For example: I write a code that generates some obj file instead of
 * compiling 3Ds Max plugin, open 3Ds Max, create scene and export to see some result.
 * 
 */

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

#if 0
TEST(Manual, case1) {
    const auto fileName = XOBJ_PATH("manual-case1.obj");
    //-----------------------------
    ObjMain mainOut;
    mainOut.mAttr.mParticleSystemPath = "some_path";
    auto & lod = mainOut.addLod();
    auto * emitter = new ObjEmitter;
	emitter->setObjectName("some_name");
    emitter->setIndex(1);
    emitter->setPosition(Point3(1, 2, 3));
    emitter->setOrientation(10.0f, 20.0f, 30.0f);
    lod.transform().addObject(emitter);
    ExportContext expContext(fileName);
    ASSERT_TRUE(mainOut.exportObj(expContext));
}
#endif

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
