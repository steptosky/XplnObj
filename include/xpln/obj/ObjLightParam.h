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

#include <string>
#include <map>
#include "ObjAbstractLight.h"
#include "xpln/common/Color.h"
#include "xpln/utils/LightUtils.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the parameterized light
 * \ingroup Objects
 */
class ObjLightParam : public ObjAbstractLight {
protected:

    ObjLightParam(const ObjLightParam &) = default;
    ObjLightParam(ObjLightParam &&) = default;

public:

    //-------------------------------------------------------------------------
    /// \name Construction/Destruction
    /// @{

    XpObjLib ObjLightParam();
    virtual ~ObjLightParam() = default;

    ObjLightParam & operator=(const ObjLightParam &) = delete;
    ObjLightParam & operator=(ObjLightParam &&) = delete;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Parameters
    /// @{

    void setName(const std::string & name) {
        mLightName = name;
    }

    const std::string & name() const {
        return mLightName;
    }

    /*!
     * \details Sets and expands parameters.
     * \pre Use \link LightUtils \endlink to calculate some parameters.
     * 
     * \warning There are some predefined variables.
     *          Those variables will be processed during export and can't be calculated before it.<br>
     *          Although they are processed while exporting they are retrieved with this method
     *          and after this method done the "expander" may be deleted.
     *          \li $direction_sp - X Y Z. Spill light direction.
     *          \li $direction - X Y Z S. Billboard direction. It uses addition scale parameter.<br>
     *                           The scale must be set with the \link LightUtils::billboardDirectionScaleFromAngle \endlink.<br>
     *                           For more information about billboard scaling see
     *                           https://developer.x-plane.com/?article=airplane-parameterized-light-guide#Cone_Width_for_Billboard_Lights <br>
     *                           It doesn't make a sense to scale direction before set it
     *                           because the direction vector will be changed by 
     *                           \link ObjLightParam::applyTransform \endlink and normalized.
     *                           
     *          
     * \warning You can use some methods from \link LightUtils \endlink
     *          but you must not use \link LightUtils::replaceVariables \endlink
     *          directly instead of this method.
     *          
     * \note Example:
     * \code
     *  setParams("$direction_sp 0 $myParam", {
     *      {"direction", [&]() { return "0 -1 0"; }},
     *      {"myParam", [&]() { return "20.0"; }},
     *  });
     * \endcode
     * 
     * \param [in] params string that may contain values and variables.
     *                    The string musts not contain light name and position.
     *                    They should be set with the corresponding class methods.
     * \param [in] expander variables expander. The key is the variable name without $ the value is functional.
     * 
     * \exception std::runtime_error if getter for variable isn't specified 
     *                               or variable syntax incorrect
     *                               or returned by expander value is incorrect.
     * \exception std::invalid_argument if some expanded values could not be converted.
     * \exception std::out_of_range if some expanded values could not be converted.
     */
    XpObjLib void setParams(const std::string & params, const LightUtils::ParamExpanderMap & expander);

    XpObjLib std::string params() const;

    /// @}
    //-------------------------------------------------------------------------
    /// \name
    /// @{

    /*! \copydoc ObjAbstract::objType */
    XpObjLib eObjectType objType() const final;

    /*! \copydoc ObjAbstract::applyTransform */
    XpObjLib void applyTransform(const TMatrix & tm, bool useParity = false) override final;

    /*! \copydoc ObjAbstract::clone */
    XpObjLib ObjAbstract * clone() const override;

    /// @}
    //-------------------------------------------------------------------------

private:

    float mBillboardScale = 1.0f;
    bool mIsSpill = false;
    bool mIsDirection = false;
    Point3 mDirection;
    std::string mLightName;
    std::string mParams;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
