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

#include "xpln/utils/DatarefsFile.h"
#include "exceptions/defines.h"
#include "sts/string/StringUtils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <limits>

namespace xobj {

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

std::uint64_t Dataref::invalidId() {
    // It hides 'max' because 3Ds Max uses win api and it conflicts with win min/max
    return std::numeric_limits<std::uint64_t>::max();
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void DatarefsFile::loadFile(const std::string & filePath) {
    using namespace std::string_literals;
    std::ifstream file(filePath, std::iostream::in);
    if (!file) {
        throw std::runtime_error(ExcTxt("can't open file <"s.append(filePath).append(">")));
    }
    try {
        loadStream(file);
        file.close();
    }
    catch (...) {
        file.close();
        throw;
    }
}

void DatarefsFile::loadStream(std::istream & input) {
    const char * sep = "\t";
    mData.clear();
    mData.reserve(1000);
    mLastId = 0;
    std::string line;
    if (!std::getline(input, line)) {
        return;
    }
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        if (line.front() == '#') {
            continue;
        }
        Dataref drf;
        const auto values = sts::MbStrUtils::splitToVector(line, sep);
        if (values.empty()) {
            continue;
        }

        std::size_t position = 0;
        if (std::isdigit(values[position].front())) {
            drf.mId = std::stoul(values[position++]);
            mLastId = std::max(mLastId, drf.mId);
        }

        if (position != values.size()) {
            drf.mKey = values[position++];
        }
        if (position != values.size()) {
            drf.mValueType = values[position++];
        }
        if (position != values.size()) {
            drf.mWritable = values[position++].front() == 'y';
        }
        if (position != values.size()) {
            drf.mValueUnits = values[position++];
        }
        if (position != values.size()) {
            drf.mDescription = values[position];
        }

        mData.emplace_back(std::move(drf));
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void DatarefsFile::saveFile(const std::string & filePath) {
    using namespace std::string_literals;
    std::ofstream file(filePath, std::iostream::out);
    if (!file) {
        throw std::runtime_error(ExcTxt("can't open file <"s.append(filePath).append(">")));
    }
    try {
        saveStream(file);
        file.close();
    }
    catch (...) {
        file.close();
        throw;
    }
}

void DatarefsFile::saveStream(std::ostream & output) {
    const char * sep = "\t";
    output << std::endl;
    for (auto & drf : mData) {
        if (drf.mId != std::numeric_limits<std::uint64_t>::max()) {
            output << std::setfill('0') << std::setw(6) << drf.mId << sep;
        }
        output << drf.mKey;
        if (!drf.mValueType.empty()) {
            output << sep << drf.mValueType;
            output << sep << (drf.mWritable ? 'y' : 'n');
            if (!drf.mValueUnits.empty()) {
                output << sep << drf.mValueUnits;
                if (!drf.mDescription.empty()) {
                    output << sep << drf.mDescription;
                }
            }
        }
        output << std::endl;
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

std::uint64_t DatarefsFile::generateId() {
    mLastId += 1;
    return mLastId;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void DatarefsFile::searchIdDuplicate() {
    using namespace std::string_literals;
    const auto uint64Max = std::numeric_limits<std::uint64_t>::max();
    for (auto iter = mData.begin(); iter != mData.end(); ++iter) {
        auto findIter = std::find_if(iter, mData.end(), [&](const auto & val) {
            if (iter->mId == uint64Max || val.mId == uint64Max) {
                return false;
            }
            return iter->mId == val.mId;
        });
        if (findIter != mData.end()) {
            throw std::domain_error(ExcTxt("found id duplicate <"s.append(std::to_string(iter->mId)).append(">")));
        }
    }
}

void DatarefsFile::searchKeyDuplicate() {
    using namespace std::string_literals;
    for (auto iter = mData.begin(); iter != mData.end(); ++iter) {
        auto findIter = std::find_if(iter, mData.end(), [&](const auto & val) {
            return iter->mKey == val.mKey;
        });
        if (findIter != mData.end()) {
            throw std::domain_error(ExcTxt("found key duplicate <"s.append(iter->mKey).append(">")));
        }
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
