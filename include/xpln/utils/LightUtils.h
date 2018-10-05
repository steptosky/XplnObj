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
#include <string>
#include <map>
#include <functional>
#include <tuple>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Utils for the lights.
 * \ingroup Utils
 */
class LightUtils {
    LightUtils() = default;
    ~LightUtils() = default;
public:

    //-------------------------------------------------------------------------
    /// @{

    typedef std::function<std::string()> ParamExpander;
    typedef std::map<std::string, ParamExpander> ParamExpanderMap;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Spill lights
    /// @{

    /*!
     * \details Calculates spill cone width value.
     * \code 
     *      return std::cos(coneInRadians * 0.5f); 
     * \endcode
     * \note https://developer.x-plane.com/?article=airplane-parameterized-light-guide#List_of_Named_Lights
     * \note LIGHT_SPILL_CUSTOM -> https://developer.x-plane.com/?article=obj8-file-format-specification
     *      
     * \param [in] coneInRadians Full (not half) light cone angle in radians.
     * \return valid value for x-plane.
     */
    XpObjLib static float spillConeWidthFromAngle(float coneInRadians);

    /*!
     * \details Converts spill cone to light cone angle.
     * \code 
     *      return std::acos(simValue) * 2.0f; 
     * \endcode
     * \see LightUtils::spillSemiFromAngle
     * \param [in] simValue the value from simulator's object.
     * \return Full (not half) light cone angle in radians.
     */
    XpObjLib static float spillConeWidthToAngle(float simValue);

    /// @}
    //-------------------------------------------------------------------------
    /// \name Billboard lights
    /// @{

    /*!
     * \details Calculates billboard cone width value.
     * \code 
     *      const auto angleCos = std::cos(coneInRadians * 0.5f);
     *      return angleCos / (angleCos - 1.0f);
     * \endcode
     * \note https://developer.x-plane.com/?article=airplane-parameterized-light-guide#List_of_Named_Lights
     *
     * \param [in] coneInRadians Full (not half) light cone angle in radians.
     * \return valid value for x-plane.
     */
    XpObjLib static float billboardConeWidthFromAngle(float coneInRadians);

    /*!
     * \details Converts billboard cone to light cone angle.
     * \code 
     *     return std::acos(simValue / (simValue - 1)) * 2.0f;
     * \endcode
     * \see LightUtils::billboardConeWidthFromAngle
     * \param [in] simValue the value from simulator's object.
     * \return Full (not half) light cone angle in radians.
     */
    XpObjLib static float billboardConeWidthToAngle(float simValue);

    /*!
     * \details Calculates billboard direction scale value.
     * \code
     *      return 1.0f - billboardConeWidthFromAngle(coneInRadians);
     * \endcode
     * \note https://developer.x-plane.com/?article=airplane-parameterized-light-guide#List_of_Named_Lights
     *
     * \param [in] coneInRadians Full (not half) light cone angle in radians.
     * \return valid value for x-plane.
     */
    static float billboardDirectionScaleFromAngle(const float coneInRadians) {
        return 1.0f - billboardConeWidthFromAngle(coneInRadians);
    }

    /*!
     * \details Billboard light can have cone angle up to 360 degrees but
     *          3d program usually has light with maximum 180 cone angle.
     *          
     *          This method takes "$direction" variable that can have additional parameter
     *          for billboard and then extracts and applies that parameter to the current cone angle.
     *          - "$direction:a+10" - adds 10 degrees to current angle.
     *          - "$direction:a-10" - subtract 10 degrees to current angle.
     *          - "$direction:a10" - set 10 degrees as current angle.
     *          - "$direction" - doesn't change current angle.
     *          
     * \details Use case for this methods is to give user ability 
     *          to set light cone angle for billboard directly or relative of 
     *          3D program's light value.<br>
     *          Assume we want spill light with cone angle 90 and we want 
     *          billboard glow light with cone angle 120 the param light may look like:<br>
     *          - create light in you 3D program with cone angle 90
     *          - apply a spill param light like 'name_of_light_sp $rgb index size $direction $width'
     *          - apply a billboard param light like 'name_of_light_glow $direction:a+30 index size'
     *          - or a billboard param light like 'name_of_light_glow $direction:a120 index size'
     *          
     *          This just example and real param light script may look different
     *          it depends on implementation param light in your 3D program.
     *          
     * \note https://developer.x-plane.com/?article=airplane-parameterized-light-guide#List_of_Named_Lights
     *          
     * \param [in] directionVar 
     * \param [in] currentAngle 
     * \return [Variable without additional parameter, Corrected cone angle].
     * \exception std::runtime_error if variable isn't "$direction" or additional parameters is incorrect.
     * \exception std::invalid_argument if some expanded values could not be converted.
     * \exception std::out_of_range if some expanded values could not be converted.
     */
    XpObjLib static std::tuple<std::string, float> billboardCorrectConeAngle(const std::string & directionVar, float currentAngle);

    /// @}
    //-------------------------------------------------------------------------
    /// \name Param lights
    /// @{

    /*!
     * \details This methods detects variables in the parameters string
     *          and search getter for that variable in the specified getters
     *          then calls getter and rewrite the variable with the result.
     * \details Variable starts with $ symbol and may contain [a-z,A-Z,1-9] characters only.
     *          Example: &direction $color $cone_sp
     * \param [in] params string with params.
     * \param [in] paramsGetter getters for variables.
     * \exception std::runtime_error if getter for variable isn't specified or variable syntax incorrect.
     */
    XpObjLib static std::string replaceVariables(const std::string & params,
                                                 const ParamExpanderMap & paramsGetter);

    /// @}
    //-------------------------------------------------------------------------
};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
