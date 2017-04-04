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

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

#include <limits>
#include "Vector3.h"
#include "../DrConverters.h"

namespace sts_t {

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

	/*!
	 * \details This class provides a representation for orientation in three space using an angle and axis.
	 * This class is similar to a quaternion, except that a normalized quaternion only represents -PI to +PI rotation.
	 * This class will have the number of revolutions stored.
	 */
	template<class T>
	class AxisAngle {
		static_assert(std::numeric_limits<T>::is_iec559,
			"The class can use only floating types");

		typedef Vector3<T> Vec3;
		T mData[4];

	public:

		typedef T Type;
		typedef Type value_type;

		//-------------------------------------------------------------------------

		AxisAngle();
		AxisAngle(Type inX, Type inY, Type inZ, Type inAngleRad);
		AxisAngle(const Vec3 & inVec, Type inAngleRad);
		~AxisAngle();

		//-------------------------------------------------------------------------

		bool operator !=(const AxisAngle & inRight) const;
		bool operator ==(const AxisAngle & inRight) const;

		const Type & operator[](size_t i) const;
		Type & operator[](size_t i);

		//-------------------------------------------------------------------------

		void setX(const Type inX);
		void setY(const Type inY);
		void setZ(const Type inZ);
		void setW(const Type inW);

		Type x() const;
		Type y() const;
		Type z() const;
		Type w() const;

		//-------------------------------------------------------------------------

		void set(Type inX, Type inY, Type inZ, Type inAngleRad);
		void set(const Vec3 & inVec, Type inAngleRad);
		void setVector(const Vec3 & inVec);
		void setAngle(Type inAngleRad);
		double angle() const;
		const Vec3 & vector() const;
		Vec3 & vector();
		void clear();

		//-------------------------------------------------------------------------

		int numRevs() const;
		void addRevs(int inNum);

		//-------------------------------------------------------------------------

		std::string toString(const std::string & inFormat = "%x %y %z %ad", uint8_t precision = 6); // d- degrees r- radians

		//-------------------------------------------------------------------------

	};

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

#include "AxisAngle.inl"

}
