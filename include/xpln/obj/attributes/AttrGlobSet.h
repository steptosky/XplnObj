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

#include "xpln/obj/attributes/AttrBlend.h"
#include "xpln/obj/attributes/AttrDrapedLayerGroup.h"
#include "xpln/obj/attributes/AttrLayerGroup.h"
#include "xpln/obj/attributes/AttrLodDrap.h"
#include "xpln/obj/attributes/AttrSlungLoadWeight.h"
#include "xpln/obj/attributes/AttrSpecular.h"
#include "xpln/obj/attributes/AttrTint.h"
#include "xpln/obj/attributes/AttrWetDry.h"
#include "xpln/obj/attributes/AttrSlopeLimit.h"
#include "xpln/obj/attributes/AttrCockpitRegion.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details Representation of the global attributes set
	 * \ingroup Attributes
	 */
	class AttrGlobSet {
	public:

		AttrGlobSet();
		virtual ~AttrGlobSet() = default;

		//-------------------------------------------------------------------------

		void setTexture(const std::string & inVal);
		void setTextureLit(const std::string & inVal);
		void setTextureNormal(const std::string & inVal);

		void setNormalMetalness(bool inVal);
		void setBlendGlass(bool inVal);
		void setTilted(bool inVal);
		void setNoShadow(bool inVal);
		void setCockpitLit(bool inVal);
		void setDebug(bool inVal);

		void setWetDry(const AttrWetDry & inVal);
		void setBlend(const AttrBlend & inVal);
		void setLayerGroup(const AttrLayerGroup & inVal);
		void setLayerGroupDraped(const AttrDrapedLayerGroup & inVal);
		void setLodDrap(const AttrLodDrap & inVal);
		void setSlungLoadWeight(const AttrSlungLoadWeight & inVal);
		void setSpecular(const AttrSpecular & inVal);
		void setTint(const AttrTint & inVal);
		void setSlopeLimit(const AttrSlopeLimit & inVal);
		void setCockpitRegion(const AttrCockpitRegion & inVal, AttrCockpitRegion::eNum inNum);

		const std::string & texture() const;
		const std::string & textureLit() const;
		const std::string & textureNormal() const;

		bool isNormalMetalness() const;
		bool isBlendGlass() const;
		bool isTilted() const;
		bool isNoShadow() const;
		bool isCockpitLit() const;
		bool isDebug() const;

		const AttrWetDry & wetDry() const;
		const AttrBlend & blend() const;
		const AttrLayerGroup & layerGroup() const;
		const AttrDrapedLayerGroup & layerGroupDraped() const;
		const AttrLodDrap & lodDrap() const;
		const AttrSlungLoadWeight & slungLoadWeight() const;
		const AttrSpecular & specular() const;
		const AttrTint & tint() const;
		const AttrSlopeLimit & slopeLimit() const;
		const AttrCockpitRegion & cockpitRegion(AttrCockpitRegion::eNum inNum) const;

		//-------------------------------------------------------------------------

		void reset();

	private:

		std::string mTexture;
		std::string mTextureLit;
		std::string mTextureNormal;

		AttrBlend mBlend;
		AttrLayerGroup mLayerGroup;
		AttrDrapedLayerGroup mLayerGroupDraped;
		AttrLodDrap mLodDrap;
		AttrSlungLoadWeight mSlungLoadWeight;
		AttrSpecular mSpecular;
		AttrTint mTint;
		AttrWetDry mAttrWetDry;
		AttrSlopeLimit mAttrSlopeLimit;
		AttrCockpitRegion mAttrCockpitRegion[4];

		bool mBlendClass : 1;
		bool mNormalMetalness : 1;
		bool mTilted : 1;
		bool mDropShadow : 1;
		bool mIsWet : 1;
		bool mIsDry : 1;
		bool mIsCockpitLit : 1;
		bool mIsDebug : 1;

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	inline AttrGlobSet::AttrGlobSet()
		: mBlendClass(false),
		mNormalMetalness(false),
		mTilted(false),
		mDropShadow(false),
		mIsWet(false),
		mIsDry(false),
		mIsCockpitLit(false),
		mIsDebug(false) {}

	inline void AttrGlobSet::reset() {
		mBlendClass = false;
		mNormalMetalness = false;
		mTilted = false;
		mDropShadow = false;
		mIsWet = false;
		mIsDry = false;
		mIsCockpitLit = false;
		mIsDebug = false;

		mTexture.clear();
		mTextureLit.clear();
		mTextureNormal.clear();

		mBlend = AttrBlend();
		mLayerGroup = AttrLayerGroup();
		mLayerGroupDraped = AttrDrapedLayerGroup();
		mLodDrap = AttrLodDrap();
		mSlungLoadWeight = AttrSlungLoadWeight();
		mSpecular = AttrSpecular();
		mTint = AttrTint();
		mAttrWetDry = AttrWetDry();
		mAttrSlopeLimit = AttrSlopeLimit();
		mAttrCockpitRegion[0] = AttrCockpitRegion();
		mAttrCockpitRegion[1] = AttrCockpitRegion();
		mAttrCockpitRegion[2] = AttrCockpitRegion();
		mAttrCockpitRegion[3] = AttrCockpitRegion();
	}

	/**************************************************************************************************/
	//////////////////////////////////////////* Functions */////////////////////////////////////////////
	/**************************************************************************************************/

	inline void AttrGlobSet::setTexture(const std::string & inVal) {
		mTexture = inVal;
	}

	inline const std::string & AttrGlobSet::texture() const {
		return mTexture;
	}

	inline void AttrGlobSet::setTextureLit(const std::string & inVal) {
		mTextureLit = inVal;
	}

	inline const std::string & AttrGlobSet::textureLit() const {
		return mTextureLit;
	}

	inline void AttrGlobSet::setTextureNormal(const std::string & inVal) {
		mTextureNormal = inVal;
	}

	inline const std::string & AttrGlobSet::textureNormal() const {
		return mTextureNormal;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	inline void AttrGlobSet::setNormalMetalness(bool inVal) {
		mNormalMetalness = inVal;
	}

	inline bool AttrGlobSet::isNormalMetalness() const {
		return mNormalMetalness;
	}

	inline void AttrGlobSet::setBlendGlass(bool inVal) {
		mBlendClass = inVal;
	}

	inline bool AttrGlobSet::isBlendGlass() const {
		return mBlendClass;
	}

	inline void AttrGlobSet::setTilted(bool inVal) {
		mTilted = inVal;
	}

	inline bool AttrGlobSet::isTilted() const {
		return mTilted;
	}

	inline void AttrGlobSet::setNoShadow(bool inVal) {
		mDropShadow = inVal;
	}

	inline bool AttrGlobSet::isNoShadow() const {
		return mDropShadow;
	}

	inline void AttrGlobSet::setCockpitLit(bool inVal) {
		mIsCockpitLit = inVal;
	}

	inline void AttrGlobSet::setDebug(bool inVal) {
		mIsDebug = inVal;
	}

	inline bool AttrGlobSet::isCockpitLit() const {
		return mIsCockpitLit;
	}

	inline bool AttrGlobSet::isDebug() const {
		return mIsDebug;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	inline void AttrGlobSet::setBlend(const AttrBlend & inVal) {
		mBlend = inVal;
	}

	inline const AttrBlend & AttrGlobSet::blend() const {
		return mBlend;
	}

	inline void AttrGlobSet::setLayerGroup(const AttrLayerGroup & inVal) {
		mLayerGroup = inVal;
	}

	inline const AttrLayerGroup & AttrGlobSet::layerGroup() const {
		return mLayerGroup;
	}

	inline void AttrGlobSet::setLayerGroupDraped(const AttrDrapedLayerGroup & inVal) {
		mLayerGroupDraped = inVal;
	}

	inline const AttrDrapedLayerGroup & AttrGlobSet::layerGroupDraped() const {
		return mLayerGroupDraped;
	}

	inline void AttrGlobSet::setLodDrap(const AttrLodDrap & inVal) {
		mLodDrap = inVal;
	}

	inline const AttrLodDrap & AttrGlobSet::lodDrap() const {
		return mLodDrap;
	}

	inline void AttrGlobSet::setSlungLoadWeight(const AttrSlungLoadWeight & inVal) {
		mSlungLoadWeight = inVal;
	}

	inline const AttrSlungLoadWeight & AttrGlobSet::slungLoadWeight() const {
		return mSlungLoadWeight;
	}

	inline void AttrGlobSet::setSpecular(const AttrSpecular & inVal) {
		mSpecular = inVal;
	}

	inline const AttrSpecular & AttrGlobSet::specular() const {
		return mSpecular;
	}

	inline void AttrGlobSet::setTint(const AttrTint & inVal) {
		mTint = inVal;
	}

	inline const AttrTint & AttrGlobSet::tint() const {
		return mTint;
	}

	inline void AttrGlobSet::setWetDry(const AttrWetDry & inVal) {
		mAttrWetDry = inVal;
	}

	inline const AttrWetDry & AttrGlobSet::wetDry() const {
		return mAttrWetDry;
	}

	inline void AttrGlobSet::setSlopeLimit(const AttrSlopeLimit & inVal) {
		mAttrSlopeLimit = inVal;
	}

	inline const AttrSlopeLimit & AttrGlobSet::slopeLimit() const {
		return mAttrSlopeLimit;
	}

	inline void AttrGlobSet::setCockpitRegion(const AttrCockpitRegion & inVal, AttrCockpitRegion::eNum inNum) {
		mAttrCockpitRegion[static_cast<size_t>(inNum)] = inVal;
	}

	inline const AttrCockpitRegion & AttrGlobSet::cockpitRegion(AttrCockpitRegion::eNum inNum) const {
		return mAttrCockpitRegion[static_cast<size_t>(inNum)];
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
