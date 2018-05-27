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

#include "xpln/obj/animation/AnimVisibilityKey.h"
#include "sts/utilities/Compare.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

AnimVisibilityKey::AnimVisibilityKey()
    : pType(UNDEFINED),
      pValue1(0.0f),
      pValue2(1.0f),
      pDrf("none"),
      pLoopValue(0.0f),
      pHasLoop(false) {}

AnimVisibilityKey::AnimVisibilityKey(eType type, float val1, float val2, const std::string & dataRef)
    : pType(type),
      pValue1(val1),
      pValue2(val2),
      pDrf(dataRef),
      pLoopValue(0.0f),
      pHasLoop(false) {}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool AnimVisibilityKey::operator==(const AnimVisibilityKey & other) const {
    return pType == other.pType &&
           sts::isEqual(pValue1, other.pValue1) &&
           sts::isEqual(pValue2, other.pValue2) &&
           sts::isEqual(pLoopValue, other.pLoopValue) &&
           pHasLoop == other.pHasLoop &&
           pDrf == other.pDrf;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void AnimVisibilityKey::reset() {
    pType = UNDEFINED;
    pValue1 = 0.0f;
    pValue2 = 1.0f;
    pDrf = "none";
    pLoopValue = 0.0f;
    pHasLoop = false;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
