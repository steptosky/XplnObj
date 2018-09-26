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

#include <cassert>

namespace sts {
namespace tree {

    /**************************************************************************************************/
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Constructor copy.
     * \warning This constructor needs the \link TreeItem::clone \endlink to be implemented!
     *          The constructor will clone all children of the input tree item 
     *          with the \link TreeItem::clone \endlink method.
     */
    template<typename TYPE, typename CONTAINER>
    TreeItem<TYPE, CONTAINER>::TreeItem(const TreeItem<TYPE, CONTAINER> & copy)
        : mParent(nullptr),
          mRemoveFromParent(true) {
        cloneContainer(&copy.mChildren);
    }

    /*! \details Constructor default */
    template<typename TYPE, typename CONTAINER>
    TreeItem<TYPE, CONTAINER>::TreeItem()
        : mParent(nullptr),
          mRemoveFromParent(true) {}

    /*!
     * \details Constructor init parent.
     * \param[in, out] inOutParent
     */
    template<typename TYPE, typename CONTAINER>
    TreeItem<TYPE, CONTAINER>::TreeItem(TreeItem<TYPE, CONTAINER> * inOutParent)
        : mParent(nullptr),
          mRemoveFromParent(true) {
        assert(inOutParent);
        TreeItem::setParent(static_cast<TYPE*>(inOutParent));
    }

    /*!
     * \details Destructor
     * \warning The destructor destroys all the item's children and removes this item from its parent.
     */
    template<typename TYPE, typename CONTAINER>
    TreeItem<TYPE, CONTAINER>::~TreeItem() {
        if (mRemoveFromParent) {
            TreeItem::setParent(nullptr);
        }
        for (auto & it : mChildren) {
            it->mRemoveFromParent = false;
            delete it;
        }
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Operators *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Operator copy.
     * \warning This operator needs the \link TreeItem::clone \endlink and copy constructor to be implemented!
     * \note The operator uses the algorithm which fixes some problem for situation when there is the pointer to this instance in copying hierarchy.
     * \remark Position in the tree hierarchy (parent) will not be changed.<br>
     *         Operator will delete all existing item's children and
     *         copy children from specified item with the \link TreeItem::clone \endlink method.
     */
    template<typename TYPE, typename CONTAINER>
    TreeItem<TYPE, CONTAINER> & TreeItem<TYPE, CONTAINER>::operator =(const TreeItem<TYPE, CONTAINER> & copy) {
        assert(this != &copy);
        if (this != &copy) {
            TreeItem<TYPE, CONTAINER> tmp(copy);
            deleteChildren();
            for (auto & it : tmp.mChildren) {
                it->mParent = static_cast<TYPE*>(this);
                mChildren.push_back(it);
            }
            tmp.mChildren.clear(); // tmp can't delete clones now
        }
        return *this;
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Checks whether the item has a parent. No parent means the item is root.
     * \return True if the item is root otherwise false.
     */
    template<typename TYPE, typename CONTAINER>
    bool TreeItem<TYPE, CONTAINER>::isRoot() const {
        return (mParent == nullptr);
    }

    /*!
     * \details Gets the tree hierarchy root (recursive by parents up to the root).
     * \return Root of the tree hierarchy.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::root() {
        return static_cast<TYPE *>(TreeItem<TYPE, CONTAINER>::extractRoot(this));
    }

    /*!
     * \details Gets the tree hierarchy root (recursive by parents up to the root).
     * \return Root of the tree hierarchy.
     */
    template<typename TYPE, typename CONTAINER>
    const TYPE * TreeItem<TYPE, CONTAINER>::root() const {
        return static_cast<const TYPE *>(TreeItem<TYPE, CONTAINER>::extractRoot(this));
    }

    /*!
     * \details Gets constant root.
     * \param [in] item Tree item whose root must be found.
     * \return Constant pointer to the root.
     */
    template<typename TYPE, typename CONTAINER>
    const TreeItem<TYPE, CONTAINER> * TreeItem<TYPE, CONTAINER>::extractRoot(const TreeItem<TYPE, CONTAINER> * item) {
        if (item->isRoot()) {
            return item;
        }
        return TreeItem<TYPE, CONTAINER>::extractRoot(item->parent());
    }

    /*!
     * \details Gets root.
     * \param [in] item Tree item whose root must be found.
     * \return Pointer to the root.
     */
    template<typename TYPE, typename CONTAINER>
    TreeItem<TYPE, CONTAINER> * TreeItem<TYPE, CONTAINER>::extractRoot(TreeItem<TYPE, CONTAINER> * item) {
        if (item->isRoot()) {
            return item;
        }
        return TreeItem<TYPE, CONTAINER>::extractRoot(item->parent());
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Sets the item's parent.
     * \remark You can set parent as the nullptr then the item will be as a root.
     * \param [in, out] inOutParent pointer to new parent.
     */
    template<typename TYPE, typename CONTAINER>
    void TreeItem<TYPE, CONTAINER>::setParent(TYPE * inOutParent) {
        if (mParent == inOutParent) {
            return;
        }
        if (inOutParent == nullptr) {
            removeParent();
        }
        else {
            inOutParent->appendChild(static_cast<TYPE*>(this));
        }
    }

    /*!
     * \details Gets the item's parent.
     * \return If the item has the parent then pointer to it otherwise nullptr.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::parent() {
        return mParent;
    }

    /*!
     * \details Gets the item's parent.
     * \return Pointer to item's parent or nullptr if the parent isn't set.
     */
    template<typename TYPE, typename CONTAINER>
    const TYPE * TreeItem<TYPE, CONTAINER>::parent() const {
        return mParent;
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Gets the item children's count.
     * \return Children's count.
     */
    template<typename TYPE, typename CONTAINER>
    size_t TreeItem<TYPE, CONTAINER>::childrenCount() const {
        return mChildren.size();
    }

    /*!
     * \details Gets the the child by its index.
     * \param [in] index
     * \return Pointer to the child.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::childAt(const Index index) {
        assert(index < mChildren.size());
        return mChildren[index];
    }

    /*!
     * \details Gets the the child by its index.
     * \param [in] index
     * \return Pointer to the child.
     */
    template<typename TYPE, typename CONTAINER>
    const TYPE * TreeItem<TYPE, CONTAINER>::childAt(const Index index) const {
        assert(index < mChildren.size());
        return mChildren[index];
    }

    /*!
     * \details Takes the the child by its index and removes it from the children list.
     *          The item will not be child's owner anymore, so don't forget to delete it yourself.
     * \param [in] index child index that must be removed from the children list and returned.
     * \return Item that is removed from the children list.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::takeChildAt(const Index index) {
        assert(index < mChildren.size());
        auto item = mChildren[index];
        mChildren.erase(index);
        item->mParent = nullptr;
        return item;
    }

    /*!
     * \details Access to the constant children list.
     * \return Reference to the children list.
     */
    template<typename TYPE, typename CONTAINER>
    const CONTAINER & TreeItem<TYPE, CONTAINER>::children() const {
        return mChildren;
    }

    /*!
     * \details Access to the children list.
     * \warning Be careful when you change this data manually.
     *          You must understand what you do.
     * \return Reference to the children list.
     */
    template<typename TYPE, typename CONTAINER>
    CONTAINER & TreeItem<TYPE, CONTAINER>::children() {
        return mChildren;
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Adds a child to the start of the children list.
     * \remark The item takes ownership of the specified pointer.
     * \param [in, out] inOutItem tree item that will be added as a child.
     * \return Pointer to the item which is the input parameter.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::prependChild(TYPE * inOutItem) {
        assert(inOutItem);
        assert(inOutItem->parent() != this);
        inOutItem->removeParent();
        inOutItem->mParent = static_cast<TYPE*>(this);
        mChildren.push_front(inOutItem);
        return inOutItem;
    }

    /*!
     * \details Inserts child by index.
     * \remark The Tree item takes ownership of the specified pointer.
     * \param [in] where index where new child must be inserted.
     * \param [in, out] inOutItem tree item that will be inserted as a child.
     * \return Pointer to the item which is the input parameter.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::insertChild(const Index where, TYPE * inOutItem) {
        assert(inOutItem);
        assert(where <= mChildren.size());
        assert(inOutItem->parent() != this);
        inOutItem->removeParent();
        inOutItem->mParent = static_cast<TYPE*>(this);
        mChildren.insert(where, inOutItem);
        return inOutItem;
    }

    /*!
     * \details Adds a child to the and of the children list.
     * \remark The Tree item takes ownership of the specified pointer.
     * \param [in, out] inOutItem tree item that will be added as a child.
     * \return Pointer to the item which is the input parameter.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::appendChild(TYPE * inOutItem) {
        assert(inOutItem);
        assert(inOutItem->parent() != this);
        inOutItem->removeParent();
        inOutItem->mParent = static_cast<TYPE*>(this);
        mChildren.push_back(inOutItem);
        return inOutItem;
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Removes child from item's children list by child's index. 
     *          The child's destructor will be called while removing.
     * \param [in] index index of a child that must be deleted.
     */
    template<typename TYPE, typename CONTAINER>
    void TreeItem<TYPE, CONTAINER>::deleteChild(const Index index) {
        assert(index < mChildren.size());
        auto item = mChildren[index];
        mChildren.erase(index);
        item->mRemoveFromParent = false;
        delete item;
    }

    /*!
     * \details Deletes <b>ALL</b> item's children.
     */
    template<typename TYPE, typename CONTAINER>
    void TreeItem<TYPE, CONTAINER>::deleteChildren() {
        for (auto & it : mChildren) {
            it->mRemoveFromParent = false;
            delete it;
        }
        mChildren.clear();
    }

    /*!
     * \details Removes child from item's children list by child's pointer.
     *          The child's destructor will be called while removing.
     * \param [in, out] inOutItem pointer to a children that must be deleted.
     * \return True if the child by the specified pointer was deleted otherwise false.
     */
    template<typename TYPE, typename CONTAINER>
    bool TreeItem<TYPE, CONTAINER>::deleteChild(TYPE * inOutItem) {
        assert(inOutItem);
        const std::size_t index = indexOf(inOutItem);
        if (index == npos) {
            return false;
        }
        deleteChild(index);
        return true;
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Checks whether the item has children.
     * \return True if the item has children otherwise false.
     */
    template<typename TYPE, typename CONTAINER>
    bool TreeItem<TYPE, CONTAINER>::hasChildren() const {
        return !mChildren.empty();
    }

    /*!
     * \details Searches an item index by its pointer.
     * \param [in] item pointer to tree item whose index must be found.
     * \return Index if specified pointer that was found otherwise \link TreeItem::npos \endlink.
     */
    template<typename TYPE, typename CONTAINER>
    size_t TreeItem<TYPE, CONTAINER>::indexOf(const TYPE * item) const {
        assert(item);
        Index outIndex = 0;
        for (auto & it : mChildren) {
            if (it == item)
                return outIndex;
            ++outIndex;
        }
        return npos;
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Checks whether the item is either branch or leaf.
     * \details If the item doesn't have any children then the item is leaf.
     * \return True if the item is leaf otherwise false.
     */
    template<typename TYPE, typename CONTAINER>
    bool TreeItem<TYPE, CONTAINER>::isLeaf() const {
        return mChildren.empty();
    }

    /*!
     * \details Checks whether the item is either branch or leaf.
     * \details If the item has some children then the item is branch.
     * \return True if the item is branch otherwise false.
     */
    template<typename TYPE, typename CONTAINER>
    bool TreeItem<TYPE, CONTAINER>::isBranch() const {
        return !mChildren.empty();
    }

    /*!
     * \details Check whether this item is one of the children of specified parent.
     * \note This method checks full hierarchy chain up to the root.
     * \param [in] parent a parent that you want to be checked.
     * \return True if this item has specified item as a parent otherwise false.
     */
    template<typename TYPE, typename CONTAINER>
    bool TreeItem<TYPE, CONTAINER>::isChildOf(const TYPE * parent) const {
        if (!mParent) {
            return false;
        }
        if (mParent == parent) {
            return true;
        }
        return mParent->isChildOf(parent);
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Clones the tree item.
     * \details default implementation is \code return nullptr; \endcode
     * \return Pointer to a cloned tree item.
     */
    template<typename TYPE, typename CONTAINER>
    TYPE * TreeItem<TYPE, CONTAINER>::clone() const {
        return nullptr;
    }

    /**************************************************************************************************/
    ///////////////////////////////////////////* Functions *////////////////////////////////////////////
    /**************************************************************************************************/

    /*!
     * \details Removes item's parent.
     */
    template<typename TYPE, typename CONTAINER>
    void TreeItem<TYPE, CONTAINER>::removeParent() {
        if (mParent != nullptr) {
            assert(mParent->indexOf(static_cast<TYPE*>(this)) != npos);
            removeFromContainer(&mParent->mChildren, this);
            mParent = nullptr;
        }
    }

    /*!
     * \details Clones new children from specified list
     * \param [in] container
     */
    template<typename TYPE, typename CONTAINER>
    void TreeItem<TYPE, CONTAINER>::cloneContainer(const Children * container) {
        assert(container);
        for (auto & item : *container) {
            appendChild(item->clone());
        }
    }

    /*!
     * \details Finds and removes certain child from container without destruction.
     * \param [in, out] inOutContainer
     * \param [in] item
     */
    template<typename TYPE, typename CONTAINER>
    void TreeItem<TYPE, CONTAINER>::removeFromContainer(Children * inOutContainer, const TreeItem<TYPE, CONTAINER> * item) {
        assert(inOutContainer);
        assert(item);
        for (auto it = inOutContainer->begin(); it != inOutContainer->end(); ++it) {
            if (*it == item) {
                inOutContainer->erase(it);
                return;
            }
        }
    }

    /********************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************/
}
}
