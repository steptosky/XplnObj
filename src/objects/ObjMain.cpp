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
#include <algorithm>

#include "xpln/obj/ObjMain.h"
#include "io/writer/ObjWriter.h"
#include "io/reader/ObjReader.h"
#include "io/reader/ObjReaderInterpreter.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

class LodGroupCreator : public ObjLodGroup {
public:
    LodGroupCreator() { }
};

bool gSortLod(ObjLodGroup * i, ObjLodGroup * j) {
    return (i->nearVal() < j->nearVal());
}

/********************************************************************************************************/
///////////////////////////////////////* Constructors/Destructor *////////////////////////////////////////
/********************************************************************************************************/

ObjMain::ObjMain() { }

ObjMain::~ObjMain() {
    for (auto it = mLods.begin(); it != mLods.end(); ++it) {
        delete *it;
    }
    mLods.clear();
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

bool ObjMain::exportToFile(const std::string & path) {
    IOStatistic outStat;
    return exportToFile(path, outStat);
}

//-------------------------------------------------------------------------

bool ObjMain::importFromFile(const std::string & path) {
    IOStatistic outStat;
    return importFromFile(path, outStat);
}

//-------------------------------------------------------------------------

bool ObjMain::exportToFile(const std::string & path, IOStatistic & outStat) {
    sortLod();
    outStat.reset();
    return ObjWriter().writeFile(this, path, pExportOptions.signature(), outStat, pMatrix);
}

//-------------------------------------------------------------------------

bool ObjMain::importFromFile(const std::string & path, IOStatistic & outStat) {
    outStat.reset();
    ObjReaderInterpreter interpreter(this, pMatrix, &outStat);
    return ObjReader::readFile(path, interpreter);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

ObjLodGroup & ObjMain::lod(const std::size_t index) {
    assert(index < mLods.size());
    return *(mLods.at(index));
}

//-------------------------------------------------------------------------

const ObjLodGroup & ObjMain::lod(const std::size_t index) const {
    assert(index < mLods.size());
    return *(mLods.at(index));
}

//-------------------------------------------------------------------------

ObjLodGroup & ObjMain::addLod() {
    ObjLodGroup * lod = new LodGroupCreator();
    mLods.push_back(lod);
    return *lod;
}

//-------------------------------------------------------------------------

void ObjMain::removeLod(const std::size_t index) {
    assert(index < mLods.size());
    mLods.erase(mLods.begin() + index);
}

//-------------------------------------------------------------------------

std::size_t ObjMain::lodCount() const {
    return mLods.size();
}

void ObjMain::sortLod() {
    std::sort(mLods.begin(), mLods.end(), gSortLod);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjMain::setObjectName(const std::string & name) {
    mName = name;
}

const std::string & ObjMain::objectName() const {
    return mName;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
