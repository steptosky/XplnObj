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
#include "xpln/obj/ObjMain.h"
#include "common/Result.h"
#include "xpln/common/IInterrupt.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class LodsAlg {
    LodsAlg() = default;
    ~LodsAlg() = default;
public:

    //-------------------------------------------------------------------------
    /// \name Validator
    /// @{

    /*!
     * \details Validates and prepares LOD objects.
     * \note It runs \link LodsAlg::mergeIdenticalLods \endlink and 
     *               \link LodsAlg::sort \endlink 
     *               
     * \param [in, out] inOutLods 
     * \param [in] objectName 
     * \return False if something is wrong with LODs otherwise true.
     *          Information about problems is printed to the log.
     */
    XpObjLib static bool validateAndPrepare(ObjMain::Lods & inOutLods, const std::string & objectName);

    /// @}
    //-------------------------------------------------------------------------
    /// \name For testing only
    /// @{

    /*!
     * \todo not implemented
     * \details It merges objects of identical LODs into one LOD.
     * \note It is not private because of testing.
     * \param [in, out] inOutLods
     * \param [in] interrupt
     */
    XpObjLib static void mergeIdenticalLods(ObjMain::Lods & inOutLods, const IInterrupt & interrupt);

    /*!
     * \details Sorts the LOD according to obj specification.
     * \note It is not private because of testing.
     * \param [in, out] inOutLods 
     * \param [in] interrupt 
     * \return false if there is an error with LODs' values 
     *          and they can't be sorted correctly or 
     *          the algorithm was interrupted
     *          otherwise true.
     */
    XpObjLib static Result sort(ObjMain::Lods & inOutLods, const IInterrupt & interrupt);

    /// @}
    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
