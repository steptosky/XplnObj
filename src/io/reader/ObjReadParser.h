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
#include <cmath>
#include <cassert>
#include <stack>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Class text parser.
 * \details Use constructor with file path or readFile() first, this methods reads specified file to the memory
 *          then you can use the methods for parsing. When you complete parsing use close() method,
 *          it frees memory and after this method you can not use parsing methods.
 *          The method close() is calling by the destructor too.
 *          Use isEnd() for check you have read all data.
 * \warning The parsing methods does not have a check for the class validation.
 *          It means if a file was not read or the memory was free by the close() method
 *          then you can not use parsing methods!
 */
class ObjReadParser {
public:

    //-------------------------------------------------------------------------

    explicit ObjReadParser(const std::string & filePath = "");

    ObjReadParser(const ObjReadParser &) = delete;
    ObjReadParser & operator =(const ObjReadParser &) = delete;

    virtual ~ObjReadParser();

    //-------------------------------------------------------------------------
    // Class initialization

    bool readFile(const std::string & filePath);
    bool isValid() const;
    void close();

    //-------------------------------------------------------------------------
    // Parsing methods

    void nextLine();
    std::string extractLine();
    std::string extractLineTilEol();
    std::string extractWord();
    int extractInt();
    float extractFloat();
    bool isMatch(const char * inString, bool skipMatched = true);
    bool isEnd() const;
    void skipWord();
    void skipSpace();
    void skipUntillParam();

    //-------------------------------------------------------------------------

    void pushPosition() const;
    void popPosition(bool apply);

    //-------------------------------------------------------------------------

private:

    void skipEol();
    bool static isEol(const uint8_t * byte);
    bool static isSpace(const uint8_t * byte);
    bool isComment() const;

    static unsigned fileSize(FILE * file);

    mutable std::stack<uint8_t*> mStack;

    uint8_t * mMemCurr;
    uint8_t * mMemStart;
    uint8_t * mMemEnd;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*! \details Identify current position at the end */
inline bool ObjReadParser::isEnd() const {
    return !(mMemCurr < mMemEnd);
}

/*! \details Identify char that indicate start a comment */
inline bool ObjReadParser::isComment() const {
    return (*mMemCurr == '#');
}

/*! \details Identify chars that indicate a new line */
inline bool ObjReadParser::isEol(const uint8_t * byte) {
    return (*byte == 0 || *byte == 13 || *byte == '\n');
}

/*! \details Identify chars that separate with whitespace */
inline bool ObjReadParser::isSpace(const uint8_t * byte) {
    return (*byte == '\t' || *byte == ' ');
}

/*! \details Consume all newlines. */
inline void ObjReadParser::skipEol() {
    assert(isValid());
    while (!isEnd() && isEol(mMemCurr))
        ++mMemCurr;
}

/*! \details Consume all white space. */
inline void ObjReadParser::skipSpace() {
    assert(isValid());
    while (!isEnd() && isSpace(mMemCurr))
        ++mMemCurr;
}

/*! 
 * \details Consume all white space, EOL and comments. 
 * \todo skipping the comments is not implemented 
 */
inline void ObjReadParser::skipUntillParam() {
    assert(isValid());
    while (!isEnd() && (isSpace(mMemCurr) || isEol(mMemCurr)))
        ++mMemCurr;
}

//-------------------------------------------------------------------------

/*! \details Build a string from the current char to the end of the line (including trailing whitespace) and skip eol. */
inline std::string ObjReadParser::extractLine() {
    std::string out = extractLineTilEol();
    skipEol();
    return out;
}

/*! \details Build a string from the current char to the end of the line (including trailing whitespace). */
inline std::string ObjReadParser::extractLineTilEol() {
    assert(isValid());
    uint8_t * start = mMemCurr;
    while (!isEnd() && !isEol(mMemCurr))
        ++mMemCurr;
    uint8_t * end = mMemCurr;
    return std::string(start, end);
}

/*! \details Build a string of the first non-whitespace word. */
inline std::string ObjReadParser::extractWord() {
    assert(isValid());
    uint8_t * start = mMemCurr;
    while (!isEnd() && !isSpace(mMemCurr) && !isEol(mMemCurr))
        ++mMemCurr;
    uint8_t * end = mMemCurr;
    return std::string(start, end);
}

/*! \details Skips current line */
inline void ObjReadParser::nextLine() {
    assert(isValid());
    while (!isEnd() && !isEol(mMemCurr))
        ++mMemCurr;
    skipEol();
}

/*! \details Skips current word */
inline void ObjReadParser::skipWord() {
    assert(isValid());
    while (!isEnd() && !isEol(mMemCurr) && !isSpace(mMemCurr))
        ++mMemCurr;
}

/*! \details Extracts int */
inline int ObjReadParser::extractInt() {
    assert(isValid());
    int retVal = 0;
    int signMult = 1;

    if (!isEnd() && *mMemCurr == '-') {
        signMult = -1;
        ++mMemCurr;
    }
    if (!isEnd() && *mMemCurr == '+') {
        signMult = 1;
        ++mMemCurr;
    }

    while (!isEnd() && !isSpace(mMemCurr) && !isEol(mMemCurr)) {
        retVal = (10 * retVal) + *mMemCurr - '0';
        ++mMemCurr;
    }
    return signMult * retVal;
}

/*! \details Extracts float */
inline float ObjReadParser::extractFloat() {
    assert(isValid());
    float retVal = 0;
    float signMult = 1.0f;
    int decimals = 0;
    int hasDecimal = false;

    while (!isEnd() && !isSpace(mMemCurr) && !isEol(mMemCurr)) {
        if (*mMemCurr == '-')
            signMult = -1.0f;
        else if (*mMemCurr == '+')
            signMult = 1.0f;
        else if (*mMemCurr == '.')
            hasDecimal = true;
        else {
            retVal = (10 * retVal) + *mMemCurr - '0';
            if (hasDecimal)
                ++decimals;
        }
        ++mMemCurr;
    }
    return float(retVal / pow(10.0f, static_cast<float>(decimals)) * signMult);
}

//-------------------------------------------------------------------------

/*!
 * \details Check for match.
 * \remark If specified string is not match then current position will be back otherwise the current position will be after.
 * \param [in] inString string that will be checked for matching.
 * \param [in] skipMatched
 * \return True if contains specified string otherwise false.
 */
inline bool ObjReadParser::isMatch(const char * inString, const bool skipMatched) {
    assert(isValid());
    skipSpace();
    if (!inString)
        return false;
    uint8_t * storePosition = mMemCurr;
    while (!isEnd() && *mMemCurr == *inString && *inString != '\0') {
        ++mMemCurr;
        ++inString;
    }
    if (*inString == '\0' && (isSpace(mMemCurr) || isEol(mMemCurr))) {
        if (!skipMatched)
            mMemCurr = storePosition;
        return true;
    }
    mMemCurr = storePosition;
    return false;
}

//-------------------------------------------------------------------------

inline bool ObjReadParser::isValid() const {
    return mMemStart != nullptr;
}

//-------------------------------------------------------------------------

inline void ObjReadParser::pushPosition() const {
    mStack.emplace(mMemCurr);
}

inline void ObjReadParser::popPosition(const bool apply) {
    if (!mStack.empty()) {
        if (apply) {
            mMemCurr = mStack.top();
        }
        mStack.pop();
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
