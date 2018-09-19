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
#include <cmath>
#include "sts/string/StringUtils.h"
#include "exceptions/defines.h"

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
}
