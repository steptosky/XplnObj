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

#include "xpln/obj/ObjLightParam.h"
#include "xpln/obj/Transform.h"
#include "sts/string/StringUtils.h"
#include "exceptions/defines.h"
#include "converters/Defines.h"

namespace xobj {

/********************************************************************************************************/
///////////////////////////////////////* Constructors/Destructor *////////////////////////////////////////
/********************************************************************************************************/

ObjLightParam::ObjLightParam() {
    setObjectName("Param light");
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjLightParam::setParams(const std::string & params, const LightUtils::ParamExpanderMap & expander) {
    using namespace std::string_literals;

    mIsSpill = false;
    mIsDirection = false;
    mDirection.clear();
    mBillboardScale = 1.0f;

    auto expanderCopy = expander;
    for (auto & pair : expanderCopy) {
        if (pair.first == "direction_sp" || pair.first == "direction") {
            mIsDirection = true;
            const auto expandedStrVar = pair.second();
            const auto strVars = sts::MbStrUtils::splitToVector(pair.second(), " ");
            if (pair.first == "direction_sp") {
                if (strVars.size() != 3) {
                    throw std::runtime_error(ExcTxt("$direction_sp expander returned incorrect [X Y Z] value: "s.append(expandedStrVar)));
                }
                mIsSpill = true;
                mDirection.set(std::stof(strVars[0]), std::stof(strVars[1]), std::stof(strVars[2]));
                pair.second = []() { return "$direction_sp"; };
            }
            else {
                if (strVars.size() != 4) {
                    throw std::runtime_error(ExcTxt("$direction expander returned incorrect [X Y Z S] value: "s.append(expandedStrVar)));
                }
                mDirection.set(std::stof(strVars[0]), std::stof(strVars[1]), std::stof(strVars[2]));
                mBillboardScale = std::stof(strVars[3]);
                pair.second = []() { return "$direction"; };
            }
        }
    }
    mParams = LightUtils::replaceVariables(params, expanderCopy);
}

std::string ObjLightParam::params() const {
    if (!mIsDirection) {
        return mParams;
    }
    return LightUtils::replaceVariables(mParams, {
            {mIsSpill ? "direction_sp" : "direction", [&]() { return (mDirection * mBillboardScale).toString(PRECISION); }},
    });
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

eObjectType ObjLightParam::objType() const {
    return OBJ_LIGHT_PARAM;
}

void ObjLightParam::applyTransform(const TMatrix & tm, const bool) {
    tm.transformPoint(mPosition);
    if (mIsDirection) {
        tm.transformVector(mDirection);
    }
}

ObjAbstract * ObjLightParam::clone() const {
    return new ObjLightParam(*this);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
