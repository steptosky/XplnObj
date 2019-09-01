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

#include <fstream>
#include <map>
#include "xpln/common/Path.h"
#include "AbstractWriter.h"
#include "xpln/utils/DatarefsFile.h"
#include "xpln/utils/CommandsFile.h"
#include "xpln/obj/ExportContext.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class Writer final : public AbstractWriter {
public:

    //-------------------------------------------------------------------------

    Writer() = default;

    Writer(const Writer &) = delete;
    Writer & operator =(const Writer &) = delete;

    virtual ~Writer();

    //-------------------------------------------------------------------------

    bool openFile(const Path & filePath);
    void closeFile();

    bool loadDatarefs(const Path & filePath);
    bool loadCommands(const Path & filePath);

    //-------------------------------------------------------------------------

    /*! \copydoc AbstractWriter::printEol */
    void writeLine(const char * msg) override;

    //-------------------------------------------------------------------------

    /*! \copydoc AbstractWriter::actualDataref */
    String actualDataref(const String & dataref) override;

    /*! \copydoc AbstractWriter::actualCommand */
    String actualCommand(const String & command) override;

    //-------------------------------------------------------------------------

private:

    std::map<std::uint64_t, Dataref> mDatarefs;
    std::map<std::uint64_t, Command> mCommands;
    std::ofstream mStream;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
