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

#include <cstddef>
#include <tuple>
#include "ObjAbstract.h"
#include "xpln/common/Point3.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the particle emitter.
 * \ingroup Objects
 */
class ObjEmitter : public ObjAbstract {
protected:

    ObjEmitter(const ObjEmitter &) = default;
    ObjEmitter(ObjEmitter &&) = default;

public:

    //-------------------------------------------------------------------------
    /// @{

    ObjEmitter() = default;

    virtual ~ObjEmitter() = default;

    ObjEmitter & operator=(const ObjEmitter &) = delete;
    ObjEmitter & operator=(ObjEmitter &&) = delete;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    /*!
     * \details Name of the emitter. Must be one from your .pss file.
     * \param [in] name from your .pss file.
     */
    void setName(const std::string & name) {
        mName = name;
    }

    /*!
     * \returnt emitter name.
     */
    const std::string & name() const {
        return mName;
    }

    /*!
     * \details Orientation - degrees roll, pitch, heading in Eulers.
     * \param [in] psi roll.
     * \param [in] the pitch.
     * \param [in] phi heading.
     */
    void setOrientation(const float psi, const float the, const float phi) {
        mPsi = psi;
        mThe = the;
        mPhi = phi;
    }

    /*!
     * \returnt [psi, the, phi].
     */
    std::tuple<float, float, float> orientation() const {
        return std::make_tuple(mPsi, mThe, mPhi);
    }

    /*!
     * \details Orientation - degrees roll, pitch, heading in Eulers.
     * \param [in] index Optional, if left out it is assumed to be 0.
     */
    void setIndex(const std::size_t index) {
        mIndex = index;
    }

    /*!
     * \returnt index.
     */
    std::size_t index() const {
        return mIndex;
    }

    void setPosition(const Point3 & pos) {
        mPosition = pos;
    }

    const Point3 & position() const {
        return mPosition;
    }

    /// @}
    //-------------------------------------------------------------------------
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

    std::string mName;
    Point3 mPosition;
    float mPsi = 0.0f;
    float mThe = 0.0f;
    float mPhi = 0.0f;
    std::size_t mIndex = 0;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
