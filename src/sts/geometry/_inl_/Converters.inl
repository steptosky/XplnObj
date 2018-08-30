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
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
sts_t::AxisAngle<Type> & fromQuat(sts_t::AxisAngle<Type> & inOutAxisAngle, const sts_t::Quaternion<Type> & inQuat) {
    Type factor = inQuat[0] * inQuat[0] + inQuat[1] * inQuat[1] + inQuat[2] * inQuat[2];
    if (factor > Type(0)) {
        factor = Type(1) / Type(sqrt(factor));
        inOutAxisAngle.set(
                           inQuat[0] * factor,
                           inQuat[1] * factor,
                           inQuat[2] * factor,
                           Type(2) * acos(inQuat[3])
                          );
        return inOutAxisAngle;
    }
    inOutAxisAngle.set(Type(0), Type(0), Type(0), Type(0));
    return inOutAxisAngle;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
sts_t::Quaternion<Type> & fromTMatrix3(sts_t::Quaternion<Type> & inOutQuat, const sts_t::TMatrix3<Type> & inMtx) {
    if (!inMtx.isRotating()) {
        inOutQuat.identity();
        return inOutQuat;
    }

    const int next[3] = {1, 2, 0};
    Type trace = inMtx(0, 0) + inMtx(1, 1) + inMtx(2, 2);
    Type root = Type(1);

    if (trace > Type(0)) {
        // |w| > 1/2, may as well choose w > 1/2
        root = Type(sqrt(trace + Type(1))); // 2w
        inOutQuat[3] = Type(0.5) * root;
        root = Type(0.5) / root; // 1/(4w)
        inOutQuat[0] = (inMtx(2, 1) - inMtx(1, 2)) * root;
        inOutQuat[1] = (inMtx(0, 2) - inMtx(2, 0)) * root;
        inOutQuat[2] = (inMtx(1, 0) - inMtx(0, 1)) * root;
    }
    else {
        // |w| <= 1/2
        int i = 0;
        if (inMtx(1, 1) > inMtx(0, 0)) {
            i = 1;
        }
        if (inMtx(2, 2) > inMtx(i, i)) {
            i = 2;
        }
        int j = next[i];
        int k = next[j];

        root = Type(sqrt(inMtx(i, i) - inMtx(j, j) - inMtx(k, k) + Type(1)));
        Type * quat[3] = {&inOutQuat[0], &inOutQuat[1], &inOutQuat[2]};
        *quat[i] = Type(0.5) * root;
        root = Type(0.5) / root;
        inOutQuat[3] = (inMtx(k, j) - inMtx(j, k)) * root;
        *quat[j] = (inMtx(j, i) + inMtx(i, j)) * root;
        *quat[k] = (inMtx(k, i) + inMtx(i, k)) * root;
    }
    return inOutQuat;
}

template<class Type>
sts_t::Quaternion<Type> & fromAxisAngle(sts_t::Quaternion<Type> & inOutQuat, const sts_t::Vector3<Type> & inAxis, Type inAngle) {
    Type halfAngle = Type(0.5) * inAngle;
    Type sn = sin(halfAngle);
    inOutQuat[0] = sn * inAxis.x;
    inOutQuat[1] = sn * inAxis.y;
    inOutQuat[2] = sn * inAxis.z;
    inOutQuat[3] = cos(halfAngle);
    return inOutQuat;
}

template<class Type>
sts_t::Quaternion<Type> & fromAxisAngle(sts_t::Quaternion<Type> & inOutQuat, const sts_t::AxisAngle<Type> & inAxisAngle) {
    return fromAxisAngle<Type>(inOutQuat, inAxisAngle.vector(), inAxisAngle.angle());
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
sts_t::TMatrix3<Type> & fromAxisAngle(sts_t::TMatrix3<Type> & inOutMtx, const sts_t::Vector3<Type> & inAxis, Type inAngle) {
    if (sts::isEqual(inAngle, Type(0)) || inAxis.isNull()) {
        inOutMtx.setRotateIdentity();
        return inOutMtx;
    }

    Type cs = cos(inAngle);
    Type sn = sin(inAngle);
    Type oneMinusCos = Type(1) - cs;
    Type x2 = inAxis.x * inAxis.x;
    Type y2 = inAxis.y * inAxis.y;
    Type z2 = inAxis.z * inAxis.z;
    Type xym = inAxis.x * inAxis.y * oneMinusCos;
    Type xzm = inAxis.x * inAxis.z * oneMinusCos;
    Type yzm = inAxis.y * inAxis.z * oneMinusCos;
    Type xSin = inAxis.x * sn;
    Type ySin = inAxis.y * sn;
    Type zSin = inAxis.z * sn;

    inOutMtx[0] = x2 * oneMinusCos + cs;
    inOutMtx[1] = xym - zSin;
    inOutMtx[2] = xzm + ySin;
    inOutMtx[3] = xym + zSin;
    inOutMtx[4] = y2 * oneMinusCos + cs;
    inOutMtx[5] = yzm - xSin;
    inOutMtx[6] = xzm - ySin;
    inOutMtx[7] = yzm + xSin;
    inOutMtx[8] = z2 * oneMinusCos + cs;

    inOutMtx.__clearIdentFlag(sts_t::TMatrix3<Type>::ROT_IDENT);
    inOutMtx.__addIdentFlags(sts_t::TMatrix3<Type>::SCL_IDENT);
    return inOutMtx;
}

template<class Type>
sts_t::TMatrix3<Type> & fromQuat(sts_t::TMatrix3<Type> & inOutMtx, const sts_t::Quaternion<Type> & inQuat) {
    if (inQuat.isIdentityOrNull()) {
        inOutMtx.setRotateIdentity();
        return inOutMtx;
    }

    Type factor = Type(2) / (inQuat[1] * inQuat[1] + inQuat[2] * inQuat[2] + inQuat[3] * inQuat[3] + inQuat[0] * inQuat[0]);

    Type wz = inQuat[3] * inQuat[2] * factor;
    Type wx = inQuat[3] * inQuat[0] * factor;
    Type xz = inQuat[0] * inQuat[2] * factor;
    Type wy = inQuat[3] * inQuat[1] * factor;
    Type yz = inQuat[1] * inQuat[2] * factor;
    Type xy = inQuat[0] * inQuat[1] * factor;
    Type xx = inQuat[0] * inQuat[0] * factor;
    Type yy = inQuat[1] * inQuat[1] * factor;
    Type zz = inQuat[2] * inQuat[2] * factor;

    inOutMtx(0, 0) = Type(1) - (zz + yy);
    inOutMtx(2, 2) = Type(1) - (yy + xx);
    inOutMtx(1, 1) = Type(1) - (zz + xx);

    inOutMtx(0, 1) = xy - wz;
    inOutMtx(0, 2) = xz + wy;
    inOutMtx(1, 0) = xy + wz;
    inOutMtx(1, 2) = yz - wx;
    inOutMtx(2, 0) = xz - wy;
    inOutMtx(2, 1) = yz + wx;

    inOutMtx.__clearIdentFlag(sts_t::TMatrix3<Type>::ROT_IDENT);
    inOutMtx.__addIdentFlags(sts_t::TMatrix3<Type>::SCL_IDENT);
    return inOutMtx;
}

template<class Type>
sts_t::TMatrix3<Type> & fromAxisAngle(sts_t::TMatrix3<Type> & inOutMtx, const sts_t::AxisAngle<Type> & inAxisAngle) {
    return fromAxisAngle<Type>(inOutMtx, inAxisAngle.vector(), inAxisAngle.angle());
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

template<class Type>
sts_t::AxisAngle<Type> toAxisAngle(const sts_t::Quaternion<Type> & inQuat) {
    sts_t::AxisAngle<Type> out;
    return fromQuat<Type>(out, inQuat);
}

template<class Type>
sts_t::Quaternion<Type> toQuat(const sts_t::TMatrix3<Type> & inMtx) {
    sts_t::Quaternion<Type> out;
    return fromTMatrix3<Type>(out, inMtx);
}

template<class Type>
sts_t::Quaternion<Type> toQuat(const sts_t::Vector3<Type> & inAxis, Type inAngle) {
    sts_t::Quaternion<Type> out;
    return fromAxisAngle<Type>(out, inAxis, inAngle);
}

template<class Type>
sts_t::Quaternion<Type> toQuat(const sts_t::AxisAngle<Type> & inAxisAngle) {
    sts_t::Quaternion<Type> out;
    return fromAxisAngle<Type>(out, inAxisAngle);
}

template<class Type>
sts_t::TMatrix3<Type> toTMatrix3(const sts_t::Vector3<Type> & inAxis, Type inAngle) {
    sts_t::TMatrix3<Type> out;
    return fromAxisAngle<Type>(out, inAxis, inAngle);
}

template<class Type>
sts_t::TMatrix3<Type> toTMatrix3(const sts_t::Quaternion<Type> & inQuat) {
    sts_t::TMatrix3<Type> out;
    return fromQuat<Type>(out, inQuat);
}

template<class Type>
sts_t::TMatrix3<Type> toTMatrix3(const sts_t::AxisAngle<Type> & inAxisAngle) {
    sts_t::TMatrix3<Type> out;
    return fromAxisAngle<Type>(out, inAxisAngle);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
