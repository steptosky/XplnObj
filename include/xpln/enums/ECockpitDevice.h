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
#include <cstdint>
#include "xpln/Export.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the X-Plane cockpit devices
 * \ingroup Enumerations
 */
class ECockpitDevice {
public:

    /*!
     * \note It is NOT guaranteed that the existing indexes will be constant when new data is added.
     *       So you can consider it when you design your serialization solution. You can use obj string (toString()).
     */
    enum eId : std::int32_t {
        none = 0,
        GNS430_1,
        GNS430_2,
        GNS530_1,
        GNS530_2,
        CDU739_1,
        CDU739_2,
        G1000_PFD1,
        G1000_MFD,
        G1000_PFD2,
    };

    //-------------------------------------------------------------------------

    typedef std::vector<ECockpitDevice> List;

    //-------------------------------------------------------------------------

    /*!
     * \details Constructor default.
     */
    XpObjLib explicit ECockpitDevice();

    /*!
    * \details Constructor init from Id.
     * \param [in] id
     */
    XpObjLib explicit ECockpitDevice(eId id);

    XpObjLib ~ECockpitDevice() = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator ==(const ECockpitDevice & other) const;
    XpObjLib bool operator ==(eId id) const;

    XpObjLib bool operator !=(const ECockpitDevice & other) const;
    XpObjLib bool operator !=(eId id) const;

    //-------------------------------------------------------------------------

    /*!
     * \details Makes from string which is used in the UI.
     * \param [in] name
     */
    XpObjLib static ECockpitDevice fromUiString(const char * name);

    /*!
     * \details Makes from string which is used in the obj files.
     * \param [in] attrName
     */
    XpObjLib static ECockpitDevice fromString(const char * attrName);

    //-------------------------------------------------------------------------

    /*!
     * \details Checks whether this instance is valid.
     * \return True if valid otherwise false.
     */
    XpObjLib bool isValid() const;

    /*!
     * \details Gets id.
     */
    XpObjLib eId id() const;

    /*!
     * \details Gets string which is used in obj files.
     */
    XpObjLib const char * toString() const;

    /*!
     * \details Gets string which can be used for UI.
     */
    XpObjLib const char * toUiString() const;

    /*!
     * \details Gets list of all id.
     */
    XpObjLib static const List & list();

    //-------------------------------------------------------------------------

private:

    eId mId;
    static void makeList(List &);
    static List mList;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
