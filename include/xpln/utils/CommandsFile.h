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
#include <functional>
#include <string>
#include <iosfwd>
#include <algorithm>

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

    bool isIdValid() const { return mId != invalidId(); }

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

public:

    //-------------------------------------------------------------------------
    /// \name IO
    /// @{

    /*!
     * \details Opens file and call \link CommandsFile::loadStream \endlink for it.
     * \exception std::exception
     */
    XpObjLib static bool loadFile(const std::string & filePath, const std::function<bool(const Command &)> & callback);

    /*!
     * \details Loads dataref from stream.
     * \param [in, out] input 
     * \param [in] callback this will be called for each parsed command. 
     *                      If you want to stop the process return false from the callback.
     * \return True if whole file is processed and callback did not return false otherwise false.
     * \exception std::exception
     */
    XpObjLib static bool loadStream(std::istream & input, const std::function<bool(const Command &)> & callback);

    //-------------------------------------------------------------------------

    /*!
     * \details Opens file and call \link CommandsFile::saveStream \endlink for it and then save one.
     * \exception std::exception
     */
    XpObjLib static void saveFile(const std::string & filePath, const std::function<bool(Command &)> & callback);

    /*!
     * \details Saves dataref to stream.
     * \param [in, out] output
     * \param [in] callback you have to fill data. If there are no any data anymore return false.
     * \exception std::exception
     */
    XpObjLib static void saveStream(std::ostream & output, const std::function<bool(Command &)> & callback);

    /// @}
    //-------------------------------------------------------------------------
    /// \name Helpers
    /// @{

    /*!
     * \details Searches duplicates.
     * \param [in] container
     * \param [in] fn
     * \return Iterator to found duplicate or Container::end()
     */
    template<typename Container>
    static typename Container::const_iterator duplicate(const Container & container,
                                                        std::function<bool(const typename Container::value_type & v1,
                                                                           const typename Container::value_type & v2)> fn) {

        for (auto iter = container.begin(); iter != container.end(); ++iter) {
            auto findIter = std::find_if(iter, container.end(), [&](const auto & val) { return fn(*iter, val); });
            if (findIter != container.end()) {
                return findIter;
            }
        }
        return container.end();
    }

    /// @}
    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
