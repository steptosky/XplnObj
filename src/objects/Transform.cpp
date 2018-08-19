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

#include "stdafx.h"

#include "xpln/obj/Transform.h"
#include "sts/utilities/templates/TreeItem.h"
#include "xpln/obj/ObjAbstract.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

class TreeItem : public sts_t::TreeItem<TreeItem> {
public:

    TreeItem(Transform * inTransformTree)
        : mIsCallDestructor(true),
          mTransformTree(inTransformTree) { }

    void setData(Transform * val) {
        mTransformTree = val;
    }

    Transform * data() {
        return mTransformTree;
    }

    TreeItem * clone() const override {
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

void Transform::setParent(Transform * parent) {
    mTreePtr->setParent(static_cast<TreeItem*>(parent->mTreePtr));
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

Transform * Transform::childAt(TransformIndex index) {
    return mTreePtr->childAt(index)->data();
}

const Transform * Transform::childAt(TransformIndex index) const {
    return mTreePtr->childAt(index)->data();
}

bool Transform::isChildOf(const Transform * parent) const {
    return mTreePtr->isChildOf(parent->mTreePtr);
}

Transform * Transform::takeChildAt(TransformIndex index) {
    return mTreePtr->takeChildAt(index)->data();
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

void Transform::addObject(ObjAbstract * baseObj) {
    if (baseObj) {
        for (auto curr : mObjList) {
            if (curr == baseObj) {
                LWarning << " You try to add an object which is already exist.";
                return;
            }
        }

        baseObj->mObjTransform = this;
        mObjList.push_back(baseObj);
    }
}

bool Transform::removeObject(ObjAbstract * baseObj) {
    if (baseObj) {
        for (auto it = mObjList.begin(); it != mObjList.end(); ++it) {
            if (*it == baseObj) {
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

bool Transform::hierarchicalParity(const Transform & parent, bool state) {
    if (parent.pMatrix.parity()) {
        state = !state;
    }
    if (parent.isRoot()) {
        return state;
    }
    return hierarchicalParity(*parent.parent(), state);
}

bool Transform::hierarchicalParity() const {
    return hierarchicalParity(*this, false);
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
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool Transform::visitObjects(const std::function<bool(ObjAbstract &)> & function) {
    for (auto o : mObjList) {
        assert(o);
        if (!function(*o)) {
            return false;
        }
    }
    return true;
}

bool Transform::visitObjects(const std::function<bool(const ObjAbstract &)> & function) const {
    for (const auto o : mObjList) {
        assert(o);
        if (!function(*o)) {
            return false;
        }
    }
    return true;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

bool Transform::visitAllOf(Transform * parent, const std::function<bool(Transform &)> & function) {
    TransformIndex numChildren = parent->childrenCount();
    for (TransformIndex idx = 0; idx < numChildren; ++idx) {
        Transform * currNode = parent->childAt(idx);
        if (!function(*currNode)) {
            return false;
        }
        if (!visitAllOf(currNode, function)) {
            return false;
        }
    }
    return true;
}

bool Transform::visitAllOf(const Transform * parent, const std::function<bool(const Transform &)> & function) {
    TransformIndex numChildren = parent->childrenCount();
    for (TransformIndex idx = 0; idx < numChildren; ++idx) {
        const Transform * currNode = parent->childAt(idx);
        if (!function(*currNode)) {
            return false;
        }
        if (!visitAllOf(currNode, function)) {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------

bool Transform::visitChildren(Transform * parent, const std::function<bool(Transform &)> & function) {
    TransformIndex count = parent->childrenCount();
    for (TransformIndex i = 0; i < count; ++i) {
        if (!function(*parent->childAt(i))) {
            return false;
        }
    }
    return true;
}

bool Transform::visitChildren(const Transform * parent, const std::function<bool(const Transform &)> & function) {
    TransformIndex count = parent->childrenCount();
    for (TransformIndex i = 0; i < count; ++i) {
        if (!function(*parent->childAt(i))) {
            return false;
        }
    }
    return true;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
