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

#include <cassert>

#include "ObjWriteGeometry.h"
#include "converters/ObjString.h"
#include "converters/StringStream.h"

#include "xpln/obj/ObjMain.h"
#include "xpln/obj/ObjMesh.h"
#include "xpln/obj/ObjLine.h"
#include "xpln/obj/ObjLightPoint.h"
#include "xpln/obj/ObjLightCustom.h"
#include "xpln/obj/ObjLightNamed.h"
#include "xpln/obj/ObjLightParam.h"
#include "xpln/obj/ObjLightSpillCust.h"
#include "xpln/obj/ObjSmoke.h"

#include "xpln/obj/IOStatistic.h"
#include "xpln/obj/ExportOptions.h"
#include "xpln/enums/eExportOptions.h"
#include "converters/Defines.h"
#include "common/AttributeNames.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ObjWriteGeometry::ObjWriteGeometry(const ExportOptions * option, IOStatistic * outStat)
    : mMeshFaceOffset(0),
      mMeshVertexOffset(0),
      mPointLightOffsetByObject(0) {

    assert(option);
    assert(outStat);

    mStat = outStat;
    mOptions = option;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteGeometry::reset() {
    mMeshVertexOffset = 0;
    mMeshFaceOffset = 0;
    mPointLightOffsetByObject = 0;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteGeometry::printMeshVerticiesRecursive(AbstractWriter & writer, const Transform & transform) const {
    for (auto & objBase : transform.objList()) {
        if (objBase->objType() == OBJ_MESH) {
            const auto * mobj = static_cast<const ObjMesh*>(objBase.get());

            if (mOptions->isEnabled(XOBJ_EXP_DEBUG)) {
                writer.printLine(std::string("# ").append(mobj->objectName()));
            }

            for (const MeshVertex & v : mobj->pVertices) {
                printObj(v, writer, mobj->pAttr.mIsTree);
            }
        }
    }

    for (Transform::TransformIndex i = 0; i < transform.childrenNum(); ++i) {
        const auto * ch = dynamic_cast<const Transform*>(transform.childAt(i));
        assert(ch);
        if (ch) {
            printMeshVerticiesRecursive(writer, *ch);
        }
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteGeometry::printMeshFaceRecursive(AbstractWriter & writer, const ObjMain & main) const {
    std::stringstream stream;
    stream.precision(PRECISION);
    stream << std::fixed;

    std::size_t idx = 0;
    std::size_t offset = 0;
    for (const auto & lod : main.lods()) {
        writeMeshFaceRecursive(stream, lod->transform(), idx, offset);
    }
    writeMeshFaceRecursive(stream, main.pDraped.transform(), idx, offset);
    writer.printLine(stream.str());
}

void ObjWriteGeometry::writeMeshFaceRecursive(std::ostream & writer, const Transform & inNode, std::size_t & idx,
                                              std::size_t & offset) const {
    for (const auto & objBase : inNode.objList()) {
        if (objBase->objType() != OBJ_MESH) {
            continue;
        }

        const auto * mobj = static_cast<const ObjMesh*>(objBase.get());
        const ObjMesh::FaceList & faces = mobj->pFaces;

        const std::size_t idxNum = faces.size() * 3U;
        const std::size_t vEnd = mStat->pMeshFacesCount * 3U;

        for (size_t currIdx = 0; currIdx < idxNum; ++currIdx) {
            const std::size_t last = (idx % 10);
            const std::size_t ost = (vEnd - idx);
            ++idx;

            if (last == 0) {
                ost < 10 ? writer << std::endl << MESH_IDX << " " : writer << std::endl << MESH_IDX10 << " ";
            }
            else if (last + ost < 10) {
                writer << std::endl << MESH_IDX << " ";
            }

            const std::size_t modulo = currIdx % 3U;
            const MeshFace & f = faces.at(currIdx / 3U);
            switch (modulo) {
                case 0: writer << (f.pV0 + offset) << " ";
                    break;
                case 2: writer << (f.pV2 + offset) << " ";
                    break;
                default: writer << (f.pV1 + offset) << " ";
                    break;
            }
        }
        offset += mobj->pVertices.size();
    }

    for (Transform::TransformIndex i = 0; i < inNode.childrenNum(); ++i) {
        const auto * ch = dynamic_cast<const Transform*>(inNode.childAt(i));
        assert(ch);
        if (ch) {
            writeMeshFaceRecursive(writer, *ch, idx, offset);
        }
    }
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriteGeometry::printLineVerticiesRecursive(AbstractWriter & writer, const Transform & transform) const {
    for (auto & objBase : transform.objList()) {
        if (objBase->objType() == OBJ_LINE) {
            const auto lobj = static_cast<const ObjLine*>(objBase.get());

            if (mOptions->isEnabled(eExportOptions::XOBJ_EXP_DEBUG)) {
                writer.printLine(std::string("# ").append(lobj->objectName()));
            }

            for (const LineVertex & v : lobj->verticesList()) {
                printObj(v, writer);
            }
        }
    }

    for (Transform::TransformIndex i = 0; i < transform.childrenNum(); ++i) {
        const auto * ch = dynamic_cast<const Transform*>(transform.childAt(i));
        assert(ch);
        if (ch) {
            printLineVerticiesRecursive(writer, *dynamic_cast<const Transform*>(transform.childAt(i)));
        }
    }
}

//-------------------------------------------------------------------------

void ObjWriteGeometry::printLightPointVerticiesRecursive(AbstractWriter & writer, const Transform & transform) const {
    for (auto & objBase : transform.objList()) {
        if (objBase->objType() == OBJ_LIGHT_POINT) {
            const auto lobj = static_cast<const ObjLightPoint*>(objBase.get());
            printObj(*lobj, writer, mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_LIGHT));
        }
    }

    for (Transform::TransformIndex i = 0; i < transform.childrenNum(); ++i) {
        const auto * ch = dynamic_cast<const Transform*>(transform.childAt(i));
        assert(ch);
        if (ch) {
            printLightPointVerticiesRecursive(writer, *dynamic_cast<const Transform*>(transform.childAt(i)));
        }
    }
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

bool ObjWriteGeometry::printMeshObject(AbstractWriter & writer, const ObjAbstract & objBase) {
    if (objBase.objType() == OBJ_MESH) {
        const auto * mobj = static_cast<const ObjMesh*>(&objBase);
        const std::size_t numface = mobj->pFaces.size();
        std::stringstream stream;
        stream.precision(PRECISION);
        stream << std::fixed;

        if (mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_MESH)) {
            stream << MESH_TRIS << " " << (mMeshFaceOffset * 3) << " " << (numface * 3) << " ## " << mobj->objectName().data();
        }
        else {
            stream << MESH_TRIS << " " << (mMeshFaceOffset * 3) << " " << (numface * 3);
        }

        writer.printLine(stream.str());
        ++mStat->pMeshObjCount;
        mMeshFaceOffset += numface;
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------

bool ObjWriteGeometry::printLightPointObject(AbstractWriter & writer, const ObjAbstract & objBase) {
    if (objBase.objType() == OBJ_LIGHT_POINT) {
        std::stringstream stream;
        stream.precision(PRECISION);
        stream << std::fixed;

        stream << LIGHTS << " " << mPointLightOffsetByObject << " " << std::size_t(1);

        if (mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_LIGHT)) {
            stream << " ## " << objBase.objectName().c_str();
        }

        writer.printLine(stream.str());
        ++mPointLightOffsetByObject;
        ++mStat->pLightObjPointCount;
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------

template<typename T>
bool printLight(AbstractWriter & writer, const T & lobj, const ExportOptions & options, std::size_t & counter) {
    printObj(lobj, writer, options.isEnabled(XOBJ_EXP_MARK_LIGHT));
    // std::string params = toObjString(lobj, options.isEnabled(XOBJ_EXP_MARK_LIGHT));
    // if (!params.empty()) {
    //     writer.printLine(params.c_str());
    //     ++counter;
    // }
    ++counter;
    return true;
}

bool ObjWriteGeometry::
printLightObject(AbstractWriter & writer, const ObjAbstract & objBase, const Transform &) const {
    const eObjectType type = objBase.objType();
    switch (type) {
        case OBJ_LIGHT_NAMED:
            return printLight<ObjLightNamed>(writer, static_cast<const ObjLightNamed&>(objBase), *mOptions,
                                             mStat->pLightObjNamedCount);
        case OBJ_LIGHT_CUSTOM:
            return printLight<ObjLightCustom>(writer, static_cast<const ObjLightCustom&>(objBase), *mOptions,
                                              mStat->pLightObjCustomCount);
        case OBJ_LIGHT_PARAM:
            return printLight<ObjLightParam>(writer, static_cast<const ObjLightParam&>(objBase), *mOptions,
                                             mStat->pLightObjParamCount);
        case OBJ_LIGHT_SPILL_CUSTOM:
            return printLight<ObjLightSpillCust>(writer, static_cast<const ObjLightSpillCust&>(objBase), *mOptions,
                                                 mStat->pLightObjSpillCustCount);
        default:
            return false;
    }
}

//-------------------------------------------------------------------------

bool ObjWriteGeometry::printLineObject(AbstractWriter & writer, const ObjAbstract & objBase) {
    if (objBase.objType() == OBJ_LINE) {
        // todo something wrong with this code wasn't it written? Seems like copy/paste from mesh.
        const auto * lobj = static_cast<const ObjLine*>(&objBase);
        const size_t numvert = lobj->verticesList().size();
        std::stringstream stream;
        stream.precision(PRECISION);
        stream << std::fixed;

        if (mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_LINE)) {
            stream << LINES << " " << mMeshVertexOffset << " " << numvert << " ## " << lobj->objectName() << std::endl;
        }
        else {
            stream << LINES << " " << mMeshVertexOffset << " " << numvert << std::endl;
        }

        writer.printLine(stream.str());
        mMeshVertexOffset += numvert;
        ++mStat->pLineObjCount;
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------

bool ObjWriteGeometry::printSmokeObject(AbstractWriter & writer, const ObjAbstract & objBase) const {
    if (objBase.objType() == OBJ_SMOKE) {
        const auto & smoke = reinterpret_cast<const ObjSmoke&>(objBase);
        printObj(smoke, writer, mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_SMOKE));
        // std::string params = toObjString(smoke, mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_SMOKE));
        // if (!params.empty()) {
        //     writer.printLine(params);
        //     ++mStat->pSmokeObjCount;
        // }
        ++mStat->pSmokeObjCount;
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------

bool ObjWriteGeometry::printDummyObject(AbstractWriter & writer, const ObjAbstract & objBase) const {
    if (objBase.objType() == OBJ_DUMMY) {
        const auto & dummy = reinterpret_cast<const ObjDummy&>(objBase);
        printObj(dummy, writer, mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_DUMMY));
        // std::string params = toObjString(dummy, mOptions->isEnabled(eExportOptions::XOBJ_EXP_MARK_DUMMY));
        // if (!params.empty()) {
        //     writer.printLine(params);
        //     ++mStat->pDummyObjCount;
        // }
        ++mStat->pDummyObjCount;
        return true;
    }
    return false;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
}
