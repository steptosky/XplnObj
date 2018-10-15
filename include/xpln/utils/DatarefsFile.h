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
#include <limits>
#include <vector>

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
    std::uint64_t mId = std::numeric_limits<std::uint64_t>::max();
    std::string mKey;
    std::string mValueType;
    std::string mValueUnits;
    std::string mDescription;

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
public:

    //-------------------------------------------------------------------------
    /// @{

    typedef std::vector<Dataref> Container;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    DatarefsFile() = default;
    ~DatarefsFile() = default;

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
