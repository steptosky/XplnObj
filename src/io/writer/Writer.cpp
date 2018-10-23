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

#include "Writer.h"
#include "common/Logger.h"
#include "exceptions/defines.h"
#include "sts/string/StringUtils.h"

using namespace std::string_literals;

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

Writer::~Writer() {
    closeFile();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool Writer::openFile(const Path & filePath) {
    mStream.open(filePath, std::ios_base::out);
    if (!mStream) {
        // todo sts::toMbString may work incorrectly with unicode.
        ULError << " - File <" << sts::toMbString(filePath) << "> couldn't be created or written!";
        return false;
    }
    mStream.precision(6);
    mStream << std::fixed;
    return true;
}

void Writer::closeFile() {
    if (mStream) {
        mStream.close();
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

void Writer::printLine(const char * msg) {
    if (msg) {
        mStream << space().c_str() << msg << std::endl;
    }
    else {
        mStream << std::endl;
    }
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool Writer::loadDatarefs(const Path & filePath) {
    std::ifstream file(filePath, std::ios_base::in);
    if (!file) {
        // todo sts::toMbString may work incorrectly with unicode.
        ULError << " - File <" << sts::toMbString(filePath) << "> couldn't be read!";
        return false;
    }

    const auto callback = [&](const Dataref & drf) ->bool {
        if (drf.mId != Dataref::invalidId()) {
            const auto iter = mDatarefs.find(drf.mId);
            if (iter != mDatarefs.end()) {
                // todo sts::toMbString may work incorrectly with unicode.
                ULError << "File <" << sts::toMbString(filePath) << "> contains data with duplicated id: " << drf.mId;
            }
            else {
                mDatarefs.emplace(drf.mId, drf);
            }
        }
        return true;
    };

    return DatarefsFile::loadStream(file, callback);
}

bool Writer::loadCommands(const Path & filePath) {
    std::ifstream file(filePath, std::ios_base::in);
    if (!file) {
        // todo sts::toMbString may work incorrectly with unicode.
        ULError << " - File <" << sts::toMbString(filePath) << "> couldn't be read!";
        return false;
    }

    const auto callback = [&](const Command & cmd) ->bool {
        if (cmd.mId != Dataref::invalidId()) {
            const auto iter = mCommands.find(cmd.mId);
            if (iter != mCommands.end()) {
                // todo sts::toMbString may work incorrectly with unicode.
                ULError << "File <" << sts::toMbString(filePath) << "> contains data with duplicated id: " << cmd.mId;
            }
            else {
                mCommands.emplace(cmd.mId, cmd);
            }
        }
        return true;
    };

    return CommandsFile::loadStream(file, callback);
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

std::string Writer::actualDataref(const std::string & dataref) {
    if (!Dataref::isKeyId(dataref)) {
        return dataref;
    }
    if (dataref.empty()) {
        throw std::domain_error(ExcTxt("Dataref <"s.append(dataref)
                                    .append("> is considered as an id but datarefs file for extracting")
                                    .append(" the correct values isn't specified or loaded.")));
    }
    const auto iter = mDatarefs.find(Dataref::keyToId(dataref));
    if (iter == mDatarefs.end()) {
        throw std::domain_error(ExcTxt("Dataref <"s.append(dataref)
                                    .append("> is considered as an id but datarefs file for extracting")
                                    .append(" the correct values doesn't contain necessary value.")));
    }
    return iter->second.mKey;
}

std::string Writer::actualCommand(const std::string & command) {
    if (!Command::isKeyId(command)) {
        return command;
    }
    if (command.empty()) {
        throw std::domain_error(ExcTxt("Command <"s.append(command)
                                    .append("> is considered as an id but commands file for extracting")
                                    .append(" the correct values isn't specified or loaded.")));
    }
    const auto iter = mCommands.find(Command::keyToId(command));
    if (iter == mCommands.end()) {
        throw std::domain_error(ExcTxt("Command <"s.append(command)
                                    .append("> is considered as an id but commands file for extracting")
                                    .append(" the correct values doesn't contain necessary value.")));
    }
    return iter->second.mKey;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
