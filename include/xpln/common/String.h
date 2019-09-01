#pragma once

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

#include "xpln/Export.h"
#include "Logger.h"
#include <string>
#include <optional>
#include <string_view>

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

namespace xobj {

class String final {
public:

    //---------------------------------------------------
    ///@{

    String() = default;
    String(const String &) = default;
    String(String &&) = default;

    ~String() = default;

    String & operator=(const String &) = default;
    String & operator=(String &&) = default;

    ///@}
    //---------------------------------------------------
    ///@{

    String(const std::string_view s) noexcept
        : mString(s) {}

    String & operator=(const std::string_view s) {
        mString = s;
        return *this;
    }

#ifdef _MSC_VER
    XpObjLib String(std::wstring_view s);
    XpObjLib String & operator=(std::wstring_view s);
#endif

    ///@}
    //---------------------------------------------------
    ///@{

    bool operator==(const String & s) const noexcept { return mString == s.mString; }
    bool operator!=(const String & s) const noexcept { return mString != s.mString; }

    ///@}
    //---------------------------------------------------
    ///@{

    XpObjLib static std::optional<std::size_t> hasIllegalSymbolsForDataRef(const std::string_view & str) noexcept;
    XpObjLib static std::optional<std::size_t> hasIllegalSymbolsForPath(const std::string_view & str) noexcept;
    std::optional<std::size_t> hasIllegalSymbolsForDataRef() const noexcept { return hasIllegalSymbolsForDataRef(mString); }
    std::optional<std::size_t> hasIllegalSymbolsForPath() const noexcept { return hasIllegalSymbolsForPath(mString); }

    ///@}
    //---------------------------------------------------
    ///@{

    bool isEmpty() const { return mString.empty(); }
    bool isNone() const { return mString == none(); }
    void clear() { mString.clear(); }

    ///@}
    //---------------------------------------------------
    ///@{

    const std::string & str() const noexcept { return mString; }
    std::string & str() noexcept { return mString; }
    XpObjLib static const std::string & none() noexcept;

    ///@}
    //---------------------------------------------------

private:

    std::string mString;

};
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<>
inline stsff::logging::LogMessage & stsff::logging::LogMessage::operator<<<xobj::String>(const xobj::String & msg) noexcept {
    write(msg.str());
    return *this;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
