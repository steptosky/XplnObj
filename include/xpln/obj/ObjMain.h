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

#include <vector>
#include <memory>
#include "ObjLodGroup.h"
#include "ExportOptions.h"
#include "IOStatistic.h"
#include "attributes/AttrGlobSet.h"

namespace xobj {

class ObjLodGroup;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the Root object
 * \ingroup Objects
 */
class ObjMain {
public:

    //-------------------------------------------------------------------------

    typedef std::vector<std::unique_ptr<ObjLodGroup>> Lods;

    //-------------------------------------------------------------------------

    ObjMain() = default;

    ObjMain(const ObjMain &) = delete;
    ObjMain & operator =(const ObjMain &) = delete;

    virtual ~ObjMain() = default;

    //-------------------------------------------------------------------------

    /*!
     * \details Set of the attributes.
     */
    AttrGlobSet pAttr;

    /*!
     * \details Export options.
     */
    ExportOptions pExportOptions;

    /*!
     * \details Transform matrix for applying while exporting/importing.
     * \details With this matrix you can move, rotate, convert to another system coordinates all the objects.
     */
    TMatrix pMatrix;

    //-------------------------------------------------------------------------

    /*!
     * \details Adds new lods to the list.
     * \details It takes ownership of the Lod's pointer.
     * \param [in] lod if nullptr then new lod will be auto-created.
     * \return Reference to just added/created lod.
     */
    XpObjLib ObjLodGroup & addLod(ObjLodGroup * lod = nullptr);

    /*!
     * \return Lods list.
     */
    Lods & lods() {
        return mLods;
    }

    /*!
     * \return Lods list.
     */
    const Lods & lods() const {
        return mLods;
    }

    //-------------------------------------------------------------------------

    void setObjectName(const std::string & name) {
        mName = name;
    }

    const std::string & objectName() const {
        return mName;
    }

    //-------------------------------------------------------------------------

    /*!
     * \details Starts export to 'obj' file.
     * \param [in] path full path with filename and extension.
     * \return True if successful otherwise false.
     */
    XpObjLib bool exportToFile(const std::string & path);

    /*!
     * \details Starts export to 'obj' file.
     * \param [in] path full path with filename and extension
     * \param [out] outStat export statistic.
     * \return True if successful otherwise false.
     */
    XpObjLib bool exportToFile(const std::string & path, IOStatistic & outStat);

    /*!
     * \details Starts import from 'obj' file.
     * \param [in] path full path with filename and extension.
     * \return True if successful otherwise false.
     */
    XpObjLib bool importFromFile(const std::string & path);

    /*!
     * \details Start import from 'obj' file
     * \param [in] path full path with filename and extension
     * \param [out] outStat import statistic.
     * \return True if successful otherwise false.
     */
    XpObjLib bool importFromFile(const std::string & path, IOStatistic & outStat);

    //-------------------------------------------------------------------------

private:

    std::string mName;
    std::vector<std::unique_ptr<ObjLodGroup>> mLods;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
