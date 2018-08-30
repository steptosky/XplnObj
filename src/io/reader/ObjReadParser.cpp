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

#include "ObjReadParser.h"
#include "common/Logger.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ObjReadParser::ObjReadParser(const std::string & filePath)
    : mMemCurr(nullptr),
      mMemStart(nullptr),
      mMemEnd(nullptr) {

    if (!filePath.empty()) {
        readFile(filePath);
    }
}

ObjReadParser::~ObjReadParser() {
    close();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ObjReadParser::readFile(const std::string & filePath) {
    close();
    FILE * file = fopen(filePath.data(), "rb");
    if (!file) {
        ULError << "File <" << filePath.data() << "> could not be read!";
        return false;
    }

    const unsigned filesize = fileSize(file);

    mMemStart = static_cast<uint8_t *>(malloc(filesize));
    if (mMemStart == nullptr) {
        LError << "Memory could not be allocated!";
        fclose(file);
        return false;
    }
    if (fread(mMemStart, 1, filesize, file) != filesize) {
        close();
        fclose(file);
        LError << "Size of the allocated memory is incorrect!";
        return false;
    }
    mMemCurr = mMemStart;
    mMemEnd = mMemStart + filesize;
    fclose(file);
    return true;
}

void ObjReadParser::close() {
    if (mMemStart) {
        free(mMemStart);
        mMemStart = nullptr;
        mMemCurr = nullptr;
        mMemEnd = nullptr;
    }
}

unsigned ObjReadParser::fileSize(FILE * file) {
    fseek(file, 0L, SEEK_END);
    const auto filesize = static_cast<unsigned>(ftell(file));
    fseek(file, 0L, SEEK_SET);
    return unsigned(filesize);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
