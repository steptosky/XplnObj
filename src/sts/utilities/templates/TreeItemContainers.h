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

#include <vector>
#include <list>

namespace sts_t {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details This class is using as a container for the TreeItem.
	 */
	template<typename TYPE>
	class TreeItemContainerVector : public std::vector<TYPE *> {

		typedef std::vector<TYPE *> Container;

	public:

		//--------------------------------------------

		TYPE * operator[](size_t inIdx) {
			return Container::operator[](inIdx);
		}

		const TYPE * operator[](size_t inIdx) const {
			return Container::operator[](inIdx);
		}

		//--------------------------------------------

		using Container::erase;

		TYPE * erase(size_t inIndex) {
			auto it = Container::begin() + inIndex;
			TYPE * out = (*it);
			Container::erase(it);
			return out;
		}

		//--------------------------------------------

		using Container::insert;

		void insert(size_t inIndex, TYPE * inVal) {
			Container::insert(Container::begin() + inIndex, inVal);
		}

		//--------------------------------------------

		void push_front(TYPE * inVal) {
			Container::insert(Container::begin(), inVal);
		}

		//--------------------------------------------

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details This class is using as a container for the TreeItem.
	 */
	template<typename TYPE>
	class TreeItemContainerList : public std::list<TYPE *> {

		typedef std::list<TYPE *> Container;

	public:

		//--------------------------------------------

		TYPE * operator[](size_t inIdx) {
			auto it = Container::begin();
			for (size_t i = 0; i < inIdx; ++i , ++it);
			return (*it);
		}

		const TYPE * operator[](size_t inIdx) const {
			auto it = Container::begin();
			for (size_t i = 0; i < inIdx; ++i , ++it);
			return (*it);
		}

		//--------------------------------------------

		using Container::erase;

		TYPE * erase(size_t inIndex) {
			auto it = Container::begin();
			for (size_t i = 0; i < inIndex; ++i , ++it);
			TYPE * out = (*it);
			Container::erase(it);
			return out;
		}

		//--------------------------------------------

		using Container::insert;

		void insert(size_t inIndex, TYPE * inVal) {
			auto it = Container::begin();
			for (size_t i = 0; i < inIndex; ++i , ++it);
			Container::insert(it, inVal);
		}

		//--------------------------------------------

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
