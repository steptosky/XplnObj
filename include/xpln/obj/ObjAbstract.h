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
#include "xpln/Export.h"
#include "xpln/enums/eObjectType.h"
#include "xpln/common/String.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class TMatrix;
class AttrSet;
class AbstractWriter;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Base class for all 'obj' objects
 * \ingroup Objects
 */
class ObjAbstract {
protected:

    //-----------------------------------------------------

    XpObjLib ObjAbstract();

    /*!
     * \details Constructor copy.
     * \note It does not copy the transform linkage.
     */
    XpObjLib ObjAbstract(const ObjAbstract & copy);

    //-----------------------------------------------------

public:

    //-----------------------------------------------------

    ObjAbstract & operator =(const ObjAbstract &) = delete;

    virtual ~ObjAbstract() = default;

    //--------------------------------------------------------

    XpObjLib virtual eObjectType objType() const;

    //--------------------------------------------------------

    XpObjLib void setObjectName(const String & name);
    XpObjLib const String & objectName() const;

    //--------------------------------------------------------

    /*!
     * \details Applies specified transformation matrix to the object.
     * \param [in] tm transform matrix.
     * \param [in] useParity \see \link TMatrix::parity \endlink
     */
    virtual void applyTransform(const TMatrix & tm, bool useParity = false) = 0;

    /*!
     * \return Cloned object.
     */
    virtual ObjAbstract * clone() const = 0;

    //--------------------------------------------------------v

    /*!
     * \details This adds text line that will be printed into .obj file before this object is processed.
     *          This data is printed after animation, manipulators and attributes.
     * \details This allows you to use new attributes manually until it is supported by the library.
     * \param [in] string 
     */
    void addDataBefore(const String & string) { mDataBefore.emplace_back(string); }

    /*!
     * \details This adds text line that will be printed into .obj file after this object is processed.
     * \details This allows you to use new attributes manually until it is supported by the library.
     * \param [in] string
     */
    void addDataAfter(const String & string) { mDataAfter.emplace_back(string); }

    const std::vector<String> & dataBefore() const { return mDataBefore; }
    const std::vector<String> & dataAfter() const { return mDataAfter; }

    //--------------------------------------------------------

private:

    String mName;
    std::vector<String> mDataBefore;
    std::vector<String> mDataAfter;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
