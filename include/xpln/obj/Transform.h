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

#include <functional>
#include "xpln/Export.h"
#include "xpln/common/TMatrix.h"
#include "xpln/obj/animation/AnimTrans.h"
#include "xpln/obj/animation/AnimRotate.h"
#include "xpln/obj/animation/AnimVisibility.h"

namespace xobj {

class TreeItem;
class ObjAbstract;

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details A transformation which is tree node. 
 * \note It takes ownership for all its children.
 */
class Transform {
    friend TreeItem;
public:

    XpObjLib Transform();

    Transform(const Transform &) = delete;
    Transform & operator=(const Transform &) = delete;

    XpObjLib virtual ~Transform();

    //-------------------------------------------------------------------------

    TMatrix pMatrix;
    AnimTransList pAnimTrans;
    AnimRotateList pAnimRotate;
    AnimVisibility pAnimVis;

    //-------------------------------------------------------------------------

    typedef std::size_t TransformIndex;
    typedef std::vector<ObjAbstract*> ObjList;

    //-------------------------------------------------------------------------

    /*!
     * \details Checks whether the transform is root.
     * \return True if the transform is root otherwise false
     */
    XpObjLib bool isRoot() const;

    /*!
     * \details Sets the transform parent
     * \remark You can set parent as nullptr then the object will be as a root.
     * \param [in] parent pointer to one new parent
     */
    XpObjLib void setParent(Transform * parent);

    /*!
     * \return root of the transform
     */
    XpObjLib Transform * root();

    /*!
     * \return root of the transform
     */
    XpObjLib const Transform * root() const;

    /*!
     * \return If the tree item has the parent then pointer to it, otherwise nullptr.
     */
    XpObjLib Transform * parent();

    /*!
     * \return If the tree item has the parent then pointer to it, otherwise nullptr.
     */
    XpObjLib const Transform * parent() const;

    /*!
     * \return children number
     */
    XpObjLib TransformIndex childrenCount() const;

    /*!
     * \details Takes children by number
     * \details Remove specified child pointer from the children container and return its pointer.
     * \return Pointer to child
     */
    XpObjLib Transform * takeChildAt(TransformIndex index);

    /*!
     * \details Gets the child by specified index
     * \param [in] index
     * \return Pointer to a child
     */
    XpObjLib Transform * childAt(TransformIndex index);

    /*!
     * \details Gets child at specified index
     * \param [in] index 
     * \return child at specified index
     */
    XpObjLib const Transform * childAt(TransformIndex index) const;

    /*!
     * \details Checks whether the transform is a child of specified parent transform.
     * \param parent 
     * \return True or false
     */
    XpObjLib bool isChildOf(const Transform * parent) const;

    //-------------------------------------------------------------------------

    /*!
     * \warning Also takes ownership of the pointer
     */
    XpObjLib void addObject(ObjAbstract * baseObj);
    XpObjLib bool removeObject(ObjAbstract * baseObj);
    bool hasObjects() const { return !mObjList.empty(); }
    XpObjLib const ObjList & objList() const;

    //-------------------------------------------------------------------------

    XpObjLib bool hasAnim() const;
    XpObjLib bool hasAnimRotate() const;
    XpObjLib bool hasAnimTrans() const;
    XpObjLib bool hasAnimVis() const;

    //-------------------------------------------------------------------------

    XpObjLib void setName(const std::string & val);
    XpObjLib const std::string & name() const;

    //-------------------------------------------------------------------------

    /*!
     * \details It comes up to the root and calculates parity value.
     * \see \link TMatrix::parity \endlink
     */
    XpObjLib bool hierarchicalParity() const;

    /*!
     * \deprecated use \link Transform::hierarchicalParity \endlink
     */
    [[deprecated("use hierarchicalParity()")]]
    XpObjLib bool checkHierarchyForParity() const { return hierarchicalParity(); }

    //-------------------------------------------------------------------------

    TMatrix parentMatrix() const;
    Transform & createChild(const char * inName = nullptr);

    //-------------------------------------------------------------------------

    /*!
     * \details Calls specified function for each object.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function.
     */
    XpObjLib bool visitObjects(const std::function<bool(ObjAbstract &)> & function);

    /*!
     * \details Calls specified function for each object.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function.
     */
    XpObjLib bool visitObjects(const std::function<bool(const ObjAbstract &)> & function) const;

    /*!
     * \details Calls specified function only for children of this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function.
     */
    bool visitChildren(const std::function<bool(Transform &)> & function) { return visitChildren(this, function); }

    /*!
     * \details Calls specified function only for children of this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function.
     */
    bool visitChildren(const std::function<bool(const Transform &)> & function) const {
        return visitChildren(this, function);
    }

    /*!
     * \details Calls specified function for all children in hierarchy 
     *          i.e. iterating full tree where this transform is root.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function.
     */
    bool visitAllChildren(const std::function<bool(Transform &)> & function) { return visitAllOf(this, function); }

    /*!
     * \details Calls specified function for all children in hierarchy
     *          i.e. iterating full tree where this transform is root.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function.
     */
    bool visitAllChildren(const std::function<bool(const Transform &)> & function) const {
        return visitAllOf(this, function);
    }

    //-------------------------------------------------------------------------

private:

    TreeItem * mTreePtr;

    static bool visitAllOf(Transform * parent, const std::function<bool(Transform &)> & function);
    static bool visitAllOf(const Transform * parent, const std::function<bool(const Transform &)> & function);
    static bool visitChildren(Transform * parent, const std::function<bool(Transform &)> & function);
    static bool visitChildren(const Transform * parent, const std::function<bool(const Transform &)> & function);

    static bool hierarchicalParity(const Transform & parent, bool state = false);

    ObjList mObjList;
    std::string mName = "undefined";

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

inline TMatrix Transform::parentMatrix() const {
    const Transform * p = parent();
    return p ? p->pMatrix : TMatrix();
}

inline Transform & Transform::createChild(const char * inName) {
    auto * tr = new Transform;
    tr->setParent(this);
    if (inName) {
        tr->setName(inName);
    }
    return *tr;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
