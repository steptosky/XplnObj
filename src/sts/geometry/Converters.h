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

#include "templates/Quaternion.h"
#include "templates/TMatrix3.h"
#include "templates/AxisAngle.h"

namespace sts {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
static sts_t::AxisAngle<Type> & fromQuat(sts_t::AxisAngle<Type> & inOutAxisAngle, const sts_t::Quaternion<Type> & inQuat);

//-------------------------------------------------------------------------

template<class Type>
static sts_t::Quaternion<Type> & fromAxisAngle(sts_t::Quaternion<Type> & inOutQuat, const sts_t::AxisAngle<Type> & inAxisAngle);

template<class Type>
static sts_t::Quaternion<Type> & fromAxisAngle(sts_t::Quaternion<Type> & inOutQuat, const sts_t::Vector3<Type> & inAxis, Type inAngle);

template<class Type>
static sts_t::Quaternion<Type> & fromTMatrix3(sts_t::Quaternion<Type> & inOutQuat, const sts_t::TMatrix3<Type> & inMtx);

//-------------------------------------------------------------------------

template<class Type>
static sts_t::TMatrix3<Type> & fromQuat(sts_t::TMatrix3<Type> & inOutMtx, const sts_t::Quaternion<Type> & inQuat);

template<class Type>
static sts_t::TMatrix3<Type> & fromAxisAngle(sts_t::TMatrix3<Type> & inOutMtx, const sts_t::AxisAngle<Type> & inAxisAngle);

template<class Type>
static sts_t::TMatrix3<Type> & fromAxisAngle(sts_t::TMatrix3<Type> & inOutMtx, const sts_t::Vector3<Type> & inAxis, Type inAngle);

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
static sts_t::AxisAngle<Type> toAxisAngle(const sts_t::Quaternion<Type> & inQuat);

//-------------------------------------------------------------------------

template<class Type>
static sts_t::Quaternion<Type> toQuat(const sts_t::AxisAngle<Type> & inAxisAngle);

template<class Type>
static sts_t::Quaternion<Type> toQuat(const sts_t::Vector3<Type> & inAxis, Type inAngle);

template<class Type>
static sts_t::Quaternion<Type> toQuat(const sts_t::TMatrix3<Type> & inMtx);

//-------------------------------------------------------------------------

template<class Type>
static sts_t::TMatrix3<Type> toTMatrix3(const sts_t::Quaternion<Type> & inQuat);

template<class Type>
static sts_t::TMatrix3<Type> toTMatrix3(const sts_t::AxisAngle<Type> & inAxisAngle);

template<class Type>
static sts_t::TMatrix3<Type> toTMatrix3(const sts_t::Vector3<Type> & inAxis, Type inAngle);

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

#include "_inl_/Converters.inl"

}
