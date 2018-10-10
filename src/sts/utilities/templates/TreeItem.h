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

#include <cstddef>
#include "TreeItemContainers.h"

namespace sts {
namespace tree {

    /********************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************/

    /*!
     * \details Tree Item.
     * \pre
     *      - You can use one of the two predefined containers \link sts::tree::TreeItemContainerVector \endlink and \link sts::tree::TreeItemContainerList \endlink.
     *      - You can specify you own container type, look at \link sts::tree::TreeItemContainerVector \endlink and \link sts::tree::TreeItemContainerList \endlink for example.
     *      - You must not use this class directly.
     *      - The tree item is owner of its children.
     *  When tree item is being destroyed it destroys all its children and remove itself from its parent.
     *      - If you need to use copy constructor and operator you must implement \link TreeItem::clone() \endlink method.
     * \warning You should be careful for working with the copy operator and constructor!<br>
     *          If you don't actually need to use it define one in your derived class in the private level.<br>
     *          <b> It is necessarily! </b><br>
     *          Example:
     * \code
     *      private:
     *      YourType &operator=(const YourType &) = delete;
     *      YourType (const YourType &) = delete;
     * \endcode
     * 
     * \tparam TYPE your type.
     * \tparam CONTAINER container type.
     */
    template<typename TYPE, typename CONTAINER = TreeItemContainerVector<TYPE>>
    class TreeItem {
    protected:

        TreeItem(const TreeItem<TYPE, CONTAINER> & copy);
        TreeItem<TYPE, CONTAINER> & operator =(const TreeItem<TYPE, CONTAINER> & copy);

    public:

        typedef std::size_t Index;    /*!< \details Tree item index. */
        const Index npos = Index(-1); /*!< \details Means no position. */
        typedef CONTAINER Children;

        //---------------------------------------------------------------
        /// @{ 

        TreeItem();
        explicit TreeItem(TreeItem<TYPE, CONTAINER> * inOutParent);
        virtual ~TreeItem();

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual bool isRoot() const;
        virtual TYPE * root();
        virtual const TYPE * root() const;

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual void setParent(TYPE * inOutParent);
        virtual TYPE * parent();
        virtual const TYPE * parent() const;

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual Index childrenCount() const;
        virtual TYPE * childAt(Index index);
        virtual const TYPE * childAt(Index index) const;
        virtual TYPE * takeChildAt(Index index);
        virtual const Children & children() const;

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual TYPE * prependChild(TYPE * inOutItem);
        virtual TYPE * insertChild(Index where, TYPE * inOutItem);
        virtual TYPE * appendChild(TYPE * inOutItem);

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual void deleteChild(Index index);
        virtual bool deleteChild(TYPE * inOutItem);
        virtual void deleteChildren();

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual bool hasChildren() const;
        virtual Index indexOf(const TYPE * item) const;

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual bool isLeaf() const;
        virtual bool isBranch() const;
        virtual bool isChildOf(const TYPE * parent) const;

        /// @}
        //---------------------------------------------------------------
        /// @{

        virtual TYPE * clone() const;

        /// @}
        //---------------------------------------------------------------

    protected:

        Children & children();

    private:

        TYPE * mParent;
        Children mChildren;
        bool mRemoveFromParent;

        void removeFromContainer(Children * inOutContainer, const TreeItem * item);
        void cloneContainer(const Children * container);
        void removeParent();

        static const TreeItem * extractRoot(const TreeItem * item);
        static TreeItem * extractRoot(TreeItem * item);

    };

    /********************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************/
}
}

#include "TreeItem.inl.h"
