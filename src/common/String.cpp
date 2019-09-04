/*
**  Copyright(C) 2019, StepToSky
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

#include "xpln/common/String.h"
#include <codecvt>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

#ifdef _MSC_VER
inline std::string toMultiByte(const std::wstring_view s) {
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
    return convert.to_bytes(s.data(), s.data() + s.size());
}

String::String(const std::wstring & s) {
    mString = toMultiByte(s);
}

String & String::operator=(const std::wstring & s) {
    mString = toMultiByte(s);
    return *this;
}

String::String(const wchar_t * s)
    : mString(s ? toMultiByte(s) : "") {}

String & String::operator=(const wchar_t * s) {
    mString = s ? toMultiByte(s) : "";
    return *this;
}
#endif

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

std::optional<std::size_t> String::hasIllegalSymbolsForDataRef(const std::string_view & str) noexcept {
    for (std::size_t i = 0; i < str.size(); ++i) {
        const auto ch = str[i];
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch < 32 || ch > 126) {
            return i;
        }
    }
    return std::nullopt;
}

std::optional<std::size_t> String::hasIllegalSymbolsForPath(const std::string_view & str) noexcept {
    for (std::size_t i = 0; i < str.size(); ++i) {
        const auto ch = str[i];
        if (ch == '\t' || ch == '\n' || ch == '\r' || ch < 32 || ch > 126) {
            return i;
        }
    }
    return std::nullopt;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

const std::string & String::none() noexcept {
    static std::string none("none");
    return none;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
