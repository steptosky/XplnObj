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

#include <cstring>
#include <cassert>

#include "TreeItemContainers.h"

namespace sts_t {

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

/*!
 * \details Tree Item.
 * \pre
 * - You can use one of the two predefined containers \link sts_t::TreeItemContainerVector \endlink and \link sts_t::TreeItemContainerList \endlink.
 * - You can specify you own container type, look at \link sts_t::TreeItemContainerVector \endlink and \link sts_t::TreeItemContainerList \endlink for example.
 * - You must not use this class directly.
 * - The tree item is owner of its children.
 * When the tree item will be destroyed then it will destroy all its children, also if the item is having a parent then will be deleted from it.
 * - If you need to use copy constructor and operator then you must implement \link TreeItem::clone() \endlink method.
 * \warning You should be careful for working with the copy operator and constructor!
 * If you don't need use it, define it in an inherited class by private level. \n
 * <b> It is necessarily! </b>\n Example:
 * \code
 * private:
 * YourType &operator=(const YourType &) = delete;
 * YourType (const YourType &) = delete;
 * \endcode
 */
template<typename TYPE, typename CONTAINER = TreeItemContainerVector<TYPE>>
class TreeItem {
protected:

    TreeItem(const TreeItem<TYPE, CONTAINER> & tr);
    TreeItem<TYPE, CONTAINER> & operator =(const TreeItem<TYPE, CONTAINER> & tr);

public:

    typedef size_t Index;         /*!< \details Tree item index. */
    const Index npos = Index(-1); /*!< \details Means no position. */
    typedef CONTAINER Children;

    //--------------------------------------------------

    TreeItem();
    explicit TreeItem(TreeItem<TYPE, CONTAINER> * inParent);
    virtual ~TreeItem();

    //--------------------------------------------------

    virtual bool isRoot() const;
    virtual TYPE * root();
    virtual const TYPE * root() const;

    virtual void setParent(TYPE * inParent);
    virtual TYPE * parent();
    virtual const TYPE * parent() const;

    virtual Index childrenCount() const;
    virtual TYPE * childAt(Index inIndex);
    virtual const TYPE * childAt(Index inIndex) const;
    virtual TYPE * takeChildAt(Index inIndex);
    virtual const Children & children() const;

    virtual TYPE * prependChild(TYPE * inTreeItem);
    virtual TYPE * insertChild(Index inWhere, TYPE * inTreeItem);
    virtual TYPE * appendChild(TYPE * inTreeItem);

    virtual void deleteChild(Index inIndex);
    virtual bool deleteChild(TYPE * inPtr);
    virtual void deleteChildren();

    virtual bool hasChildren() const;
    virtual Index indexOf(const TYPE * inTreeItem) const;

    virtual bool isLeaf() const;
    virtual bool isBranch() const;
    virtual bool isChildOf(const TYPE * inParent) const;

    virtual TYPE * clone() const;

    //--------------------------------------------------

protected:

    Children & children();

private:

    TYPE * mParent;
    Children mChildren;
    bool mRemoveFromParent;

    void _remove(Children * inList, TreeItem * inPtr);
    void _clone(const Children * inList);
    void _removeParent();

    static const TreeItem * _getRootC(const TreeItem * inCurrentItem);
    static TreeItem * _getRootNc(TreeItem * inCurrentItem);

};

/********************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************************/

#include "TreeItem.inl"

}
