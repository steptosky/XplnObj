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

#include "xpln/obj/Transform.h"
#include "sts/utilities/templates/TreeItem.h"
#include "xpln/obj/ObjAbstract.h"
#include "common/BaseLogger.h"

namespace xobj {

/**************************************************************************************************/
//////////////////////////////////////////* Static area *///////////////////////////////////////////
/**************************************************************************************************/

class TreeItem : public sts::tree::TreeItem<TreeItem> {
    // remove loop calling of the destructors
    friend Transform;
public:

    explicit TreeItem(Transform * inTransformTree)
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

    virtual ~TreeItem() {
        // remove loop calling of the destructors
        if (mIsCallDestructor) {
            mTransformTree->mTreePtr = nullptr;
            delete mTransformTree;
        }
    }

private:

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
        // During destruction object will 
        // try to delete itself from the transform.
        // This prevents it as it doesn't make a sense in this case.
        curr->mObjTransform = nullptr;
    }
    mObjList.clear();

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
    if (isRoot()) {
        return nullptr;
    }
    return mTreePtr->parent()->data();
}

const Transform * Transform::parent() const {
    if (isRoot()) {
        return nullptr;
    }
    return mTreePtr->parent()->data();
}

Transform::TransformIndex Transform::childrenNum() const {
    return static_cast<TransformIndex>(mTreePtr->childrenCount());
}

Transform * Transform::childAt(const TransformIndex index) {
    return mTreePtr->childAt(index)->data();
}

const Transform * Transform::childAt(const TransformIndex index) const {
    return mTreePtr->childAt(index)->data();
}

bool Transform::isChildOf(const Transform * transform) const {
    return mTreePtr->isChildOf(transform->mTreePtr);
}

Transform * Transform::takeChildAt(const TransformIndex index) {
    return mTreePtr->takeChildAt(index)->data();
}

bool Transform::deleteChild(const Transform * child) {
    return mTreePtr->deleteChild(child->mTreePtr);
}

Transform & Transform::newChild(const char * name) {
    auto * tr = new Transform;
    tr->setParent(this);
    if (name) {
        tr->setName(name);
    }
    return *tr;
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
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<typename O, typename F>
bool callForChildren(O * transform, const F & function) {
    const Transform::TransformIndex count = transform->childrenNum();
    for (Transform::TransformIndex i = 0; i < count; ++i) {
        if (!function(*transform->childAt(i))) {
            return false;
        }
    }
    return true;
}

template<typename O, typename F>
bool callForAllChildren(O * transform, const F & function) {
    const Transform::TransformIndex numChildren = transform->childrenNum();
    for (Transform::TransformIndex idx = 0; idx < numChildren; ++idx) {
        auto currNode = transform->childAt(idx);
        if (!function(*currNode)) {
            return false;
        }
        if (!callForAllChildren(currNode, function)) {
            return false;
        }
    }
    return true;
}

template<typename O, typename F>
bool iterateUpByHierarchy(O * transform, const F & function) {
    assert(transform);
    if (!function(*transform)) {
        return false;
    }
    if (transform->isRoot()) {
        return true;
    }
    return iterateUpByHierarchy(transform->parent(), function);
}

//-------------------------------------------------------------------------

bool Transform::visitChildren(const std::function<bool(Transform &)> & function) {
    return callForChildren(this, function);
}

bool Transform::visitChildren(const std::function<bool(const Transform &)> & function) const {
    return callForChildren(this, function);
}

//-------------------------------------------------------------------------

bool Transform::visitAllChildren(const std::function<bool(Transform &)> & function) {
    return callForAllChildren(this, function);
}

bool Transform::visitAllChildren(const std::function<bool(const Transform &)> & function) const {
    return callForAllChildren(this, function);
}

//-------------------------------------------------------------------------

bool Transform::iterateDown(const std::function<bool(Transform &)> & function) {
    if (!function(*this)) {
        return false;
    }
    return callForAllChildren(this, function);
}

bool Transform::iterateDown(const std::function<bool(const Transform &)> & function) const {
    if (!function(*this)) {
        return false;
    }
    return callForAllChildren(this, function);
}

bool Transform::iterateUp(const std::function<bool(const Transform &)> & function) const {
    return iterateUpByHierarchy(this, function);
}

bool Transform::iterateUp(const std::function<bool(Transform &)> & function) {
    return iterateUpByHierarchy(this, function);
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void Transform::addObject(ObjAbstract * object) {
    if (object) {
        for (const auto & curr : mObjList) {
            if (curr.get() == object) {
                LWarning << "You try to add an object which already exists.";
                return;
            }
        }

        object->mObjTransform = this;
        mObjList.emplace_back(object);
    }
}

ObjAbstract * Transform::takeObject(const ObjAbstract * object) {
    ObjAbstract * out = nullptr;
    if (object) {
        for (auto it = mObjList.begin(); it != mObjList.end(); ++it) {
            if (it->get() == object) {
                (*it)->mObjTransform = nullptr;
                out = it->release();
                mObjList.erase(it);
                return out;
            }
        }
    }
    return out;
}

bool Transform::removeObject(const ObjAbstract * object) {
    if (object) {
        for (auto it = mObjList.begin(); it != mObjList.end(); ++it) {
            if (it->get() == object) {
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
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<typename O, typename F>
bool callForObjects(O & objects, const F & function) {
    for (auto & o : objects) {
        assert(o);
        if (!function(*o)) {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------

bool Transform::visitObjects(const std::function<bool(ObjAbstract &)> & function) {
    return callForObjects(mObjList, function);
}

bool Transform::visitObjects(const std::function<bool(const ObjAbstract &)> & function) const {
    return callForObjects(mObjList, function);
}

//-------------------------------------------------------------------------

bool Transform::visitAllObjects(const std::function<bool(Transform &, ObjAbstract &)> & function) {
    return iterateDown([&](Transform & tr) {
        return tr.visitObjects([&](ObjAbstract & obj) {
            return function(tr, obj);
        });
    });
}

bool Transform::visitAllObjects(const std::function<bool(const Transform &, const ObjAbstract &)> & function) const {
    return iterateDown([&](const Transform & tr) {
        return tr.visitObjects([&](const ObjAbstract & obj) {
            return function(tr, obj);
        });
    });
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
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

TMatrix Transform::parentMatrix() const {
    const auto p = parent();
    return p ? p->pMatrix : TMatrix();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
