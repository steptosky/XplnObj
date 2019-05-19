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

#include <stsff/logging/BaseLogger.h>

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

namespace xobj {

class Logger final : public stsff::logging::BaseLogger {
public:

    //-------------------------------------------------------------------------
    /// @{

    Logger() = default;
    Logger(const Logger &) = default;
    Logger(Logger &&) = default;

    virtual ~Logger() = default;

    Logger & operator=(const Logger &) = default;
    Logger & operator=(Logger &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @}

    static Logger mInstance;

    /// @}
    //-------------------------------------------------------------------------

};

}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

#define LOG_CATEGORY_FOR_USER "Xlb"

// Message with a category for user showing (UL = user log)
#define ULVar(VAR,L)   LcVar(VAR,L,LOG_CATEGORY_FOR_USER)
#define ULCritical(L)  LcCritical(L,LOG_CATEGORY_FOR_USER)
#define ULError(L)     LcError(L,LOG_CATEGORY_FOR_USER)
#define ULWarning(L)   LcWarning(L,LOG_CATEGORY_FOR_USER)
#define ULSuccess(L)   LcSuccess(L,LOG_CATEGORY_FOR_USER)
#define ULInfo(L)      LcInfo(L,LOG_CATEGORY_FOR_USER)
#define ULMessage(L)   LcMessage(L,LOG_CATEGORY_FOR_USER)
#define ULDebug(L)     LcDebug(L)
#define ULLevel(L,LVL) LcLevel(L,LOG_CATEGORY_FOR_USER,LVL)

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
