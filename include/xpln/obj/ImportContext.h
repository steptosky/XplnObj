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
#include "xpln/common/IInterrupter.h"
#include "IOStatistic.h"

// todo remove duplicate in ExportContext
// it can be done if common things for contexts will be in the same abstract class.
#ifndef XOBJ_PATH
#   ifdef _MSC_VER
#       define XOBJ_PATH(X) L##X;
#   else
#       define XOBJ_PATH(X) X;
#   endif
#endif

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ImportContext {
public:

    //-------------------------------------------------------------------------
    /// @{

#ifdef _MSC_VER
    /*!
     * \pre Windows uses UTF16 and wide string, Unix uses UTF8 and char.
     * \note I decided to not use boost file system now
     *       because it will increase build time on CI.
     */
    typedef std::wstring Path;
#else
    /*!
     * \pre Windows uses UTF16 and wide string, Unix uses UTF8 and char.
     * \note I decided to not use boost file system now
     *       because it will increase build time on CI.
     */
        typedef std::string Path;
#endif

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    ImportContext() = default;

    /*! \see \link ImportContext::setObjFile \endlink */
    explicit ImportContext(const Path & fullFilePath) { setObjFile(fullFilePath); }

    ImportContext(const ImportContext &) = delete;
    ImportContext(ImportContext &&) = delete;

    virtual ~ImportContext() = default;

    ImportContext & operator=(const ImportContext &) = delete;
    ImportContext & operator=(ImportContext &&) = delete;

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

    /// @}
    //-------------------------------------------------------------------------
    /// \name Files
    /// @{

    /*!
     * \details File path for obj reading.
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

    /*! \see \link ImportContext::setObjFile \endlink */
    const Path & objFile() const { return mObjFile; }

    /*! \see \link ImportContext::setDatarefsFile \endlink */
    const Path & datarefsFile() const { return mDatarefsFile; }

    /*! \see \link ImportContext::setCommandsFile \endlink */
    const Path & commandsFile() const { return mCommandsFile; }

    /// @}
    //-------------------------------------------------------------------------

private:

    Path mObjFile;
    Path mDatarefsFile;
    Path mCommandsFile;
    IOStatistic mStatistic;
    std::unique_ptr<IInterrupter> mInterruptor;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
