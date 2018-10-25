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
#include <stdexcept>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class AbstractWriter {
public:

    //-------------------------------------------------------------------------
    /// @{

    AbstractWriter(const AbstractWriter &) = delete;
    AbstractWriter & operator =(const AbstractWriter &) = delete;

    AbstractWriter() = default;
    virtual ~AbstractWriter() = default;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \details Print line with EOL.
     * \param [in] msg nullptr means only EOL will be printed
     */
    virtual void printLine(const char * msg) = 0;

    /*!
     * \details Print line with EOL.
     * \param [in] msg if it is empty then only EOL will be printed
     */
    void printLine(const std::string & msg);

    /*!
     * \details Print only EOL.
     */
    void printEol();

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \todo better description - needs link to this functional description 
     * \details Dataref can be just an id and must be resolved to actual one.
     *          So you have to use this method for printing any datarefs into obj.
     * \param [in] dataref current dataref value.
     * \return actual dataref value.
     * \exception std::domain_error is thrown if dataref must be resolved but there is no data to do it.
     *                              For example file with data for resolving isn't specified or isn't loaded.
     */
    virtual std::string actualDataref(const std::string & dataref) = 0;

    /*!
     * \todo better description - needs link to this functional description 
     * \details Command can be just an id and must be resolved to actual one.
     *          So you have to use this method for printing any command into obj.
     * \param [in] command current command value.
     * \return actual command value.
     * \exception std::domain_error is thrown if command must be resolved but there is no data to do it.
     *                              For example file with data for resolving isn't specified or isn't loaded.
     */
    virtual std::string actualCommand(const std::string & command) = 0;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void spaceEnable(bool state);
    void spaceMore();
    void spaceLess();

    /// @}
    //-------------------------------------------------------------------------

protected:

    /*!
     * \details Gets actual space for the line.
     * \return Space symbols if it is enabled otherwise empty string.
     */
    const std::string & space() const;

private:

    bool isSpaceEnabled() const;

    bool mIsSpaceEnabled = true;
    std::string mResult;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline void AbstractWriter::spaceEnable(const bool state) {
    mIsSpaceEnabled = state;
}

inline bool AbstractWriter::isSpaceEnabled() const {
    return mIsSpaceEnabled;
}

//-------------------------------------------------------------------------

inline void AbstractWriter::spaceMore() {
    mResult.append("\t");
}

inline void AbstractWriter::spaceLess() {
    if (!mResult.empty()) {
        mResult.pop_back();
    }
}

inline const std::string & AbstractWriter::space() const {
    static std::string emptyResult;
    return isSpaceEnabled() ? mResult : emptyResult;
}

//-------------------------------------------------------------------------

inline void AbstractWriter::printLine(const std::string & msg) {
    msg.empty() ? printEol() : printLine(msg.c_str());
}

inline void AbstractWriter::printEol() {
    printLine("");
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
