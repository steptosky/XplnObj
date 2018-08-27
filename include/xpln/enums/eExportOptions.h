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

#include <cstdint>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Export options
 * \ingroup Enumerations
 */
enum eExportOptions : uint64_t {

    /*! \details No options */
    XOBJ_EXP_NO_OPT = 0,

    /*! \details Mark meshes (TRIS) by objectName in the 'obj' file */
    XOBJ_EXP_MARK_MESH = 1 << 0,

    /*! \details Mark lines (LINE) by objectName in the 'obj' file */
    XOBJ_EXP_MARK_LINE = 1 << 1,

    /*! \details Mark dummies by objectName in the 'obj' file */
    XOBJ_EXP_MARK_DUMMY = 1 << 2,

    /*! \details Mark lights by objectName in the 'obj' file */
    XOBJ_EXP_MARK_LIGHT = 1 << 3,

    /*! \details The tree branch indent in the 'obj' file */
    XOBJ_EXP_MARK_TREE_HIERARCHY = 1 << 4,

    /*! \details Mark transforms by objectName in the 'obj' file */
    XOBJ_EXP_MARK_TRANSFORM = 1 << 5,

    /*! \details Mark vertex group by objectName in the 'obj' file */
    XOBJ_EXP_MARK_VERTEX = 1 << 6,

    /*! \details Mark smokes by objectName in the 'obj' file */
    XOBJ_EXP_MARK_SMOKE = 1 << 7,

    /*!
     * \details Applying the LOD transform matrix to the hierarchy.
     * \details Use it if you want the LOD's transform matrix to affect all its children,
     * for example it can be used for align object relative the lods.
     */
    XOBJ_EXP_APPLY_LOD_TM = 1 << 21,

    /*!
     * \details Optimizing the object and hierarchy.
     * \note If you need to debug your obj file probably you have to temporarily turn this option off.
     */
    XOBJ_EXP_OPTIMIZATION = 1 << 22,

    /*!
     * \details Checking scenery objects for make it as instance.
     * Since X-Plane 10, it has "instancing" and some conditions for make it possible for an object.
     * If this option is enabled then library will check the objects for that conditions.
     */
    XOBJ_EXP_CHECK_INSTANCE = 1 << 23,

    /*!
     * \details Print addition information to file. It is not the same as Obj's DEBUG attribute.
     */
    XOBJ_EXP_DEBUG = 1 << 24,

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
