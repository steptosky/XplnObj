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
#include <cassert>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <limits>
#include <algorithm>

namespace xobj {

/**************************************************************************************************/
/////////////////////////////////////////* Static area *////////////////////////////////////////////
/**************************************************************************************************/

std::uint64_t Dataref::invalidId() {
    // It hides 'max' because 3Ds Max uses win api and it conflicts with win min/max
    return std::numeric_limits<std::uint64_t>::max();
}

bool Dataref::isKeyId(const std::string & key) {
    if (key.empty()) {
        return false;
    }
    for (auto ch : key) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

std::uint64_t Dataref::keyToId(const std::string & key) {
    return std::stoul(key);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool DatarefsFile::loadFile(const Path & filePath, const std::function<bool(const Dataref &)> & callback) {
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

void DatarefsFile::saveFile(const Path & filePath, const std::function<bool(Dataref &)> & callback) {
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

bool DatarefsFile::loadStream(std::istream & input, const std::function<bool(const Dataref &)> & callback) {
    assert(callback);
    std::string line;
    Dataref data;

    const auto isDelimiter = [](const auto ch) { return ch == '\t'; };

    // remove firs line as the datarefs format
    // uses it for just an information.
    if (! std::getline(input, line)) {
        return false;
    }

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        // skip space
        auto currPos = std::find_if_not(line.begin(), line.end(), std::isblank);
        if (currPos == line.end()) {
            continue;
        }

        data.clear();
        //------------------
        if (std::isdigit(*currPos)) {
            auto iter = std::find_if_not(currPos, line.end(), std::isdigit);
            if (iter != line.end()) {
                if (*iter == ':') {
                    data.mId = Dataref::keyToId(std::string(currPos, iter));
                    currPos = iter;
                    ++currPos; // skip ':'
                }

                currPos = std::find_if_not(currPos, line.end(), std::isblank);
                iter = std::find_if(currPos, line.end(), std::isblank);
                data.mKey.assign(currPos, iter);
                currPos = iter;
            }
            else {
                data.mKey.assign(currPos, iter);
                currPos = iter;
            }
        }
        else {
            const auto iter = std::find_if(currPos, line.end(), std::isblank);
            data.mKey.assign(currPos, iter);
            currPos = iter;
        }
        //------------------
        currPos = std::find_if(currPos, line.end(), isDelimiter);
        currPos = std::find_if_not(currPos, line.end(), isDelimiter); // remove delimiters

        auto nextDelimiter = std::find_if(currPos, line.end(), isDelimiter);
        data.mValueType.assign(currPos, nextDelimiter);
        currPos = nextDelimiter;
        //------------------
        currPos = std::find_if_not(currPos, line.end(), isDelimiter); // remove delimiters

        nextDelimiter = std::find_if(currPos, line.end(), isDelimiter);
        const std::string tmp(currPos, nextDelimiter);
        data.mWritable = !tmp.empty() && tmp.front() == 'y';
        currPos = nextDelimiter;
        //------------------
        currPos = std::find_if_not(currPos, line.end(), isDelimiter); // remove delimiters

        nextDelimiter = std::find_if(currPos, line.end(), isDelimiter);
        data.mValueUnits.assign(currPos, nextDelimiter);
        currPos = nextDelimiter;
        //------------------
        currPos = std::find_if_not(currPos, line.end(), isDelimiter); // remove delimiters
        data.mDescription.assign(currPos, line.end());
        //------------------
        if (!callback(data)) {
            return false;
        }
    }
    return true;
}

void DatarefsFile::saveStream(std::ostream & output, const std::function<bool(Dataref &)> & callback) {
    output << std::endl;
    const char * delimiter = "\t";
    Dataref drf;
    while (callback(drf)) {
        if (drf.mId != Dataref::invalidId()) {
            output << std::setfill('0') << std::setw(6) << drf.mId << ":" << delimiter;
        }
        output << drf.mKey;
        if (!drf.mValueType.empty()) {
            output << delimiter << drf.mValueType;
            output << delimiter << (drf.mWritable ? 'y' : 'n');
            if (!drf.mValueUnits.empty()) {
                output << delimiter << drf.mValueUnits;
                if (!drf.mDescription.empty()) {
                    output << delimiter << drf.mDescription;
                }
            }
        }
        output << std::endl;
        drf = Dataref();
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void Dataref::fillEmptyFields(const std::string & val) {
    if (!mDescription.empty() && mValueUnits.empty()) {
        mValueUnits = val;
    }
    if (!mValueUnits.empty() && mValueType.empty()) {
        mValueType = val;
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
