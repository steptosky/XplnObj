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
 * \brief Represents one dataref.
 * \details This class contains ID that isn't used in the original datarefs.
 *          We use it for our company internal purposes you may ignore it.
 * \ingroup Utils
 */
class Dataref {
public:

    Dataref() = default;
    Dataref(const Dataref &) = default;
    Dataref(Dataref &&) = default;

    ~Dataref() = default;

    Dataref & operator=(const Dataref &) = default;
    Dataref & operator=(Dataref &&) = default;

    //-------------------------------------------------------------------------

    bool mWritable = false;
    std::uint64_t mId = invalidId();
    std::string mKey;
    std::string mValueType;
    std::string mValueUnits;
    std::string mDescription;

    bool isIdValid() const { return mId != invalidId(); }

    //-------------------------------------------------------------------------

    /*!
     * \return Value that is used for invalid Id.
     */
    XpObjLib static std::uint64_t invalidId();

    /*!
     * \details The key that starts from digit can be considered as an id. 
     *          So your dataref key must not be started with digits.
     * \return True if the specified string key can be considered as id.
     */
    XpObjLib static bool isKeyId(const std::string & key);

    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \brief Represents datarefs file.
 * \details This class contains some methods that 
 *          are not used in the original datarefs.
 *          We use them for our company internal purposes you may ignore them.
 * \ingroup Utils
 */
class DatarefsFile {

    //-------------------------------------------------------------------------
    /// @{

    DatarefsFile() = default;
    DatarefsFile(const DatarefsFile &) = default;
    DatarefsFile(DatarefsFile &&) = default;

    ~DatarefsFile() = default;

    DatarefsFile & operator=(const DatarefsFile &) = default;
    DatarefsFile & operator=(DatarefsFile &&) = default;

    /// @}
    //-------------------------------------------------------------------------

public:

    //-------------------------------------------------------------------------
    /// \name IO
    /// @{

    /*!
     * \details Opens file and call \link DatarefsFile::loadStream \endlink for it.
     * \exception std::exception
     */
    XpObjLib static bool loadFile(const std::string & filePath, const std::function<bool(const Dataref &)> & callback);

    /*!
     * \details Loads dataref from stream.
     * \param [in, out] input 
     * \param [in] callback this will be called for each parsed dataref. 
     *                      If you want to stop the process return false from the callback.
     * \return True if whole file is processed and callback did not return false otherwise false.
     * \exception std::exception
     */
    XpObjLib static bool loadStream(std::istream & input, const std::function<bool(const Dataref &)> & callback);

    //-------------------------------------------------------------------------

    /*!
     * \details Opens file and call \link DatarefsFile::saveStream \endlink for it and then save one.
     * \exception std::exception
     */
    XpObjLib static void saveFile(const std::string & filePath, const std::function<bool(Dataref &)> & callback);

    /*!
     * \details Saves dataref to stream.
     * \param [in, out] output
     * \param [in] callback you have to fill data. If there are no any data anymore return false.
     * \exception std::exception
     */
    XpObjLib static void saveStream(std::ostream & output, const std::function<bool(Dataref &)> & callback);

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
