#pragma once

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

#include <functional>
#include <memory>
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
 * \note It takes ownership for all its children and objects.
 */
class Transform {
    friend TreeItem;
public:

    //-------------------------------------------------------------------------
    /// @{

    typedef std::size_t TransformIndex;
    typedef std::vector<std::unique_ptr<ObjAbstract>> ObjList;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Construction/Destruction
    /// @{

    XpObjLib Transform();

    Transform(const Transform &) = delete;
    Transform & operator=(const Transform &) = delete;

    XpObjLib virtual ~Transform();

    /// @}
    //-------------------------------------------------------------------------

    TMatrix pMatrix;
    AnimTransList pAnimTrans;
    AnimRotateList pAnimRotate;
    AnimVisibility pAnimVis;

    //-------------------------------------------------------------------------
    /// \name Naming
    /// @{

    void setName(const std::string & val) {
        mName = val;
    }

    const std::string & name() const {
        return mName;
    }

    /// @}
    //-------------------------------------------------------------------------
    /// \name Tree
    /// @{

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
    XpObjLib TransformIndex childrenNum() const;

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
     * \details Checks whether the transform is 
     *          a child of specified transform's hierarchy.
     * \param transform 
     * \return True or false
     */
    XpObjLib bool isChildOf(const Transform * transform) const;

    /*!
     * \details Creates new children with given name.
     * \param [in] name of children
     * \return Reference to new created children.
     */
    XpObjLib Transform & newChild(const char * name = nullptr);

    /// @}
    //-------------------------------------------------------------------------
    /// \name Children visitors
    /// @{

    /*!
     * \details Calls specified function only for children of this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitChildren(const std::function<bool(Transform &)> & function);

    /*!
     * \details Calls specified function only for children of this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitChildren(const std::function<bool(const Transform &)> & function) const;

    /*!
     * \details Calls specified function for all children in hierarchy 
     *          i.e. iterating full tree where this transform is root.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitAllChildren(const std::function<bool(Transform &)> & function);

    /*!
     * \details Calls specified function for all children in hierarchy
     *          i.e. iterating full tree where this transform is root.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitAllChildren(const std::function<bool(const Transform &)> & function) const;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Iteration
    /// @{

    /*!
     * \details Calls specified function for this transform and 
     *          all its children in hierarchy.
     *          i.e. iterating full tree where this transform is root.
     * \details Unlike \link Transform::visitAllChildren \endlink
     *          it also calls function for this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool iterateDown(const std::function<bool(Transform &)> & function);

    /*!
     * \details Calls specified function for this transform and
     *          all its children in hierarchy.
     *          i.e. iterating full tree where this transform is root.
     * \details Unlike \link Transform::visitAllChildren \endlink
     *          it also calls function for this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool iterateDown(const std::function<bool(const Transform &)> & function) const;

    /*!
     * \details Calls specified function for
     *          this transform and all its parents
     *          according to the hierarchy.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool iterateUp(const std::function<bool(const Transform &)> & function) const;

    /*!
     * \details Calls specified function for
     *          this transform and all its parents
     *          according to the hierarchy.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool iterateUp(const std::function<bool(Transform &)> & function);

    /// @}
    //-------------------------------------------------------------------------
    /// \name Objects
    /// @{

    /*!
     * \details Adds new object.
     * \note Takes ownership of the pointer
     */
    XpObjLib void addObject(ObjAbstract * object);

    /*!
     * \details Removes and destructs object by its pointer.
     * \param [in] object 
     * \return True if object was found and deleted otherwise false.
     */
    XpObjLib bool removeObject(const ObjAbstract * object);

    XpObjLib const ObjList & objList() const;

    bool hasObjects() const {
        return !mObjList.empty();
    }

    /// @}
    //-------------------------------------------------------------------------
    /// \name Object visitors
    /// @{

    /*!
     * \details Calls specified function for each object of this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitObjects(const std::function<bool(ObjAbstract &)> & function);

    /*!
     * \details Calls specified function for each object of this transform.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitObjects(const std::function<bool(const ObjAbstract &)> & function) const;

    /*!
     * \details Calls specified functions for each object in 
     *          the hierarchy including this one.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitAllObjects(const std::function<bool(Transform &, ObjAbstract &)> & function);

    /*!
     * \details Calls specified functions for each object in 
     *          the hierarchy including this one.
     * \param function Return false if you want to stop iterating.
     * \return False if iterating was stopped by function otherwise true.
     */
    XpObjLib bool visitAllObjects(const std::function<bool(const Transform &, const ObjAbstract &)> & function) const;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Animation
    /// @{

    XpObjLib bool hasAnim() const;
    XpObjLib bool hasAnimRotate() const;
    XpObjLib bool hasAnimTrans() const;
    XpObjLib bool hasAnimVis() const;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Matrix
    /// @{

    /*!
     * \return Parent's matrix. If parent isn't set then identity matrix.
     */
    XpObjLib TMatrix parentMatrix() const;

    /// @}
    //-------------------------------------------------------------------------

private:

    TreeItem * mTreePtr;
    std::string mName = "Transform";
    ObjList mObjList;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
