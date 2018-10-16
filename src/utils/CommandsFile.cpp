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

#include "xpln/utils/CommandsFile.h"
#include "exceptions/defines.h"
#include "sts/string/StringUtils.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <utility>
#include <limits>

namespace xobj {

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

std::uint64_t Command::invalidId() {
    // It hides 'max' because 3Ds Max uses win api and it conflicts with win min/max
    return std::numeric_limits<std::uint64_t>::max();
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void CommandsFile::loadFile(const std::string & filePath) {
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

void CommandsFile::loadStream(std::istream & input) {
    mData.clear();
    mData.reserve(1000);
    mLastId = 0;
    std::string line;

    // [val, rest string]
    const auto extractValueFn = [](const std::string & str) ->std::pair<std::string, std::string> {
        const auto pos = str.find_first_of(' ');
        if (pos == std::string::npos) {
            return std::make_pair(std::string(), str);
        }
        return std::make_pair(sts::MbStrUtils::trimCopy(str.substr(0, pos)),
                              sts::MbStrUtils::trimCopy(str.substr(pos)));
    };

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        if (line.front() == '#') {
            continue;
        }
        Command cmd;
        auto extractedVal = extractValueFn(line);

        if (std::isdigit(extractedVal.first.front())) {
            cmd.mId = std::stoul(extractedVal.first);
            mLastId = std::max(mLastId, cmd.mId);
            extractedVal = extractValueFn(extractedVal.second);
        }

        cmd.mKey = extractedVal.first;
        cmd.mDescription = extractedVal.second;

        mData.emplace_back(std::move(cmd));
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void CommandsFile::saveFile(const std::string & filePath) {
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

void CommandsFile::saveStream(std::ostream & output) {
    const char * sep = "    ";
    for (auto & drf : mData) {
        if (drf.mId != std::numeric_limits<std::uint64_t>::max()) {
            output << std::setfill('0') << std::setw(6) << drf.mId << sep;
        }
        output << drf.mKey;
        if (!drf.mDescription.empty()) {
            output << sep << drf.mDescription;
        }
        output << std::endl;
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

std::uint64_t CommandsFile::generateId() {
    mLastId += 1;
    return mLastId;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void CommandsFile::searchIdDuplicate() {
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

void CommandsFile::searchKeyDuplicate() {
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
