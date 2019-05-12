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

#include "common/Logger.h"
#include "xpln/common/ExternalLog.h"
#include "xpln/Info.h"

#ifndef NDEBUG
#	define LOGLEVEL sts::BaseLogger::eType::Debug
#else
#	define LOGLEVEL sts::BaseLogger::eType::Msg
#endif

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

sts::BaseLogger * sts::BaseLogger::mInstance = nullptr;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

void ExternalLog::registerCallBack(const CallBack callback) {
    sts::BaseLogger::instance().setCallBack(reinterpret_cast<sts::BaseLogger::CallBack>(callback));
    sts::BaseLogger::instance().setLevel(LOGLEVEL);
}

void ExternalLog::unRegisterCallBack() {
    sts::BaseLogger::instance().removeCallBack();
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::string ExternalLog::about(const bool useWinEol) {
    std::stringstream stream;
    const char * eol = useWinEol ? "\r\n" : "\n";
    //-------------------------------------------------------------------------

    stream << "Project: " << XOBJ_PROJECT_NAME << eol;
    stream << "Organization: " << XOBJ_ORGANIZATION_NAME << " (" << XOBJ_ORGANIZATION_WEBLINK << ")" << eol;
    stream << "Desc: " << XOBJ_PROJECT_DESCRIPTION << eol;
    stream << "Link: " << XOBJ_PROJECT_WEBLINK << eol;

    stream << "Version: " XOBJ_VERSION_STRING << "-" << XOBJ_RELEASE_TYPE << "+" << XOBJ_VCS_REVISION << " (" << XOBJ_VCS_BRANCH << ") "
            << XOBJ_COMPILE_DATE << Debug(" (" << XOBJ_COMPILE_TIME << ") " << "DEBUG" <<) eol;

    stream << "Compiler: " << XOBJ_COMPILER_NAME << " " << XOBJ_COMPILER_VERSION << eol;
    stream << XOBJ_COPYRIGHT << eol;
    stream << "Contacts: " << XOBJ_ORGANIZATION_WEBLINK << eol;
    stream << "License: " << XOBJ_LICENSE_TYPE << eol;
    stream << "Sources: " << XOBJ_PROJECT_SOURCES_WEBLINK << eol;

    stream << "Contributors: " << eol;
    for (size_t i = 0; i < XOBJ_ARRAY_LENGTH(XOBJ_CONTRIBUTORS); ++i) {
        stream << "    " << XOBJ_CONTRIBUTORS[i] << eol;
    }

    //-------------------------------------------------------------------------
    return stream.str();
}

std::string ExternalLog::shortAbout(const bool useWinEol) {
    std::stringstream stream;
    const char * eol = useWinEol ? "\r\n" : "\n";
    //-------------------------------------------------------------------------

    stream << "Project: " << XOBJ_PROJECT_NAME << eol;
    stream << "Version: " XOBJ_VERSION_STRING << "-" << XOBJ_RELEASE_TYPE << "+" << XOBJ_VCS_REVISION << " (" << XOBJ_VCS_BRANCH << ") "
            << XOBJ_COMPILE_DATE << Debug(" (" << XOBJ_COMPILE_TIME << ") " << "DEBUG" <<) eol;
    stream << "Compiler: " << XOBJ_COMPILER_NAME << " " << XOBJ_COMPILER_VERSION << eol;

    //-------------------------------------------------------------------------
    return stream.str();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
