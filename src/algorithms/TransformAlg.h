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

#include <functional>
#include "xpln/Export.h"
#include "xpln/obj/Transform.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class TransformAlg {
    TransformAlg() = default;
    ~TransformAlg() = default;
public:

    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \details Applies animation translation containing only 1 key 
     *          to transform position and removes that animation.
     * \param [in, out] inOutTrans
     * \param [in, out] inOutAnim
     */
    XpObjLib static void applyTranslateKeysToTransform(Transform & inOutTrans, AnimTransList & inOutAnim);

    /*!
     * \details Applies animation rotation containing only 1 key
     *          to transform rotation and removes that animation.
     * \param [in, out] inOutTrans
     * \param [in, out] inOutAnim
     */
    XpObjLib static void applyRotateKeysToTransform(Transform & inOutTrans, AnimRotateList & inOutAnim);

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \details Applies specified matrix to each keys of each animation.
     * \param [in, out] inOutAnim
     * \param [in] tm
     */
    XpObjLib static void applyMatrixToAnimTranslate(AnimTransList & inOutAnim, const TMatrix & tm);

    /*!
     * \details Applies specified matrix to vector of each animation.
     * \param [in, out] inOutAnim
     * \param [in] tm
     */
    XpObjLib static void applyMatrixToAnimRotate(AnimRotateList & inOutAnim, const TMatrix & tm);

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \details It iterates up by hierarchy starting from the specified transform's parent 
     *          and return first found transform with translate animation 
     *          or nullptr if no one is found.
     * \param [in] transform
     */
    XpObjLib static const Transform * animatedTranslateParent(const Transform & transform);

    /*!
     * \details It iterates up by hierarchy starting from the specified transform's parent 
     *          and return first found transform with rotate animation
     *          or nullptr if no one is found.
     * \param [in] transform
     */
    XpObjLib static const Transform * animatedRotateParent(const Transform & transform);

    /*!
     * \details It iterates up by hierarchy starting from the specified transform's parent
     *          and return first found transform the predicate returns true for.
     * \param [in] transform
     * \param [in] p predicate
     */
    XpObjLib static const Transform * findParentIf(const Transform & transform,
                                                   const std::function<bool(const Transform &)> & p);

    /// @}
    //-------------------------------------------------------------------------

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
