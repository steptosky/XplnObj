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

#include <optional>
#include "xpln/obj/attributes/AttrHard.h"
#include "xpln/obj/attributes/AttrShiny.h"
#include "xpln/obj/attributes/AttrBlend.h"
#include "xpln/obj/attributes/AttrPolyOffset.h"
#include "xpln/obj/manipulators/AttrManipBase.h"
#include "xpln/obj/attributes/AttrLightLevel.h"
#include "xpln/obj/attributes/AttrCockpit.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Representation of the attributes set
 * \ingroup Attributes
 */
class AttrSet final {
public:

    //-------------------------------------------------------------------------
    /// @{

    AttrSet() = default;
    AttrSet(const AttrSet & copy) { this->operator=(copy); }
    AttrSet(AttrSet &&) = delete;

    bool operator==(const AttrSet & other) const {
        if (mAttrManipBase != nullptr) {
            if (!mAttrManipBase->equals(other.mAttrManipBase)) {
                return false;
            }
        }
        return mAttrLightLevel == other.mAttrLightLevel &&
               mAttrPolyOffset == other.mAttrPolyOffset &&
               mAttrBlend == other.mAttrBlend &&
               mAttrShiny == other.mAttrShiny &&
               mAttrHard == other.mAttrHard &&
               mAttrCockpit == other.mAttrCockpit &&

               mIsDraw == other.mIsDraw &&
               mIsTwoSided == other.mIsTwoSided &&
               mIsDraped == other.mIsDraped &&
               mIsTree == other.mIsTree &&
               mIsCastShadow == other.mIsCastShadow &&
               mIsSolidForCamera == other.mIsSolidForCamera;
    }

    bool operator!=(const AttrSet & other) const { return !this->operator==(other); }

    ~AttrSet() { setManipulator(nullptr); }

    AttrSet & operator=(const AttrSet & copy) {
        copy.mAttrManipBase ? setManipulator(copy.mAttrManipBase->clone()) : setManipulator(nullptr);

        mAttrLightLevel = copy.mAttrLightLevel;
        mAttrPolyOffset = copy.mAttrPolyOffset;
        mAttrBlend = copy.mAttrBlend;
        mAttrShiny = copy.mAttrShiny;
        mAttrHard = copy.mAttrHard;
        mAttrCockpit = copy.mAttrCockpit;

        mIsDraw = copy.mIsDraw;
        mIsTwoSided = copy.mIsTwoSided;
        mIsDraped = copy.mIsDraped;
        mIsTree = copy.mIsTree;
        mIsCastShadow = copy.mIsCastShadow;
        mIsSolidForCamera = copy.mIsSolidForCamera;
        return *this;
    }

    AttrSet & operator=(AttrSet &&) = delete;

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    void reset() {
        setManipulator(nullptr);
        const AttrSet clear;
        this->operator=(clear);
    }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    //!< takes ownership
    void setManipulator(AttrManipBase * manip) {
        delete mAttrManipBase;
        mAttrManipBase = manip;
    }

    const AttrManipBase * manipulator() const {
        return mAttrManipBase;
    }

    /// @}
    //-------------------------------------------------------------------------
    /// @{

    std::optional<AttrLightLevel> mAttrLightLevel;
    std::optional<AttrPolyOffset> mAttrPolyOffset;
    std::optional<AttrBlend> mAttrBlend;
    std::optional<AttrShiny> mAttrShiny;
    std::optional<AttrHard> mAttrHard;
    std::optional<AttrCockpit> mAttrCockpit;

    bool mIsDraw = true;
    bool mIsDraped = false;
    bool mIsTree = false;
    bool mIsTwoSided = false;
    bool mIsCastShadow = true;
    bool mIsSolidForCamera = false;

    /// @}
    //-------------------------------------------------------------------------

private:

    AttrManipBase * mAttrManipBase = nullptr;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
