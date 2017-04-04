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

#include <stdint.h>

namespace xobj {

	/*!
	*   \brief Woks with user flags
	*/
	class Flags {

		uint64_t mFlags;

	public:

		/*! Constructor default */
		Flags()
			: mFlags(0) { }

		/*! Constructor init */
		Flags(uint64_t f)
			: mFlags(f) { }

		/*! Constructor copy */
		Flags(const Flags & inFlags)
			: mFlags(inFlags.mFlags) { }

		/*! Operator copy */
		Flags & operator =(const Flags & inFlags) {
			mFlags = inFlags.mFlags;
			return *this;
		}

		/*! Operator copy */
		Flags & operator =(const uint64_t inValue) {
			mFlags = inValue;
			return *this;
		}

		/*! SetFlag
		*   \details Add flag
		*	\param [in] inFlag flag
		*/
		void setFlag(uint64_t inFlag) {
			mFlags |= inFlag;
		}

		/*! ClearFlag
		*   \details Delete specified flag
		*	\param [in] inFlag flag
		*/
		void clearFlag(uint64_t inFlag) {
			mFlags -= (mFlags & inFlag);
		}

		/*! GetFlag
		*   \details Check is there specified flag
		*	\param [in] inFlag flag
		*	\return True if specified flag is exist otherwise false
		*/
		bool getFlag(uint64_t inFlag) const {
			return (mFlags & inFlag) != 0;
		}

		/*! ClearAllFlags
		*   \details Clear any this flags
		*/
		void clearAllFlags() {
			mFlags = 0;
		}

		/*! Check is there any flags set
		*	\details Check is the flagClass has no any flags (0)
		*	\return true if any flags was set otherwise false
		*/
		bool isEmpty() const {
			return (mFlags == 0);
		}

		/*! Check all flag status is they are set
		*   \details Check is the flagClass has all flags (1)
		*	\return true if the class has all flags otherwise false
		*/
		bool isFull() const {
			return (mFlags == 1);
		}

		void orFlags(const Flags & inFlags) {
			mFlags |= inFlags.mFlags;
		}

		void orFlags(const Flags * inFlags) {
			mFlags |= inFlags->mFlags;
		}

		void andFlags(const Flags & inFlags) {
			mFlags &= inFlags.mFlags;
		}

		void andFlags(const Flags * inFlags) {
			mFlags &= inFlags->mFlags;
		}

		bool flagMatch(uint64_t inFmask, uint64_t inFlags) const {
			return ((mFlags & inFmask) == (inFlags & inFmask));
		}

		bool flagMatch(uint64_t inFmask, const Flags & inFlags) const {
			return ((mFlags & inFmask) == (inFlags.mFlags & inFmask));
		}

		bool flagMatch(uint64_t inFmask, const Flags * inFlags) const {
			return ((mFlags & inFmask) == (inFlags->mFlags & inFmask));
		}

		/*! Export Flags
		*	\return The flags
		*/
		uint64_t exportFlags() const {
			return mFlags;
		}

		/*! ImportFlags
		*/
		void importFlags(uint64_t fl) {
			mFlags = fl;
		}

	};
}
