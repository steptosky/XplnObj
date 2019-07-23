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

#include <memory>
#include <string>
#include "xpln/Export.h"
#include "xpln/common/Path.h"
#include "xpln/common/IInterrupter.h"
#include "IOStatistic.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ExportContext {
public:

    //-------------------------------------------------------------------------
    /// @{

    ExportContext() = default;

    /*! \see \link ExportContext::setObjFile \endlink */
    explicit ExportContext(const Path & fullFilePath) { setObjFile(fullFilePath); }

    ExportContext(const ExportContext &) = delete;
    ExportContext(ExportContext &&) = delete;

    virtual ~ExportContext() = default;

    ExportContext & operator=(const ExportContext &) = delete;
    ExportContext & operator=(ExportContext &&) = delete;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \note Takes ownership.
     */
    XpObjLib void setInterrupter(IInterrupter * interruptor);

    /*!
     * \return Always valid pointer to interrupter.
     */
    XpObjLib IInterrupter * interrupter();

    void setStatistic(const IOStatistic & stats) { mStatistic = stats; }
    IOStatistic & statistic() { return mStatistic; }
    const IOStatistic & statistic() const { return mStatistic; }

    void setSignature(const std::string & signature) { mSignature = signature; }
    const std::string & signature() const { return mSignature; }

    /// @}
    //-------------------------------------------------------------------------
    /// \name Files
    /// @{

    /*!
     * \details File path for obj writing.
     * \param [in] fullFilePath
     */
    void setObjFile(const Path & fullFilePath) { mObjFile = fullFilePath; }

    /*!
     * \details File path for datarefs reading.
     *          These datarefs are used if you specified them as id.
     * \todo better description what it is for.
     * \param [in] fullFilePath
     */
    void setDatarefsFile(const Path & fullFilePath) { mDatarefsFile = fullFilePath; }

    /*!
     * \details File path for commands reading.
     *          These commands are used if you specified them as id.
     * \todo better description what it is for.
     * \param [in] fullFilePath
     */
    void setCommandsFile(const Path & fullFilePath) { mCommandsFile = fullFilePath; }

    /*!
     * \details Enable/disable printing time stamp at the end of the obj file.
     * \param [in] state
     */
    void setPrintTimeStamp(const bool state) { mIsPrintTimeStamp = state; }

    /*! \see \link ExportContext::setObjFile \endlink */
    const Path & objFile() const { return mObjFile; }

    /*! \see \link ExportContext::setDatarefsFile \endlink */
    const Path & datarefsFile() const { return mDatarefsFile; }

    /*! \see \link ExportContext::setCommandsFile \endlink */
    const Path & commandsFile() const { return mCommandsFile; }

    bool isPrintTimeStamp() const { return mIsPrintTimeStamp; }

    /// @}
    //-------------------------------------------------------------------------

private:

    Path mObjFile;
    Path mDatarefsFile;
    Path mCommandsFile;
    std::string mSignature;
    IOStatistic mStatistic;
    std::unique_ptr<IInterrupter> mInterruptor;
    bool mIsPrintTimeStamp = true;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
