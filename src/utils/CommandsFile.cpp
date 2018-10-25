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
#include <utility>
#include <limits>
#include "xpln/utils/DatarefsFile.h"
#include "sts/string/StringUtils.h"

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
        // todo sts::toMbString(filePath) may work incorrectly with UNICODE
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

bool CommandsFile::loadStream(std::istream & input, const std::function<bool(const Command &)> & callback) {
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

        if (Command::isKeyId(extractedVal.first)) {
            cmd.mId = Command::keyToId(extractedVal.first);
            extractedVal = extractValueFn(extractedVal.second);
        }

        cmd.mKey = extractedVal.first;
        cmd.mDescription = extractedVal.second;

        if (!callback(cmd)) {
            return false;
        }
    }
    return true;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void CommandsFile::saveFile(const Path & filePath, const std::function<bool(Command &)> & callback) {
    using namespace std::string_literals;
    std::ofstream file(filePath, std::iostream::out);
    if (!file) {
        // todo sts::toMbString(filePath) may work incorrectly with UNICODE
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

void CommandsFile::saveStream(std::ostream & output, const std::function<bool(Command &)> & callback) {
    const char * sep = "    ";
    Command cmd;
    while (callback(cmd)) {
        if (cmd.mId != std::numeric_limits<std::uint64_t>::max()) {
            output << std::setfill('0') << std::setw(6) << cmd.mId << sep;
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
