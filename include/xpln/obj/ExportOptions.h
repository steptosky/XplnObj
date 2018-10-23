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
#include <cstdint>
#include "xpln/Export.h"
#include "xpln/enums/eExportOptions.h"

namespace xobj {

class ObjWriter;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation class of the 'obj' exporter options.
 */
class ExportOptions {
public:

    //-------------------------------------------------------------------------
    /// @{

    XpObjLib ExportOptions();
    virtual ~ExportOptions() = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    XpObjLib bool isEnabled(eExportOptions option) const;
    XpObjLib void enable(eExportOptions option);
    XpObjLib void disable(eExportOptions option);
    XpObjLib virtual void reset();

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \details Gets option flags.
     * \remark It can be useful for serialization/deserialization.
     * \return flags.
     */
    XpObjLib uint64_t optionFlags() const;

    /*!
     * \details Sets option flags.
     * \remark It can be useful for serialization/deserialization.
     * \param [in] flags
     */
    XpObjLib void setOptionFlags(std::uint64_t flags);

    /// @}
    //-------------------------------------------------------------------------

private:

    std::uint64_t mOptionFlags;
    std::string mSignature;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
