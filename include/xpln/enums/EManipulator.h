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
#include "xpln/XplnObjExport.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the X-Plane manipulators' types
 * \ingroup Enumerations
 */
class EManipulator {
public:

    /*!
     * \note It is NOT guaranteed that the existing indexes will be constant when new data is added.
     *       So you can consider it when you design your serialization solution. 
     *       You can use obj string \link EManipulator::toString \endlink.
     */
    enum eId : int32_t {
        none = 0,
        axis_knob,
        axis_switch_lr,
        axis_switch_ud,
        command,
        command_axis,
        command_knob,
        command_switch_lr,
        command_switch_ud,
        delta,
        drag_axis,
        drag_axis_pix,
        drag_xy,
        noop,
        panel,
        push,
        radio,
        toggle,
        wrap,
    };

    //-------------------------------------------------------------------------

    typedef std::vector<EManipulator> List;

    //-------------------------------------------------------------------------

    /*!
     * \details Constructor default.
     */
    XpObjLib EManipulator();

    /*!
     * \details Constructor init from manipulator's Id.
     * \param [in] id
     */
    XpObjLib explicit EManipulator(eId id);

    XpObjLib ~EManipulator() = default;

    //-------------------------------------------------------------------------

    XpObjLib bool operator ==(const EManipulator & other) const;
    XpObjLib bool operator ==(eId id) const;

    XpObjLib bool operator !=(const EManipulator & other) const;
    XpObjLib bool operator !=(eId id) const;

    //-------------------------------------------------------------------------

    /*!
     * \details Makes from string which is used in the ui.
     * \param [in] name
     */
    XpObjLib static EManipulator fromUiString(const char * name);

    /*!
     * \details Makes from string which is used in the obj files.
     * \param [in] attrName
     */
    XpObjLib static EManipulator fromString(const char * attrName);

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
     * \details Gets list of all manipulators' id.
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
