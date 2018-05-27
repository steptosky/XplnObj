#pragma once

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

#include <cstddef>
#include "AbstractWriter.h"

namespace xobj {

class Logger;
class ExportOptions;

class ObjIOStream;
class IOStatistic;
class ObjAbstract;

class ObjAbstractLight;
class String;
class Counter;

class Point3;
class Transform;

class ObjMain;

/**********************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************/

/*!
 *	\details Class helper that write geometry for ObjWritter
 */
class ObjWriteGeometry {
public:

    ObjWriteGeometry(const ExportOptions * option, IOStatistic * outStat);
    ~ObjWriteGeometry() = default;

    void printMeshVerticiesRecursive(AbstractWriter & writer, const Transform & transform) const;
    void printLineVerticiesRecursive(AbstractWriter & writer, const Transform & transform) const;
    void printLightPointVerticiesRecursive(AbstractWriter & writer, const Transform & transform) const;
    void printMeshFaceRecursive(AbstractWriter & writer, const ObjMain & main) const;

    bool printMeshObject(AbstractWriter & writer, const ObjAbstract & objBase);
    bool printLightPointObject(AbstractWriter & writer, const ObjAbstract & objBase);
    bool printLightObject(AbstractWriter & writer, const ObjAbstract & objBase, const Transform & transform) const;
    bool printLineObject(AbstractWriter & writer, const ObjAbstract & objBase);
    bool printSmokeObject(AbstractWriter & writer, const ObjAbstract & objBase) const;
    bool printDummyObject(AbstractWriter & writer, const ObjAbstract & objBase) const;

    void reset();

private:

    ObjWriteGeometry(const ObjWriteGeometry &) = delete;
    ObjWriteGeometry & operator =(const ObjWriteGeometry &) = delete;

    void writeMeshFaceRecursive(std::ostream & writer, const Transform & parent, size_t & idx, size_t & offset) const;

    IOStatistic * mStat;
    const ExportOptions * mOptions;

    // Mesh
    size_t mMeshFaceOffset;
    size_t mMeshVertexOffset;

    // Light
    size_t mPointLightOffsetByObject;

};

/**********************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************/
}
