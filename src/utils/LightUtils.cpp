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

#include "xpln/utils/LightUtils.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstring>
#include "sts/string/StringUtils.h"
#include "exceptions/defines.h"
#include "xpln/common/Logger.h"
#include <locale>

using namespace std::string_literals;

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

float LightUtils::spillConeWidthFromAngle(const float coneInRadians) {
    return std::cos(coneInRadians * 0.5f);
}

float LightUtils::spillConeWidthToAngle(const float simValue) {
    return std::acos(simValue) * 2.0f;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

float LightUtils::billboardConeWidthFromAngle(const float coneInRadians) {
    const auto angleCos = std::cos(coneInRadians * 0.5f);
    return angleCos / (angleCos - 1.0f);
}

float LightUtils::billboardConeWidthToAngle(const float simValue) {
    return std::acos(simValue / (simValue - 1)) * 2.0f;
}

std::tuple<std::string, float> LightUtils::billboardCorrectConeAngle(const std::string & directionVar, const float currentAngle) {
    if (directionVar.find(':') == std::string::npos) {
        return std::make_tuple(directionVar, currentAngle);
    }
    //---------------------------------
    auto vars = sts::MbStrUtils::splitToVector(directionVar, ":");
    assert(vars.size() == 2);
    if (vars[0] != "$direction") {
        throw std::runtime_error(ExcTxt(directionVar + " - doesn't have $direction directionVar"));
    }
    auto & additional = vars[1];
    if (additional.size() < 2) {
        throw std::runtime_error(ExcTxt(directionVar + " - has incorrect additional parameter"));
    }
    if (additional.front() != 'a') {
        throw std::runtime_error(ExcTxt(directionVar + " - has incorrect additional parameter name should be 'a'"));
    }
    //---------------------------------
    const auto isNotDigitFn = [](const auto ch) {
        return !std::isdigit(ch) && ch != '.' && ch != ',';
    };

    if (additional[1] == '+') {
        const std::string valStr(additional.begin() + 2, additional.end());
        if (std::any_of(valStr.begin(), valStr.end(), isNotDigitFn)) {
            throw std::invalid_argument(ExcTxt(directionVar + " - has incorrect additional parameter value should be digit"));
        }
        return std::make_tuple(vars[0], currentAngle + std::stof(valStr));
    }
    if (additional[1] == '-') {
        const std::string valStr(additional.begin() + 2, additional.end());
        if (std::any_of(valStr.begin(), valStr.end(), isNotDigitFn)) {
            throw std::invalid_argument(ExcTxt(directionVar + " - has incorrect additional parameter value should be digit"));
        }
        return std::make_tuple(vars[0], currentAngle - std::stof(valStr));
    }
    const std::string valStr(additional.begin() + 1, additional.end());
    if (std::any_of(valStr.begin(), valStr.end(), isNotDigitFn)) {
        throw std::invalid_argument(ExcTxt(directionVar + " - has incorrect additional parameter value should be digit"));
    }
    return std::make_tuple(vars[0], std::stof(valStr));
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::string LightUtils::replaceVariables(const std::string & params, const ParamExpanderMap & paramsGetter) {
    using namespace std::string_literals;
    std::string out;
    const auto parameters = sts::MbStrUtils::splitToVector(params, " \n\r\t");
    for (const auto & p : parameters) {
        if (sts::MbStrUtils::startsWith(p, "$", 1)) {
            if (p.size() == 1) {
                throw std::runtime_error(ExcTxt("Empty variable is found"));
            }
            std::string var(p.begin() + 1, p.end());
            const auto varGetter = paramsGetter.find(var);
            if (varGetter == paramsGetter.end()) {
                throw std::runtime_error(ExcTxt("Can't find getter for variable <"s.append(var).append(">")));
            }
            out.append(varGetter->second()).append(" ");
        }
        else {
            out.append(p).append(" ");
        }
    }
    if (!out.empty()) {
        out.pop_back(); // remove last space
    }
    return out;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

std::vector<LightUtils::LightName> LightUtils::parseLights(const Path & filePath) {
    std::vector<LightName> out;
    std::ifstream file(filePath);
    if (!file) {
        throw std::system_error(errno, std::system_category(),
                                "Failed to open file: <"s.append(u8string(filePath)).append(">"));
    }
    out.reserve(1000);
    //----------------------------------------------
    const auto isSpace = [](const char ch) { return std::isspace(static_cast<unsigned char>(ch)); };
    const auto startWith = [](const std::string_view string, const std::string_view start) ->bool {
        return string.size() >= start.size() &&
               std::strncmp(string.data(), start.data(), start.size()) == 0;
    };
    //----------------------------------------------
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line == "A" || line == "850" || line == "LIGHT_SPECS" ||
            startWith(line, "TEXTURE") ||
            startWith(line, "X_DIVISIONS") ||
            startWith(line, "Y_DIVISIONS")) {
            continue;
        }

        // skip space on line start
        auto currPos = std::find_if_not(line.begin(), line.end(), isSpace);
        if (currPos == line.end() || *currPos == '#') {
            continue;
        }
        // skip the first word
        currPos = std::find_if(currPos, line.end(), isSpace);
        // skip space up to the second word
        currPos = std::find_if_not(currPos, line.end(), isSpace);
        // save start word position
        auto startName = currPos;
        // find word end

        currPos = std::find_if(currPos, line.end(), isSpace);

        LightName & name = out.emplace_back();
        std::size_t counter = 0;
        while (startName != currPos) {
            if (counter > LightName::mDataSize) {
                XULError << "Light name is too big, constraint is: " << LightName::mDataSize;
                break;
            }
            name.mData[counter] = *startName;
            ++startName;
            ++counter;
        }
        name.mData[counter] = '\0';
        name.mSize = counter;
    }
    //----------------------------------------------
    return out;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
