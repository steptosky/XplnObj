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

#pragma once

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
		AttrSet(const AttrSet & inCopy);
		AttrSet & operator=(const AttrSet & inCopy);

		bool operator==(const AttrSet & inOther) const;
		bool operator!=(const AttrSet & inOther) const;

		virtual ~AttrSet();

		//-------------------------------------------------------------------------

		void setSunLight(bool inEnable);
		void setTwoSided(bool inEnable);
		void setDraw(bool inState);
		void setDraped(bool inState);
		void setCastShadow(bool inState);
		void setSolidForCamera(bool inState);

		void setPolyOffset(const AttrPolyOffset & inValue);
		void setShiny(const AttrShiny & inShiny);
		void setBlend(const AttrBlend & inBlend);
		void setHard(const AttrHard & inSurface);
		void setLightLevel(const AttrLightLevel & inLightLevel);
		void setManipulator(AttrManipBase * inManip); //!< takes ownership
		void setCockpit(const AttrCockpit & inAttr);

		//-------------------------------------------------------------------------

		bool isSunLight() const;
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
		bool mIsSunLight : 1;
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
		mIsSunLight(true),
		mIsTwoSided(false),
		mIsCastShadow(true),
		mIsSolidForCamera(false) {}

	inline AttrSet::AttrSet(const AttrSet & inCopy) {
		this->operator=(inCopy);
	}

	inline void AttrSet::reset() {
		mIsDraw = true;
		mIsDraped = false;
		mIsSunLight = true;
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

	inline AttrSet & AttrSet::operator=(const AttrSet & inCopy) {
		inCopy.mAttrManipBase ?
			setManipulator(inCopy.mAttrManipBase->clone()) : setManipulator(nullptr);

		mAttrLightLevel = inCopy.mAttrLightLevel;
		mAttrPolyOffset = inCopy.mAttrPolyOffset;
		mAttrBlend = inCopy.mAttrBlend;
		mAttrShiny = inCopy.mAttrShiny;
		mAttrHard = inCopy.mAttrHard;
		mAttrCockpit = inCopy.mAttrCockpit;

		mIsDraw = inCopy.mIsDraw;
		mIsTwoSided = inCopy.mIsTwoSided;
		mIsDraped = inCopy.mIsDraped;
		mIsSunLight = inCopy.mIsSunLight;
		mIsCastShadow = inCopy.mIsCastShadow;
		mIsSolidForCamera = inCopy.mIsSolidForCamera;
		return *this;
	}

	inline AttrSet::~AttrSet() {
		setManipulator(nullptr);
	}

	//-------------------------------------------------------------------------

	inline bool AttrSet::operator==(const AttrSet & inOther) const {
		if (mAttrManipBase != nullptr) {
			if (!mAttrManipBase->equals(inOther.mAttrManipBase)) {
				return false;
			}
		}
		return mAttrLightLevel == inOther.mAttrLightLevel &&
				mAttrPolyOffset == inOther.mAttrPolyOffset &&
				mAttrBlend == inOther.mAttrBlend &&
				mAttrShiny == inOther.mAttrShiny &&
				mAttrHard == inOther.mAttrHard &&
				mAttrCockpit == inOther.mAttrCockpit &&

				mIsDraw == inOther.mIsDraw &&
				mIsTwoSided == inOther.mIsTwoSided &&
				mIsDraped == inOther.mIsDraped &&
				mIsSunLight == inOther.mIsSunLight &&
				mIsCastShadow == inOther.mIsCastShadow &&
				mIsSolidForCamera == inOther.mIsSolidForCamera;
	}

	inline bool AttrSet::operator!=(const AttrSet & inOther) const {
		return !this->operator==(inOther);
	}

	//-------------------------------------------------------------------------

	inline void AttrSet::setSunLight(bool inState) {
		mIsSunLight = inState;
	}

	inline void AttrSet::setTwoSided(bool inState) {
		mIsTwoSided = inState;
	}

	inline void AttrSet::setDraw(bool inState) {
		mIsDraw = inState;
	}

	inline void AttrSet::setDraped(bool inState) {
		mIsDraped = inState;
	}

	inline void AttrSet::setCastShadow(bool inState) {
		mIsCastShadow = inState;
	}

	inline void AttrSet::setSolidForCamera(bool inState) {
		mIsSolidForCamera = inState;
	}

	inline void AttrSet::setPolyOffset(const AttrPolyOffset & inValue) {
		mAttrPolyOffset = inValue;
	}

	inline void AttrSet::setShiny(const AttrShiny & inShiny) {
		mAttrShiny = inShiny;
	}

	inline void AttrSet::setBlend(const AttrBlend & inBlend) {
		mAttrBlend = inBlend;
	}

	inline void AttrSet::setHard(const AttrHard & inSurface) {
		mAttrHard = inSurface;
	}

	inline void AttrSet::setLightLevel(const AttrLightLevel & inLightLevel) {
		mAttrLightLevel = inLightLevel;
	}

	inline void AttrSet::setManipulator(AttrManipBase * inManip) {
		delete mAttrManipBase;
		mAttrManipBase = inManip;
	}

	inline void AttrSet::setCockpit(const AttrCockpit & inAttr) {
		mAttrCockpit = inAttr;
	}

	//-------------------------------------------------------------------------

	inline bool AttrSet::isSunLight() const {
		return mIsSunLight;
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
