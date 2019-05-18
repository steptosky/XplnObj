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
#include <vector>
#include <memory>
#include "xpln/Export.h"
#include "xpln/common/TMatrix.h"
#include "xpln/obj/ObjAbstract.h"
#include "xpln/obj/animation/AnimTrans.h"
#include "xpln/obj/animation/AnimRotate.h"
#include "xpln/obj/animation/AnimVisibility.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details A transformation which is tree node. 
 * \note It takes ownership for all its children and objects.
 */
class Transform {
public:

    //-------------------------------------------------------------------------
    /// @{

    typedef std::vector<std::unique_ptr<ObjAbstract>> ObjList;
    typedef std::vector<std::unique_ptr<Transform>> Children;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Construction/Destruction
    /// @{

    Transform() = default;

    Transform(const Transform &) = delete;
    Transform & operator=(const Transform &) = delete;

    XpObjLib virtual ~Transform();

    /// @}
    //-------------------------------------------------------------------------

    std::string mName = "transform";
    TMatrix mMatrix;
    AnimTransList mAnimTrans;
    AnimRotateList mAnimRotate;
    AnimVisibility mAnimVis;

    /// @}
    //-------------------------------------------------------------------------
    /// \name Tree
    /// @{

    /*!
     * \details Checks whether the transform is root.
     * \return True if the transform is root otherwise false
     */
    bool isRoot() const { return !mParent; }

    /*!
     * \return If the tree item has the parent then pointer to it, otherwise nullptr.
     */
    Transform * parent() { return mParent; }

    /*!
     * \return If the tree item has the parent then pointer to it, otherwise nullptr.
     */
    const Transform * parent() const { return mParent; }

    /*!
     * \details Creates new children with given name.
     * \param [in] name of children
     * \return Reference to new created children.
     */
    XpObjLib Transform & newChild(std::string_view name = std::string_view());

    /*!
     * \todo remove when it is not needed anymore
     */
    bool hasChildren() const { return !mChildren.empty(); }

    /*!
     * \todo remove when it is not needed anymore
     */
    std::size_t childrenNum() const { return mChildren.size(); }

    Children::iterator begin() { return mChildren.begin(); }
    Children::iterator end() { return mChildren.end(); }
    Children::const_iterator begin() const { return mChildren.begin(); }
    Children::const_iterator end() const { return mChildren.end(); }

    /*!
     * \return Parent's matrix. If parent isn't set then identity matrix.
     */
    XpObjLib TMatrix parentMatrix() const;

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

    XpObjLib ObjAbstract * takeObject(const ObjAbstract * object);

    const ObjList & objList() const { return mObjList; }
    bool hasObjects() const { return !mObjList.empty(); }

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

private:

    Transform * mParent = nullptr;
    ObjList mObjList;
    Children mChildren;

};

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
