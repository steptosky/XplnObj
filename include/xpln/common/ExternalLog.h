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

#include <string>
#include "xpln/Export.h"

#define LOG_CATEGORY_FOR_USER "Xlb"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Allows you to receive the messages from the library's log system into your own function.
 * \note The category \link LOG_CATEGORY_FOR_USER \endlink is set when the library wants to show current message to the end-user.
 */
class ExternalLog {
public:

    enum eType {
        Fatal = 0,
        Critical = 1,
        Error = 2,
        Warning = 3,
        Msg = 4,
        Debug = 5,
    };

    /*!
     * \details Log callback.
     * \param [in] type function message type
     * \param [in] msg function message
     * \param [in] file function source file
     * \param [in] line function line of the source file
     * \param [in] function objectName
     * \param [in] category of the message
     */
    typedef void (*CallBack)(eType type, const char * msg,
                             const char * file, int line, const char * function,
                             const char * category);

    /*!
     * \details If a callback is registered then all logs from this library will be sent to the callback.
     * \param [in] callBack function
     */
    XpObjLib static void registerCallBack(CallBack callBack);

    /*!
     * \details Unregisters current callback.
     */
    XpObjLib static void unRegisterCallBack();

    /*!
     * \details Generates the string that can be used in about window.
     * \param [in] useWinEol true = "\r\n", false = "\n"
     * \return ASCII string for about window.
     */
    XpObjLib static std::string about(bool useWinEol = false);

    /*!
    * \details Generates the short string that can be used in about window.
    * \param [in] useWinEol true = "\r\n", false = "\n"
    * \return ASCII string for about window.
    */
    XpObjLib static std::string shortAbout(bool useWinEol = false);

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
