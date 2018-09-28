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

#include "Transform.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the LOD object
 * \ingroup Objects
 */
class ObjLodGroup {
public:

    //--------------------------------------------------------

    ObjLodGroup()
        : ObjLodGroup(0.0f, 0.0f) {}

    ObjLodGroup(const float nearVal, const float farVal)
        : ObjLodGroup("LOD", nearVal, farVal) {}

    ObjLodGroup(const std::string & name, const float nearVal, const float farVal)
        : mName(name),
          mNear(nearVal),
          mFar(farVal) {

        mObjTransform.setName(name);
    }

    ObjLodGroup(const ObjLodGroup &) = delete;
    ObjLodGroup & operator =(const ObjLodGroup &) = delete;

    virtual ~ObjLodGroup() = default;

    //--------------------------------------------------------

    void setNearVal(const float val) {
        mNear = val;
    }

    void setFarVal(const float val) {
        mFar = val;
    }

    float nearVal() const {
        return mNear;
    }

    float farVal() const {
        return mFar;
    }

    //--------------------------------------------------------

    void setObjectName(const std::string & name) {
        mName = name;
        mObjTransform.setName(name);
    }

    const std::string & objectName() const {
        return mName;
    }

    //--------------------------------------------------------

    /*! \copydoc ObjAbstract::transform */
    Transform & transform() {
        return mObjTransform;
    }

    /*! \copydoc ObjAbstract::transform */
    const Transform & transform() const {
        return mObjTransform;
    }

    //--------------------------------------------------------

private:

    Transform mObjTransform;
    std::string mName;
    float mNear;
    float mFar;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
