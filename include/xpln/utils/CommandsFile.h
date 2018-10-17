#pragma once

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

#include "xpln/Export.h"
#include <cstdint>
#include <string>
#include <iosfwd>
#include <vector>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*! 
 * \brief Represents one command.
 * \details This class contains ID that isn't used in the original commands.
 *          We use it for our company internal purposes you may ignore it.
 * \ingroup Utils
 */
class Command {
public:

    Command() = default;
    Command(const Command &) = default;
    Command(Command &&) = default;

    ~Command() = default;

    Command & operator=(const Command &) = default;
    Command & operator=(Command &&) = default;

    //-------------------------------------------------------------------------

    std::uint64_t mId = invalidId();
    std::string mKey;
    std::string mDescription;

    //-------------------------------------------------------------------------

    /*!
     * \return Value that is used for invalid Id.
     */
    XpObjLib static std::uint64_t invalidId();

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \brief Represents commands file.
 * \details This class contains some methods that 
 *          are not used in the original commands.
 *          We use them for our company internal purposes you may ignore them.
 * \ingroup Utils
 */
class CommandsFile {
public:

    //-------------------------------------------------------------------------
    /// @{

    typedef std::vector<Command> Container;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    CommandsFile() = default;
    CommandsFile(const CommandsFile &) = default;
    CommandsFile(CommandsFile &&) = default;

    ~CommandsFile() = default;

    CommandsFile & operator=(const CommandsFile &) = default;
    CommandsFile & operator=(CommandsFile &&) = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    Container mData;

    /// @}
    //-------------------------------------------------------------------------
    /// \name IO
    /// @{

    /*!
     * \exception std::exception
     */
    XpObjLib void loadFile(const std::string & filePath);

    /*!
     * \exception std::exception
     */
    XpObjLib void loadStream(std::istream & input);

    /*!
     * \exception std::exception
     */
    XpObjLib void saveFile(const std::string & filePath);

    /*!
     * \exception std::exception
     */
    XpObjLib void saveStream(std::ostream & output);

    /// @}
    //-------------------------------------------------------------------------
    /// \name For our company internal purposes 
    /// @{

    XpObjLib std::uint64_t generateId();

    /*!
     * \exception std::exception
     */
    XpObjLib void searchIdDuplicate();

    /*!
     * \exception std::exception
     */
    XpObjLib void searchKeyDuplicate();

    /// @}
    //-------------------------------------------------------------------------

private:

    std::uint64_t mLastId = 0;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
