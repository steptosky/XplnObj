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

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Constructor copy.
 * \warning This constructor need the TreeItem::clone() to be implemented!
 * The constructor will clone all children of the input tree item with "clone" function.
 */
template<typename TYPE, typename CONTAINER>
TreeItem<TYPE, CONTAINER>::TreeItem(const TreeItem<TYPE, CONTAINER> & tr)
	: mParent(nullptr),
	mRemoveFromParent(true) {
	_clone(&tr.mChildren);
}

/*! \details Constructor default */
template<typename TYPE, typename CONTAINER>
TreeItem<TYPE, CONTAINER>::TreeItem()
	: mParent(nullptr),
	mRemoveFromParent(true) {}

/*!
 * \details Constructor init parent
 * \param[in] inParent
 */
template<typename TYPE, typename CONTAINER>
TreeItem<TYPE, CONTAINER>::TreeItem(TreeItem<TYPE, CONTAINER> * inParent)
	: mParent(nullptr),
	mRemoveFromParent(true) {
	assert(inParent);
	TreeItem::setParent(static_cast<TYPE*>(inParent));
}

/*!
 * \details Destructor
 * \warning The destructor also destroys all this tree item children and deleted this tree item from its parent.
 */
template<typename TYPE, typename CONTAINER>
TreeItem<TYPE, CONTAINER>::~TreeItem() {
	if (mRemoveFromParent)
		TreeItem::setParent(nullptr);
	for (auto & it : mChildren) {
		it->mRemoveFromParent = false;
		delete it;
	}
}

/**************************************************************************************************/
///////////////////////////////////////////* Operators *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Operator copy
 * \warning This operator needs the TreeItem::clone() and Copy constructor to be implemented!
 * \note The operator uses the algorithm which fixes some problem for situation when there is the pointer to this instance in copying hierarchy.
 * \remark Position in the tree hierarchy (parent) will not be changed. \n
 * Operator will delete all exists children of this tree item and copy children from specified tree item with "clone" function.
 */
template<typename TYPE, typename CONTAINER>
TreeItem<TYPE, CONTAINER> & TreeItem<TYPE, CONTAINER>::operator =(const TreeItem<TYPE, CONTAINER> & inCopy) {
	assert(this != &inCopy);
	if (this != &inCopy) {
		TreeItem<TYPE, CONTAINER> tmp(inCopy);
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
 * \details Checks whether the tree item has a parent, No parent means the tree item is root.
 * \return True if the tree item is root otherwise false.
 */
template<typename TYPE, typename CONTAINER>
bool TreeItem<TYPE, CONTAINER>::isRoot() const {
	return (mParent == nullptr);
}

/*!
 * \details Gets the tree hierarchy root (recursive by parent to root).
 * \return Root of the tree hierarchy.
 */
template<typename TYPE, typename CONTAINER>
TYPE * TreeItem<TYPE, CONTAINER>::root() {
	return static_cast<TYPE *>(TreeItem<TYPE, CONTAINER>::_getRootNc(this));
}

/*!
 * \details Gets the tree hierarchy root (recursive by parent to root).
 * \return Root of the tree hierarchy.
 */
template<typename TYPE, typename CONTAINER>
const TYPE * TreeItem<TYPE, CONTAINER>::root() const {
	return static_cast<const TYPE *>(TreeItem<TYPE, CONTAINER>::_getRootC(this));
}

/*!
 * \details Gets constant root
 * \param [in] inCurrentItem Treeitem whose root must be found.
 * \return Constant pointer to the root
 */
template<typename TYPE, typename CONTAINER>
const TreeItem<TYPE, CONTAINER> * TreeItem<TYPE, CONTAINER>::_getRootC(const TreeItem<TYPE, CONTAINER> * inCurrentItem) {
	if (inCurrentItem->isRoot())
		return inCurrentItem;
	return TreeItem<TYPE, CONTAINER>::_getRootC(inCurrentItem->parent());
}

/*!
 * \details Gets root
 * \param [in] inCurrentItem Treeitem whose root must be found.
 * \return Pointer to the root
 */
template<typename TYPE, typename CONTAINER>
TreeItem<TYPE, CONTAINER> * TreeItem<TYPE, CONTAINER>::_getRootNc(TreeItem<TYPE, CONTAINER> * inCurrentItem) {
	if (inCurrentItem->isRoot())
		return inCurrentItem;
	return TreeItem<TYPE, CONTAINER>::_getRootNc(inCurrentItem->parent());
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Sets the tree item parent.
 * \remark You can set parent as the nullptr then the tree item will be as the root.
 * \param [in] inParent pointer to new parent.
 */
template<typename TYPE, typename CONTAINER>
void TreeItem<TYPE, CONTAINER>::setParent(TYPE * inParent) {
	if (mParent == inParent)
		return;
	if (inParent == nullptr)
		_removeParent();
	else
		inParent->appendChild(static_cast<TYPE*>(this));
}

/*!
 * \details Gets the tree item parent.
 * \return If the tree item has the parent then pointer to it, otherwise nullptr.
 */
template<typename TYPE, typename CONTAINER>
TYPE * TreeItem<TYPE, CONTAINER>::parent() {
	return mParent;
}

/*!
 * \details Gets the tree item parent.
 * \return If the tree item has the parent then pointer to it, otherwise nullptr.
 */
template<typename TYPE, typename CONTAINER>
const TYPE * TreeItem<TYPE, CONTAINER>::parent() const {
	return mParent;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Gets the tree item children count.
 * \return children count.
 */
template<typename TYPE, typename CONTAINER>
size_t TreeItem<TYPE, CONTAINER>::childrenCount() const {
	return mChildren.size();
}

/*!
 * \details Gets the pointer to the child of the tree item by given index.
 * \param [in] inIndex
 * \return Pointer to the child.
 */
template<typename TYPE, typename CONTAINER>
TYPE * TreeItem<TYPE, CONTAINER>::childAt(Index inIndex) {
	assert(inIndex < mChildren.size());
	return mChildren[inIndex];
}

/*!
 * \details Gets the pointer to the child of the tree item by given index.
 * \param [in] inIndex
 * \return Pointer to the child.
 */
template<typename TYPE, typename CONTAINER>
const TYPE * TreeItem<TYPE, CONTAINER>::childAt(Index inIndex) const {
	assert(inIndex < mChildren.size());
	return mChildren[inIndex];
}

/*!
 * \details Gets the pointer to the child of the tree item by given index and removes it from the children list.
 * The tree item will not be owner of the returned child, so don't forget to delete it.
 * \param [in] inIndex child index that must be removed from the children list and returned.
 * \return TreeItem that will be removed from the children list.
 */
template<typename TYPE, typename CONTAINER>
TYPE * TreeItem<TYPE, CONTAINER>::takeChildAt(Index inIndex) {
	assert(inIndex < mChildren.size());
	TYPE * t = mChildren.erase(inIndex);
	t->mParent = nullptr;
	return t;
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
 * \remark The treeitem takes ownership of the specified pointer.
 * \param [in] inTreeItem tree item that will be added as a child.
 * \return Pointer to the inTreeItem (which is the input parameter).
 */
template<typename TYPE, typename CONTAINER>
TYPE * TreeItem<TYPE, CONTAINER>::prependChild(TYPE * inTreeItem) {
	assert(inTreeItem);
	assert(inTreeItem->parent() != this);
	inTreeItem->_removeParent();
	inTreeItem->mParent = static_cast<TYPE*>(this);
	mChildren.push_front(inTreeItem);
	return inTreeItem;
}

/*!
 * \details Inserts child by the index.
 * \remark The treeitem takes ownership of the specified pointer.
 * \param [in] inWhere index where new child must be inserted.
 * \param [in] inTreeItem tree item that will be inserted as a child.
 * \return Pointer to the inTreeItem (which is the input parameter).
 */
template<typename TYPE, typename CONTAINER>
TYPE * TreeItem<TYPE, CONTAINER>::insertChild(Index inWhere, TYPE * inTreeItem) {
	assert(inTreeItem);
	assert(inWhere <= mChildren.size());
	assert(inTreeItem->parent() != this);
	inTreeItem->_removeParent();
	inTreeItem->mParent = static_cast<TYPE*>(this);
	mChildren.insert(inWhere, inTreeItem);
	return inTreeItem;
}

/*!
 * \details Adds a child to the and of the children list.
 * \remark The treeitem takes ownership of the specified pointer.
 * \param [in] inTreeItem tree item that will be added as a child.
 * \return Pointer to the inTreeItem (which is the input parameter).
 */
template<typename TYPE, typename CONTAINER>
TYPE * TreeItem<TYPE, CONTAINER>::appendChild(TYPE * inTreeItem) {
	assert(inTreeItem);
	assert(inTreeItem->parent() != this);
	inTreeItem->_removeParent();
	inTreeItem->mParent = static_cast<TYPE*>(this);
	mChildren.push_back(inTreeItem);
	return inTreeItem;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Deletes one of the children of this tree item with delete operator and removes it from the children list.
 * \param [in] inIndex index of a child which must be deleted.
 */
template<typename TYPE, typename CONTAINER>
void TreeItem<TYPE, CONTAINER>::deleteChild(Index inIndex) {
	assert(inIndex < mChildren.size());
	TYPE * val = mChildren.erase(inIndex);
	val->mRemoveFromParent = false;
	delete val;
}

/*!
 * \details Deletes <b>ALL</b> children from this item.
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
 * \details Deletes one of the children of this tree item with delete operator and removes it from the children list.
 * \param [in] inPtr pointer to a children which must be deleted.
 * \return True if the data by the specified point was deleted otherwise false.
 */
template<typename TYPE, typename CONTAINER>
bool TreeItem<TYPE, CONTAINER>::deleteChild(TYPE * inPtr) {
	assert(inPtr);
	size_t index = indexOf(inPtr);
	if (index == npos)
		return false;
	deleteChild(index);
	return true;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

/*!
 * \details Checks whther this item has children.
 * \return True if the item has the children, otherwise false.
 */
template<typename TYPE, typename CONTAINER>
bool TreeItem<TYPE, CONTAINER>::hasChildren() const {
	return !mChildren.empty();
}

/*!
 * \details Searches a tree item index by its pointer.
 * \param [in] inTreeItem pointer to tree item whose index must be found.
 * \return Index if specified pointer that was found otherwise TreeItem->npos (TreeItem::Index(-1)).
 */
template<typename TYPE, typename CONTAINER>
size_t TreeItem<TYPE, CONTAINER>::indexOf(const TYPE * inTreeItem) const {
	assert(inTreeItem);
	Index outIndex = 0;
	for (auto & it : mChildren) {
		if (it == inTreeItem)
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
 * \details If the item doesn't have any children then the item is the leaf.
 * \return True if the item is leaf otherwise false.
 */
template<typename TYPE, typename CONTAINER>
bool TreeItem<TYPE, CONTAINER>::isLeaf() const {
	return mChildren.empty();
}

/*!
 * \details Checks whether the item is either branch or leaf.
 * \details If the item has some children then the item is the branch.
 * \return True if the item is branch otherwise false.
 */
template<typename TYPE, typename CONTAINER>
bool TreeItem<TYPE, CONTAINER>::isBranch() const {
	return !mChildren.empty();
}

/*!
 * \details Check whether this item is one of the children of specified parent.
 * \note This method checks full chain till the root.
 * \param inParent a parent that you want to be checked.
 * \return True if this item has specified item as parent otherwise false.
 */
template<typename TYPE, typename CONTAINER>
bool TreeItem<TYPE, CONTAINER>::isChildOf(const TYPE * inParent) const {
	if (!mParent) {
		return false;
	}
	if (mParent == inParent) {
		return true;
	}
	return mParent->isChildOf(inParent);
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
 * \details Removes this parent;
 */
template<typename TYPE, typename CONTAINER>
void TreeItem<TYPE, CONTAINER>::_removeParent() {
	if (mParent != nullptr) {
		assert(mParent->indexOf(static_cast<TYPE*>(this)) != npos);
		_remove(&mParent->mChildren, this);
		mParent = nullptr;
	}
}

/*!
 * \details Clones new children from specified list
 * \param [in] inList
 */
template<typename TYPE, typename CONTAINER>
void TreeItem<TYPE, CONTAINER>::_clone(const Children * inList) {
	assert(inList);
	for (auto it = inList->begin(); it != inList->end(); ++it)
		appendChild((*it)->clone());
}

/*!
 * \details Finds and removes particular child without call the delete operator.
 * \param [in, out] inOutList
 * \param [in, out] inPtr
 */
template<typename TYPE, typename CONTAINER>
void TreeItem<TYPE, CONTAINER>::_remove(Children * inOutList, TreeItem<TYPE, CONTAINER> * inPtr) {
	assert(inOutList);
	assert(inPtr);
	for (auto it = inOutList->begin(); it != inOutList->end(); ++it) {
		if (*it == inPtr) {
			inOutList->erase(it);
			return;
		}
	}
}

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/
