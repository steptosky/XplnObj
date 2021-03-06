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

#include "ObjReaderListener.h"
#include "xpln/obj/ImportContext.h"

namespace xobj {
class IOStatistic;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ObjReadParser;

class ObjReader {

    ObjReader() = default;
    ~ObjReader() = default;

public:

    static bool readFile(ImportContext & context, ObjReaderListener & listener);

private:

    bool readFile(const std::string & filePath) const;

    static bool readCounts(ObjReadParser & parser,
                           size_t & outVertices,
                           size_t & outLines,
                           size_t & outLites,
                           size_t & outFaces);
    static bool readHeader(ObjReadParser & parser);
    static bool readVertex(ObjReadParser & parser, ObjMesh::VertexList & outVert, ObjReaderListener::FaceIndex & inOutIndex);
    static bool readIndexes(ObjReadParser & parser, ObjReaderListener::FaceIndexArray & outIndexes, ObjReaderListener::FaceIndex & inOUtIndex);
    bool readLod(ObjReadParser & parser) const;
    bool readGlobalAttribute(ObjReadParser & parser) const;
    bool readAttribute(ObjReadParser & parser) const;
    bool readManipulators(ObjReadParser & parser) const;
    bool readTris(ObjReadParser & parser) const;
    bool readAnimBegin(ObjReadParser & parser) const;
    bool readAnimEnd(ObjReadParser & parser) const;
    bool readTranslateAnim(ObjReadParser & parser) const;
    bool readHideAnim(ObjReadParser & parser) const;
    bool readShowAnim(ObjReadParser & parser) const;
    bool readRotateAnim(ObjReadParser & parser) const;
    bool readTranslateKeysAnim(ObjReadParser & parser) const;
    bool readRotateKeysAnim(ObjReadParser & parser) const;

    static bool readAnimLoop(ObjReadParser & parser, float & outVal);

    ObjReaderListener * mObjParserListener = nullptr;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
