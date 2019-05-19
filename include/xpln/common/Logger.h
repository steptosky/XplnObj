#pragma once

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

#include "xpln/Export.h"
#include <stsff/logging/BaseLogger.h>

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

namespace xobj {

class Logger final : public stsff::logging::BaseLogger {
public:

    //-------------------------------------------------------------------------
    /// @{

    Logger()
        : BaseLogger("XLIB") { }

    Logger(const Logger &) = default;
    Logger(Logger &&) = default;

    virtual ~Logger() = default;

    Logger & operator=(const Logger &) = default;
    Logger & operator=(Logger &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @}

    XpObjLib static Logger mInstance;

    /// @}
    //-------------------------------------------------------------------------

};

}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

#define LOG_CATEGORY_FOR_USER "user"

// Message with a category for user showing (UL = user log)
#define XULVar(VAR)   LcVar(VAR,xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER)
#define XULCritical   LcCritical(xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER)
#define XULError      LcError(xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER)
#define XULWarning    LcWarning(xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER)
#define XULSuccess    LcSuccess(xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER)
#define XULInfo       LcInfo(xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER)
#define XULMessage    LcMessage(xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER)
#define XULDebug      LcDebug(xobj::Logger::mInstance)
#define XULLevel(LVL) LcLevel(xobj::Logger::mInstance,LOG_CATEGORY_FOR_USER,LVL)

#define XLVar(VAR)    LVar(VAR,xobj::Logger::mInstance)
#define XLCritical    LCritical(xobj::Logger::mInstance)
#define XLError       LError(xobj::Logger::mInstance)
#define XLWarning     LWarning(xobj::Logger::mInstance)
#define XLSuccess     LSuccess(xobj::Logger::mInstance)
#define XLInfo        LInfo(xobj::Logger::mInstance)
#define XLMessage     LMessage(xobj::Logger::mInstance)
#define XLDebug       LDebug(xobj::Logger::mInstance)
#define XLLevel(LVL)  LLevel(xobj::Logger::mInstance,LVL)

#ifndef TOTEXT
#   define TOTEXT(x) #x
#endif

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
