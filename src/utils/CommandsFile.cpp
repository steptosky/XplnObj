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
#include <fstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include "xpln/utils/DatarefsFile.h"

namespace xobj {

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

std::uint64_t Command::invalidId() {
    // It hides 'max' because 3Ds Max uses win api and it conflicts with win min/max
    return Dataref::invalidId();
}

bool Command::isKeyId(const std::string & key) {
    return Dataref::isKeyId(key);
}

std::uint64_t Command::keyToId(const std::string & key) {
    return Dataref::keyToId(key);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool CommandsFile::loadFile(const Path & filePath, const std::function<bool(const Command &)> & callback) {
    using namespace std::string_literals;
    std::ifstream file(filePath, std::iostream::in);
    if (!file) {
        throw std::runtime_error(ExcTxt("can't open file <"s.append(sts::toMbString(filePath)).append(">")));
    }
    try {
        const auto res = loadStream(file, callback);
        file.close();
        return res;
    }
    catch (...) {
        file.close();
        throw;
    }
}

void CommandsFile::saveFile(const Path & filePath, const std::function<bool(Command &)> & callback) {
    using namespace std::string_literals;
    std::ofstream file(filePath, std::iostream::out);
    if (!file) {
        throw std::runtime_error(ExcTxt("can't open file <"s.append(sts::toMbString(filePath)).append(">")));
    }
    try {
        saveStream(file, callback);
        file.close();
    }
    catch (...) {
        file.close();
        throw;
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool CommandsFile::loadStream(std::istream & input, const std::function<bool(const Command &)> & callback) {
    std::string line;
    Command data;

    const auto isBlank = [](const char ch) { return std::isblank(static_cast<unsigned char>(ch)); };
    const auto isDigit = [](const char ch) { return std::isdigit(static_cast<unsigned char>(ch)); };

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        // skip space
        auto currPos = std::find_if_not(line.begin(), line.end(), isBlank);
        if (currPos == line.end()) {
            continue;
        }

        data.clear();
        //------------------
        if (isDigit(*currPos)) {
            auto iter = std::find_if_not(currPos, line.end(), isDigit);
            if (iter != line.end()) {
                if (*iter == ':') {
                    data.mId = Command::keyToId(std::string(currPos, iter));
                    currPos = iter;
                    ++currPos; // skip ':'
                }

                currPos = std::find_if_not(currPos, line.end(), isBlank);
                iter = std::find_if(currPos, line.end(), isBlank);
                data.mKey.assign(currPos, iter);
                currPos = iter;
            }
            else {
                data.mKey.assign(currPos, iter);
                currPos = iter;
            }
        }
        else {
            const auto iter = std::find_if(currPos, line.end(), isBlank);
            data.mKey.assign(currPos, iter);
            currPos = iter;
        }
        //------------------
        currPos = std::find_if_not(currPos, line.end(), isBlank);
        data.mDescription.assign(currPos, line.end());

        if (!callback(data)) {
            return false;
        }
    }
    return true;
}

void CommandsFile::saveStream(std::ostream & output, const std::function<bool(Command &)> & callback) {
    const char * sep = "    ";
    Command cmd;
    while (callback(cmd)) {
        if (cmd.mId != Command::invalidId()) {
            output << std::setfill('0') << std::setw(6) << cmd.mId << ":" << sep;
        }
        output << cmd.mKey;
        if (!cmd.mDescription.empty()) {
            output << sep << cmd.mDescription;
        }
        output << std::endl;
        cmd = Command();
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
