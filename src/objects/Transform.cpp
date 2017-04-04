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

#include "xpln/obj/Transform.h"
#include "sts/utilities/templates/TreeItem.h"
#include "xpln/obj/ObjAbstract.h"
#include "../common/Logger.h"
#include "sts/geometry/TMatrix3.h"

namespace xobj {

	/**************************************************************************************************/
	//////////////////////////////////////////* Static area *///////////////////////////////////////////
	/**************************************************************************************************/

	class TreeItem : public sts_t::TreeItem<TreeItem> {
	public:

		TreeItem(Transform * inTransformTree)
			: mTransformTree(inTransformTree),
			mIsCallDestructor(true) { }

		void setData(Transform * val) {
			mTransformTree = val;
		}

		Transform * data() {
			return mTransformTree;
		}

		TreeItem * clone() const {
			return nullptr;
		}

		~TreeItem() {
			// remove loop calling of the destructors
			if (mIsCallDestructor) {
				mTransformTree->mTreePtr = nullptr;
				delete mTransformTree;
			}
		}

	private:

		// remove loop calling of the destructors
		friend Transform;

		bool mIsCallDestructor;
		Transform * mTransformTree;

	};

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	Transform::Transform() {
		mTreePtr = new TreeItem(this);
	}

	Transform::~Transform() {
		for (auto & curr : mObjList) {
			curr->mObjTransform = nullptr;
			delete curr;
		}
		// remove loop calling of the destructors
		if (mTreePtr) {
			mTreePtr->mIsCallDestructor = false;
			delete mTreePtr;
		}
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool Transform::isRoot() const {
		return mTreePtr->isRoot();
	}

	void Transform::setParent(Transform * inParent) {
		mTreePtr->setParent(static_cast<TreeItem*>(inParent->mTreePtr));
	}

	Transform * Transform::parent() {
		if (isRoot())
			return nullptr;
		return mTreePtr->parent()->data();
	}

	const Transform * Transform::parent() const {
		if (isRoot())
			return nullptr;
		return mTreePtr->parent()->data();
	}

	Transform::TransformIndex Transform::childrenCount() const {
		return static_cast<TransformIndex>(mTreePtr->childrenCount());
	}

	Transform * Transform::childAt(TransformIndex inIndex) {
		return mTreePtr->childAt(inIndex)->data();
	}

	const Transform * Transform::childAt(TransformIndex inIndex) const {
		return mTreePtr->childAt(inIndex)->data();
	}

	bool Transform::isChildOf(const Transform * parent) const {
		return mTreePtr->isChildOf(parent->mTreePtr);
	}

	Transform * Transform::takeChildAt(TransformIndex inIndex) {
		return mTreePtr->takeChildAt(inIndex)->data();
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	Transform * Transform::root() {
		return mTreePtr->root()->data();
	}

	const Transform * Transform::root() const {
		return mTreePtr->root()->data();
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	void Transform::addObject(ObjAbstract * inObj) {
		if (inObj) {
			for (auto curr : mObjList) {
				if (curr == inObj) {
					LWarning << " You try to add an object which is already exist.";
					return;
				}
			}

			inObj->mObjTransform = this;
			mObjList.push_back(inObj);
		}
	}

	bool Transform::removeObject(ObjAbstract * inObj) {
		if (inObj) {
			for (auto it = mObjList.begin(); it != mObjList.end(); ++it) {
				if (*it == inObj) {
					(*it)->mObjTransform = nullptr;
					mObjList.erase(it);
					return true;
				}
			}
		}
		return false;
	}

	const Transform::ObjList & Transform::objList() const {
		return mObjList;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool Transform::_checkForParity(const Transform & inParent, bool state /*= false*/) {
		static bool res = false;
		res = state;
		if (inParent.pMatrix.isParity())
			res = !res;
		if (inParent.isRoot())
			return res;
		return _checkForParity(*inParent.parent(), res);
	}

	bool Transform::checkHierarchyForParity() const {
		return _checkForParity(*this, false);
	}

	//-------------------------------------------------------------------------

	const std::string & Transform::name() const {
		return mName;
	}

	void Transform::setName(const std::string & val) {
		mName = val;
	}

	/**************************************************************************************************/
	///////////////////////////////////////////* Functions *////////////////////////////////////////////
	/**************************************************************************************************/

	bool Transform::hasAnim() const {
		return hasAnimRotate() || hasAnimTrans() || hasAnimVis();
	}

	bool Transform::hasAnimRotate() const {
		for (auto & a : pAnimRotate) {
			if (a.isAnimated()) {
				return true;
			}
		}
		return false;
	}

	bool Transform::hasAnimTrans() const {
		for (auto & a : pAnimTrans) {
			if (a.isAnimated()) {
				return true;
			}
		}
		return false;
	}

	bool Transform::hasAnimVis() const {
		return pAnimVis.isAnimated();
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
