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
class AttrSet {
public:

    AttrSet();
    AttrSet(const AttrSet & copy);
    AttrSet & operator=(const AttrSet & copy);

    bool operator==(const AttrSet & other) const;
    bool operator!=(const AttrSet & other) const;

    virtual ~AttrSet();

    //-------------------------------------------------------------------------

    [[deprecated("use setTree instead")]]
    void setSunLight(const bool state) { setTree(!state); }

    void setTree(bool state);
    void setTwoSided(bool state);
    void setDraw(bool state);
    void setDraped(bool state);
    void setCastShadow(bool state);
    void setSolidForCamera(bool state);

    void setPolyOffset(const AttrPolyOffset & attr);
    void setShiny(const AttrShiny & attr);
    void setBlend(const AttrBlend & attr);
    void setHard(const AttrHard & attr);
    void setLightLevel(const AttrLightLevel & attr);
    void setManipulator(AttrManipBase * manip); //!< takes ownership
    void setCockpit(const AttrCockpit & attr);

    //-------------------------------------------------------------------------

    [[deprecated("use isTree instead")]]
    bool isSunLight() const { return !isTree(); }

    bool isTree() const;
    bool isTwoSided() const;
    bool isDraw() const;
    bool isDraped() const;
    bool isCastShadow() const;
    bool isSolidForCamera() const;

    const AttrPolyOffset & polyOffset() const;
    const AttrHard & hard() const;
    const AttrShiny & shiny() const;
    const AttrBlend & blend() const;
    const AttrLightLevel & lightLevel() const;
    const AttrManipBase * manipulator() const;
    const AttrCockpit & cockpit() const;

    //-------------------------------------------------------------------------

    void reset();

private:

    AttrManipBase * mAttrManipBase = nullptr;
    AttrLightLevel mAttrLightLevel;
    AttrPolyOffset mAttrPolyOffset;
    AttrBlend mAttrBlend;
    AttrShiny mAttrShiny;
    AttrHard mAttrHard;
    AttrCockpit mAttrCockpit;

    bool mIsDraw : 1;
    bool mIsDraped : 1;
    bool mIsTree : 1;
    bool mIsTwoSided : 1;
    bool mIsCastShadow : 1;
    bool mIsSolidForCamera : 1;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline AttrSet::AttrSet()
    : mIsDraw(true),
      mIsDraped(false),
      mIsTree(false),
      mIsTwoSided(false),
      mIsCastShadow(true),
      mIsSolidForCamera(false) {}

inline AttrSet::AttrSet(const AttrSet & copy) {
    this->operator=(copy);
}

inline void AttrSet::reset() {
    mIsDraw = true;
    mIsDraped = false;
    mIsTree = false;
    mIsTwoSided = false;
    mIsCastShadow = true;
    mIsSolidForCamera = false;

    setManipulator(nullptr);
    mAttrCockpit = AttrCockpit();
    mAttrLightLevel = AttrLightLevel();
    mAttrPolyOffset = AttrPolyOffset();
    mAttrBlend = AttrBlend();
    mAttrShiny = AttrShiny();
    mAttrHard = AttrHard();
}

inline AttrSet & AttrSet::operator=(const AttrSet & copy) {
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

inline AttrSet::~AttrSet() {
    setManipulator(nullptr);
}

//-------------------------------------------------------------------------

inline bool AttrSet::operator==(const AttrSet & other) const {
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

inline bool AttrSet::operator!=(const AttrSet & other) const {
    return !this->operator==(other);
}

//-------------------------------------------------------------------------

inline void AttrSet::setTree(const bool state) {
    mIsTree = state;
}

inline void AttrSet::setTwoSided(const bool state) {
    mIsTwoSided = state;
}

inline void AttrSet::setDraw(const bool state) {
    mIsDraw = state;
}

inline void AttrSet::setDraped(const bool state) {
    mIsDraped = state;
}

inline void AttrSet::setCastShadow(const bool state) {
    mIsCastShadow = state;
}

inline void AttrSet::setSolidForCamera(const bool state) {
    mIsSolidForCamera = state;
}

inline void AttrSet::setPolyOffset(const AttrPolyOffset & attr) {
    mAttrPolyOffset = attr;
}

inline void AttrSet::setShiny(const AttrShiny & attr) {
    mAttrShiny = attr;
}

inline void AttrSet::setBlend(const AttrBlend & attr) {
    mAttrBlend = attr;
}

inline void AttrSet::setHard(const AttrHard & attr) {
    mAttrHard = attr;
}

inline void AttrSet::setLightLevel(const AttrLightLevel & attr) {
    mAttrLightLevel = attr;
}

inline void AttrSet::setManipulator(AttrManipBase * manip) {
    delete mAttrManipBase;
    mAttrManipBase = manip;
}

inline void AttrSet::setCockpit(const AttrCockpit & attr) {
    mAttrCockpit = attr;
}

//-------------------------------------------------------------------------

inline bool AttrSet::isTree() const {
    return mIsTree;
}

inline bool AttrSet::isTwoSided() const {
    return mIsTwoSided;
}

inline bool AttrSet::isDraw() const {
    return mIsDraw;
}

inline bool AttrSet::isDraped() const {
    return mIsDraped;
}

inline bool AttrSet::isCastShadow() const {
    return mIsCastShadow;
}

inline bool AttrSet::isSolidForCamera() const {
    return mIsSolidForCamera;
}

inline const AttrPolyOffset & AttrSet::polyOffset() const {
    return mAttrPolyOffset;
}

inline const AttrHard & AttrSet::hard() const {
    return mAttrHard;
}

inline const AttrShiny & AttrSet::shiny() const {
    return mAttrShiny;
}

inline const AttrBlend & AttrSet::blend() const {
    return mAttrBlend;
}

inline const AttrLightLevel & AttrSet::lightLevel() const {
    return mAttrLightLevel;
}

inline const AttrManipBase * AttrSet::manipulator() const {
    return mAttrManipBase;
}

inline const AttrCockpit & AttrSet::cockpit() const {
    return mAttrCockpit;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
