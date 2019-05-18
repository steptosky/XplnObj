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
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

Transform::~Transform() {
    if (mParent) {
        auto it = std::find_if(mParent->mChildren.begin(), mParent->mChildren.end(),
                               [this](const auto & t) { return t.get() == this; });
        if (it != mParent->mChildren.end()) {
            it->release();
            mParent->mChildren.erase(it);
        }
    }

    for (auto & ch : mChildren) {
        ch->mParent = nullptr;
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

Transform & Transform::newChild(const std::string_view name) {
    const auto & t = mChildren.emplace_back(std::make_unique<Transform>());
    t->mParent = this;
    if (!name.empty()) {
        t->mName = name;
    }
    return *t;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

template<typename O, typename F>
bool callForChildren(O & transform, const F & function) {
    for (auto & child : transform) {
        if (!function(*child)) {
            return false;
        }
    }
    return true;
}

template<typename O, typename F>
bool callForAllChildren(O & transform, const F & function) {
    for (auto & child : transform) {
        if (!function(*child)) {
            return false;
        }
        if (!callForAllChildren(*child, function)) {
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
    return callForChildren(*this, function);
}

bool Transform::visitChildren(const std::function<bool(const Transform &)> & function) const {
    return callForChildren(*this, function);
}

//-------------------------------------------------------------------------

bool Transform::visitAllChildren(const std::function<bool(Transform &)> & function) {
    return callForAllChildren(*this, function);
}

bool Transform::visitAllChildren(const std::function<bool(const Transform &)> & function) const {
    return callForAllChildren(*this, function);
}

//-------------------------------------------------------------------------

bool Transform::iterateDown(const std::function<bool(Transform &)> & function) {
    if (!function(*this)) {
        return false;
    }
    return callForAllChildren(*this, function);
}

bool Transform::iterateDown(const std::function<bool(const Transform &)> & function) const {
    if (!function(*this)) {
        return false;
    }
    return callForAllChildren(*this, function);
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
        mObjList.emplace_back(object);
    }
}

ObjAbstract * Transform::takeObject(const ObjAbstract * object) {
    ObjAbstract * out = nullptr;
    if (object) {
        for (auto it = mObjList.begin(); it != mObjList.end(); ++it) {
            if (it->get() == object) {
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
                mObjList.erase(it);
                return true;
            }
        }
    }
    return false;
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
    for (auto & a : mAnimRotate) {
        if (a.isAnimated()) {
            return true;
        }
    }
    return false;
}

bool Transform::hasAnimTrans() const {
    for (auto & a : mAnimTrans) {
        if (a.isAnimated()) {
            return true;
        }
    }
    return false;
}

bool Transform::hasAnimVis() const {
    return mAnimVis.isAnimated();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

TMatrix Transform::parentMatrix() const {
    const auto p = parent();
    return p ? p->mMatrix : TMatrix();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
