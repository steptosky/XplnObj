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

#include <cstddef>
#include "xpln/Export.h"

namespace xobj {

class ObjReader;
class ObjWriter;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Statistic of the 'obj' Reader/Writer.
 */
class IOStatistic {
public:

    /*! \details Constructor default. */
    XpObjLib IOStatistic();

    //-----------------------------------

    std::size_t mMeshVerticesCount; //!< Mesh vertices count
    std::size_t mMeshFacesCount;    //!< Mesh faces count (triangles)
    std::size_t mLineVerticesCount; //!< Line vertices count

    std::size_t mMeshObjCount;           //!< Mesh objects count
    std::size_t mLineObjCount;           //!< Line objects count
    std::size_t mLightObjPointCount;     //!< Light named objects count
    std::size_t mLightObjNamedCount;     //!< Light named objects count
    std::size_t mLightObjCustomCount;    //!< Light custom objects count
    std::size_t mLightObjParamCount;     //!< Light param objects count
    std::size_t mLightObjSpillCustCount; //!< Light spill custom objects count
    std::size_t mDummyObjCount;          //!< Dummy objects count
    std::size_t mSmokeObjCount;          //!< Dummy objects count
    std::size_t mEmitterObjCount;        //!< Particle emitter objects count

    std::size_t mCustomLinesCount; //!< Count of lines that are printed before and after objects.
    std::size_t mGlobAttrCount;    //!< Global attributes count
    std::size_t mTrisManipCount;   //!< Object manipulators count
    std::size_t mTrisAttrCount;    //!< Object attributes count

    std::size_t mAnimAttrCount;

    //------------------------------------------------------------

    XpObjLib void reset();

    //------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
