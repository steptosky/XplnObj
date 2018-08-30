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

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>

namespace sts {

#define STS_FUNC_INFO              __FUNCTION__
#define STS_LINE_NUMBER            __LINE__
#define STS_FILE_NAME              __FILE__

#define STS_LOGGER_INFO STS_FUNC_INFO, STS_LINE_NUMBER, STS_FILE_NAME

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
    Logger
    */

class Logger {
public:

    /*! \details Index of stream in stream list */
    typedef size_t streamIndex;

    /*! \details Levels of log messages and for output print level */
    enum eMsgLevel {
        lvlDebug = 0,
        lvlWarning,
        lvlError,
        lvlCrterror,
        lvlMsg
    };

    //-------------------------------------------------------------------------

    Logger();
    virtual ~Logger();

    /*!
    \details Fully reset logger with clearing stream list by clearStreamList(). (like creating a new instance of logger.)
    */
    virtual void clear();

    //-------------------------------------------------------------------------

    /*!
    \details Gets current formating time
    \warning You don't need to delete returned data.
    \param [in] format - format for returned time like format for strftime();
    \return current time in your format;
    */
    const char * currentTime(const char * format = "%H:%M:%S");

    // Time flags

    /*! \details Sets Print timestamp to log messages */
    void setPrintTime(bool isPrint) {
        mPrintTimef = isPrint;
    }

    /*! \details Check is print timestamp to log */
    bool isPrintTime() const {
        return mPrintTimef;
    }

    //-------------------------------------------------------------------------

    // Level of messages operation

    /*!
    \details Sets logger output level
    \details Logger will print messages with a level, which is equaled or greater than the output level
    */
    void setOutLevel(const eMsgLevel & level) {
        mOutLevel = level;
    }

    /*!
    \details Gets logger output level
    \details For more info read about setOutLevel.
    \return Current logger output level
    */
    const eMsgLevel & outLevel(void) const {
        return mOutLevel;
    }

    //-------------------------------------------------------------------------

    /*! \details Sets level of the next messages */
    void setLevelOfNextMessage(const eMsgLevel & level) {
        mCurMsgLevel = level;
    }

    /*! \details Gets level of the next messages */
    const eMsgLevel & levelOfNextMessage(void) const {
        return mCurMsgLevel;
    }

    /*! \details Sets default level of messages */
    void setDefaultLevelOfMessages(const eMsgLevel & level) {
        mDefaultLevel = level;
    }

    //-------------------------------------------------------------------------

    // Stream operation

    /*!
    \details Return size
    \return number of elements in the stream list.
    */
    virtual size_t numOfStreams() const {
        return mStreamList.size();
    }

    /*!
    \details Adds a new element at the end of the stream list, after its current last element.
    Pointer t just copied to the list.
    Not allocate/free memory operation.
    \param [in] t - pointer to allocated std::ostream
    \return If success then return true otherwise false;
    */
    virtual bool pushBackStream(std::ostream * t);

    /*!
    \details Removes the last element in the stream list, effectively reducing the container size by one.
    \warning this function have not any allocation/free memory action with elements! Just remove element from self;
    \return std::ostream* - pointer to std::ostream which was removed;
    */
    virtual std::ostream * popBackStream();

    /*!
    \details Access element of stream list
    \details The function automatically checks whether index is within the bounds of valid elements in the stream list, printing to cerr about it.
    \param [in] index - index of element
    \return If successful then returns a pointer to the element at position index in the stream list otherwise nullptr
    */
    virtual const std::ostream * stream(streamIndex index) const;

    /*!
    \details Takes element of stream list
    \warning This function have not any allocation/free memory action with elements! Just remove element from self.
    \details The function automatically checks whether index is within the bounds of valid elements in the stream list, printing to cerr about it.
    \param [in] index - index of element
    \return If successful then returns a pointer to the element at position index in the stream list and delete this element from stream list otherwise nullptr.
    */
    virtual std::ostream * takeStream(streamIndex index);

    /*!
    \details Remove all elements from the stream list. Auto call in the Logger destructor;
    \warning this function has not any allocation/free memory action with elements! Just remove elements from self;
    */
    virtual void clearStreamList();

    //-------------------------------------------------------------------------

    // Log operation

    /*! \details Operator for print some data. */
    template<class T>
    Logger & operator<<(const T & msg) {
        mMsgList << msg;
        return *this;
    }

    /*! \details Operator for print std::string data. */
    Logger & operator<<(const std::string & msg) {
        Logger::operator <<(msg.c_str());
        return *this;
    }

    /*! \details Operator for set message level. */
    Logger & operator<<(const eMsgLevel & inLevel) {
        printNow();
        setLevelOfNextMessage(inLevel);
        return *this;
    }

    /*! \details Operator for manipulators from std lib like std::endl */
    Logger & operator<<(std::ostream & (*pf)(std::ostream &)) {
        mMsgList << pf;
        printNow();
        return *this;
    }

    /*! \details Operator for manipulators from std lib like std::endl */
    Logger & operator<<(std::ios & (*pf)(std::ios &)) {
        mMsgList << pf;
        printNow();
        return *this;
    }

    /*! \details Operator for manipulators from std lib like std::endl */
    Logger & operator<<(std::ios_base & (*pf)(std::ios_base &)) {
        mMsgList << pf;
        printNow();
        return *this;
    }

    //-------------------------------------------------------------------------

    /*!
    \details Print message with format.
    \warning The function will change level of the next messages and all "<<" operators will be used this level too.
    \return *this
    */
    virtual Logger & message(const char * inMethodName = nullptr, int inLineNumber = -1, const char * inFileName = nullptr);

    /*!
    \details Print debug message with format.
    \warning The function will change level of the next messages and all "<<" operators will be used this level too.
    \return *this
    */
    virtual Logger & debug(const char * inMethodName = nullptr, int inLineNumber = -1, const char * inFileName = nullptr);

    /*!
    \details Print critical error message with format.
    \remark The function will increment critical error counter.
    \warning The function will change level of the next messages and all "<<" operators will be used this level too.
    \return *this
    */
    virtual Logger & critical(const char * inMethodName = nullptr, int inLineNumber = -1, const char * inFileName = nullptr);

    /*!
    \details Print error message with format.
    \remark The function will increment error counter.
    \warning The function will change level of the next messages and all "<<" operators will be used this level too.
    \return *this
    */
    virtual Logger & error(const char * inMethodName = nullptr, int inLineNumber = -1, const char * inFileName = nullptr);

    /*!
    \details Print warning message with format.
    \remark The function will increment warning counter.
    \warning The function will change level of the next messages and all "<<" operators will be used this level too.
    \return *this
    */
    virtual Logger & warning(const char * inMethodName = nullptr, int inLineNumber = -1, const char * inFileName = nullptr);

    //-------------------------------------------------------------------------

    /*!
    \details Get Critical messages count.
    \return count
    */
    virtual unsigned int criticalCount() const {
        return mCriticalCount;
    }

    /*!
    \details Reset Critical messages count.
    */
    virtual void resetCriticalCount() {
        mCriticalCount = 0;
    }

    /*!
    \details Get Error messages count.
    \return count
    */
    virtual unsigned int errorCount() const {
        return mErrorCount;
    }

    /*!
    \details Reset Error messages count.
    */
    virtual void resetErrorCount() {
        mErrorCount = 0;
    }

    /*!
    \details Get Warning messages count.
    \return count
    */
    virtual unsigned int warningCount() const {
        return mWarningCount;
    }

    /*!
    \details Reset Warning messages count.
    */
    virtual void resetWarningCount() {
        mWarningCount = 0;
    }

protected:

    // Print operation

    /*!
    \details Print current stack of messages.
    \warning After this functions message's stack will be cleared.
    */
    virtual void printNow();

    /*!
    \details Get current message's stack which will be printed
    \return Copy of current message which will be printed.
    */
    std::string actualMessageStack() const;

private:

    Logger & operator=(const Logger &) = delete;
    Logger(const Logger &) = delete;

    void _printClassAndFileInfo(const char * inMethodName = nullptr, int inLineNumber = -1, const char * inFileName = nullptr);
    void _print();

    // streams
    std::vector<std::ostream *> mStreamList;

    // Levels
    eMsgLevel mCurMsgLevel;
    eMsgLevel mOutLevel;
    eMsgLevel mDefaultLevel;
    std::stringstream mMsgList;
    bool mPrintTimef;

    // TIME
    char mBuffer[80];
    time_t mSeconds;
    tm mTimeinfo;

    // Counters
    unsigned int mWarningCount;  //!< Pre-message warning counter
    unsigned int mErrorCount;    //!< Pre-message error counter
    unsigned int mCriticalCount; //!< Pre-message information counter

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline Logger::Logger() {
    clear();
}

//-------------------------------------------------------------------------

inline Logger::~Logger() {
    printNow();
    clearStreamList();
}

inline void Logger::clear() {
    setDefaultLevelOfMessages(Logger::lvlMsg);
    setLevelOfNextMessage(Logger::lvlMsg);
    setOutLevel(Logger::lvlDebug);

    setPrintTime(true);

    resetCriticalCount();
    resetErrorCount();
    resetWarningCount();

    printNow(); // flush
    clearStreamList();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline bool Logger::pushBackStream(std::ostream * t) {
    if (!t)
        return false;
    mStreamList.push_back(t);
    return true;
}

//-------------------------------------------------------------------------

inline std::ostream * Logger::popBackStream() {
    if (mStreamList.size() == 0) {
        std::cerr << "Logger Exceptions: index out of range; in " << STS_FUNC_INFO << ";" << std::endl;
        return nullptr;
    }
    std::ostream * temp = mStreamList.back();
    mStreamList.pop_back();
    return temp;
}

//-------------------------------------------------------------------------

inline const std::ostream * Logger::stream(streamIndex index) const {
    streamIndex size = mStreamList.size();
    if (index < size && size != 0)
        return mStreamList[index];

    std::cerr << "Logger Exceptions: index out of range; in " << STS_FUNC_INFO << ";" << std::endl;
    return nullptr;
}

//-------------------------------------------------------------------------

inline std::ostream * Logger::takeStream(streamIndex index) {
    streamIndex size = mStreamList.size();
    if (index < size && size != 0) {
        std::ostream * ptr = mStreamList[index];
        mStreamList.erase(mStreamList.begin() + index);
        return ptr;
    }
    std::cerr << "Logger Exceptions: index out of range; in " << STS_FUNC_INFO << ";" << std::endl;
    return nullptr;
}

//-------------------------------------------------------------------------

inline void Logger::clearStreamList() {
    mStreamList.clear();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline Logger & Logger::message(const char * inMethodName, int inLineNumber, const char * inFileName) {
    setLevelOfNextMessage(Logger::eMsgLevel::lvlMsg);
    if (mPrintTimef)
        *this << currentTime("%H:%M:%S ");
    _printClassAndFileInfo(inMethodName, inLineNumber, inFileName);
    return *this;
}

inline Logger & Logger::debug(const char * inMethodName, int inLineNumber, const char * inFileName) {
    setLevelOfNextMessage(Logger::eMsgLevel::lvlDebug);
    if (mPrintTimef)
        *this << currentTime("%H:%M:%S ");
    *this << "DEBUG: ";
    _printClassAndFileInfo(inMethodName, inLineNumber, inFileName);
    return *this;
}

inline Logger & Logger::critical(const char * inMethodName, int inLineNumber, const char * inFileName) {
    setLevelOfNextMessage(Logger::eMsgLevel::lvlCrterror);
    if (mPrintTimef)
        *this << currentTime("%H:%M:%S ");
    *this << "CRITICAL: ";
    _printClassAndFileInfo(inMethodName, inLineNumber, inFileName);
    mCriticalCount++;
    return *this;
}

inline Logger & Logger::error(const char * inMethodName, int inLineNumber, const char * inFileName) {
    setLevelOfNextMessage(Logger::eMsgLevel::lvlError);
    if (mPrintTimef)
        *this << currentTime("%H:%M:%S ");
    *this << "ERROR: ";
    _printClassAndFileInfo(inMethodName, inLineNumber, inFileName);
    mErrorCount++;
    return *this;
}

inline Logger & Logger::warning(const char * inMethodName, int inLineNumber, const char * inFileName) {
    setLevelOfNextMessage(Logger::eMsgLevel::lvlWarning);
    if (mPrintTimef)
        *this << currentTime("%H:%M:%S ");
    *this << "WARNING: ";
    _printClassAndFileInfo(inMethodName, inLineNumber, inFileName);
    mWarningCount++;
    return *this;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline void Logger::printNow() {
    if (mCurMsgLevel >= mOutLevel) {
        if (mMsgList.tellp() > 0) {
            _print();
        }
    }
    mMsgList.str("");
    return;
}

//-------------------------------------------------------------------------

inline std::string Logger::actualMessageStack() const {
    return mMsgList.str();
}

//-------------------------------------------------------------------------

inline const char * Logger::currentTime(const char * format) {
    mSeconds = time(NULL);
#ifdef _MSC_VER
    /*errno_t errnoResult = */
    localtime_s(&mTimeinfo, &mSeconds);
#else
        mTimeinfo = *localtime(&mSeconds);
#endif //_MSC_VER
    //char* format = "%A, %B %d, %Y %I:%M:%S";
    //char* format = "%A, %B %d, %Y %H:%M:%S";
    strftime(mBuffer, 80, format, &mTimeinfo);
    return mBuffer;
}

//-------------------------------------------------------------------------

inline void Logger::_printClassAndFileInfo(const char * inMethodName, int inLineNumber, const char * inFileName) {
    if (inMethodName != nullptr) {
        Logger::operator <<(inMethodName);
        Logger::operator <<("; ");
    }
    if (inLineNumber >= 0) {
        Logger::operator <<("Line: ");
        Logger::operator <<(inLineNumber);
        Logger::operator <<("; ");
    }
    if (inFileName != nullptr) {
        Logger::operator <<("In File: ");
        Logger::operator <<(inFileName);
        Logger::operator <<("; ");
    }
    //sts::Logger::operator << (Logger::endl);
}

//-------------------------------------------------------------------------

inline void Logger::_print() {
    // print to streams
    for (size_t i = 0; i < mStreamList.size(); ++i) {
        if (mStreamList[i]) {
            *mStreamList[i] << mMsgList.str();
        }
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

} // namespace sts
