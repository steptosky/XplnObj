#pragma once

/*
**  Copyright(C) 2019, StepToSky
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
#include <optional>
#include "xpln/common/Quat.h"
#include "xpln/obj/animation/AnimRotate.h"

namespace xobj {

class TMatrix;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Converter quaternions sequence to animation rotate.
 * \note Big sequence that produces many different vectors may lead 
 *       to performance issue because it will produce many animation. 
 *       
 *       Example (as angle axis):
 *       
 *              [vec(0,1,0) angle(0),vec(0,1,0) angle(30),vec(0,1,0) angle(90)]
 *                  Will produce just one animation with 3 keys because vector the same
 *                  for all the keys, but:
 *              
 *              [vec(1,0,0) angle(0),vec(0,1,0) angle(30),vec(0,0,1) angle(90)]
 *                  Will produce 3 animations with various keys.
 *                  Sometimes it can be imposable to avoid this situation according to some specific animations,
 *                  and other animation types like Euler will not help much,
 *                  in other cases you should consider to ask user to use other animation types like Euler.
 *                  It doesn't make a sense to ask the user if the produced animations number less than 3-5.
 */
class LinearRotateHelper final {
public:

    LinearRotateHelper() = delete;

    struct Key {
        Quat mQuat;
        float mDrfValue = 0.0f;
    };

    typedef std::vector<Key> Input;

    /*!
     * \details Checks whether the dataref values are in correct order.
     * \details Use it before call \link LinearRotateHelper::makeAnimations \endlink
     * \param [in] input dataref values.
     * \return position where value is incorrect or std::nullopt
     */
    XpObjLib static std::optional<std::size_t> checkDatarefValuesOrder(const Input & input);

    /*!
     * \pre The algorithm doesn't work if sequence contains less then 2 keys,
     *      and will return empty animation. 
     *      
     *      You also have to check dataref values with the \link LinearRotateHelper::checkDatarefValuesOrder \endlink
     *      if they are in correct order.
     *      
     * \param [in] input quaternion sequence.
     * \param [in] matrix for applying to final vector of \link AnimRotate \endlink.
     */
    XpObjLib static AnimRotateList makeAnimations(const Input & input, const TMatrix & matrix);

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
