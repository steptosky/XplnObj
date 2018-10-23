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

#include "ObjWriter.h"
#include "xpln/obj/ObjMain.h"
#include "io/ObjValidators.h"

#include "xpln/Info.h"
#include "Writer.h"
#include "xpln/obj/ObjLine.h"
#include "sts/utilities/Compare.h"
#include "converters/ObjString.h"
#include "algorithms/Draped.h"
#include "io/ObjTransformation.h"
#include "algorithms/InstancingAlg.h"
#include "common/Logger.h"
#include "sts/string/StringUtils.h"
#include "algorithms/LodsAlg.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ObjWriter::ObjWriter()
    : mAnimationWritter(&mExportOptions, &mStatistic),
      mObjWriteGeometry(&mExportOptions, &mStatistic),
      mWriteAttr(&mObjWriteManip) {

    reset();
}

//-------------------------------------------------------------------------

ObjWriter::~ObjWriter() {
    reset();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjWriter::reset() {
    mStatistic.reset();
    mWriteGlobAttr.reset();
    mWriteAttr.reset();
    mObjWriteGeometry.reset();
    mObjWriteManip.reset();
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ObjWriter::writeFile(ObjMain * root, ExportContext & context, const TMatrix & tm) {
    try {
        const IInterrupt & interrupt = *context.interruptor();
        reset(); // reset all data that needs to be recalculated

        if (root == nullptr || !checkParameters(*root, root->objectName())) {
            return false;
        }

        if (root->pExportOptions.isEnabled(XOBJ_EXP_DEBUG)) {
            // todo sts::toMbString may work incorrectly.
            ULMessage << "File: " << sts::toMbString(context.objFile());
        }

        mMain = root;
        mExportOptions = root->pExportOptions;

        Writer writer;
        if (!writer.openFile(context.objFile())) {
            return false;
        }
        writer.spaceEnable(mExportOptions.isEnabled(XOBJ_EXP_MARK_TREE_HIERARCHY));
        //-------------------------------------------------------------------------

        if (mMain->pDraped.objectName().empty()) {
            mMain->pDraped.setObjectName(mMain->objectName());
        }

        if (!LodsAlg::validate(mMain->lods(), mMain->objectName(), interrupt)) {
            return false;
        }

        // Draped::ensureDrapedAttrIsSet(mMain->pDraped, interrupt);
        // for (const auto & lod : mMain->lods()) {
        //     INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);
        //     Draped::extract(mMain->pDraped, lod->transform(), interrupt);
        // }

        LodsAlg::removeWithoutObjects(mMain->lods(), interrupt);
        LodsAlg::mergeIdenticalLods(mMain->lods(), interrupt);
        if (!LodsAlg::sort(mMain->lods(), interrupt)) {
            return false;
        }
        INTERRUPT_CHECK_WITH_RETURN_VAL(interrupt, false);
        //-------------------------------------------------------------------------

        if (mExportOptions.isEnabled(XOBJ_EXP_CHECK_INSTANCE)) {
            InstancingAlg::validateAndPrepare(*mMain);
        }

        if (!ObjWritePreparer::prepare(*mMain)) {
            return false;
        }

        ObjTransformation::correctExportTransform(*mMain, tm, mExportOptions.isEnabled(XOBJ_EXP_APPLY_LOD_TM));

        //-------------------------------------------------------------------------
        // calculate count
        for (const auto & lod : mMain->lods()) {
            calculateVerticiesAndFaces(lod->transform());
        }

        calculateVerticiesAndFaces(mMain->pDraped.transform());

        //-------------------------------------------------------------------------
        // print global
        printGlobalInformation(writer, *mMain);

        // print mesh vertex 
        if (mStatistic.pMeshVerticesCount) {
            for (const auto & lod : mMain->lods()) {
                mObjWriteGeometry.printMeshVerticiesRecursive(writer, lod->transform());
            }
        }

        // print line vertex 
        if (mStatistic.pLineVerticesCount) {
            for (const auto & lod : mMain->lods()) {
                mObjWriteGeometry.printLineVerticiesRecursive(writer, lod->transform());
            }
        }

        // print VLIGHT vertex 
        if (mStatistic.pLightObjPointCount) {
            for (const auto & lod : mMain->lods()) {
                mObjWriteGeometry.printLightPointVerticiesRecursive(writer, lod->transform());
            }
        }

        // print draped
        mObjWriteGeometry.printMeshVerticiesRecursive(writer, mMain->pDraped.transform());

        writer.printEol();

        //-------------------------------------------------------------------------
        // print mesh faces 
        if (mStatistic.pMeshVerticesCount) {
            mObjWriteGeometry.printMeshFaceRecursive(writer, *mMain);
        }

        writer.printEol();
        writer.printEol();

        // print animation and objects
        for (const auto & currLod : mMain->lods()) {
            if (currLod->transform().hasAnim()) {
                ULError << currLod->objectName() << " - Lod can't be animated.";
            }

            printLOD(writer, *currLod, mMain->lods().size());
            printObjects(writer, currLod->transform());
            writer.printEol();
        }

        printObjects(writer, mMain->pDraped.transform());
        writer.printEol();

        mStatistic.pTrisManipCount += mObjWriteManip.count();
        mStatistic.pTrisAttrCount += mWriteAttr.count();

        if (mMain->pAttr.isDebug()) {
            ++mStatistic.pGlobAttrCount;
            writer.printLine("DEBUG");
            writer.printEol();
        }

        printSignature(writer, context.signature());
        writer.closeFile();
        context.setStatistic(mStatistic);
        return true;
    }
    catch (std::exception & e) {
        ULFatal << e.what();
        return false;
    }
}

void ObjWriter::printLOD(AbstractWriter & writer, const ObjLodGroup & lod, const size_t count) const {
    if (count < 2 && sts::isEqual(lod.nearVal(), lod.farVal(), 0.1f)) {
        return;
    }
    printObj(lod, writer, true);
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

inline std::string currentDateTime() {
    time_t now = time(nullptr);
    char buf[80];
    struct tm tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
}

void ObjWriter::printSignature(AbstractWriter & writer, const std::string & signature) {
    if (!signature.empty()) {
        writer.printEol();
        std::string s("## ");
        s.append(signature);
        s = sts::MbStrUtils::replaceCopy(s, "\r\n", "\n## ");
        writer.printLine(s);
    }
    std::string msg("## ");
    msg.append(XOBJ_ORGANIZATION_NAME).append(" ").append(XOBJ_PROJECT_NAME);
    msg.append(": ").append(XOBJ_VERSION_STRING);
    if (!std::string(XOBJ_RELEASE_TYPE).empty()) {
        msg.append("-").append(XOBJ_RELEASE_TYPE);
    }
    msg.append("+[").append(XOBJ_COMPILE_DATE).append("]");
    writer.printLine(msg);
    writer.printLine(std::string("## Object created: ").append(currentDateTime()));
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

void ObjWriter::calculateVerticiesAndFaces(const Transform & parent) {
    static const ObjMesh * mobj = nullptr;
    static const ObjLine * lobj = nullptr;
    for (auto & obj : parent.objList()) {
        if (obj->objType() == OBJ_MESH) {
            mobj = static_cast<const ObjMesh*>(obj.get());
            mStatistic.pMeshVerticesCount += mobj->pVertices.size();
            mStatistic.pMeshFacesCount += mobj->pFaces.size();
        }
        else if (obj->objType() == OBJ_LINE) {
            lobj = static_cast<const ObjLine*>(obj.get());
            mStatistic.pLineVerticesCount += lobj->verticesList().size();
        }
        else if (obj->objType() == OBJ_LIGHT_POINT) {
            ++mStatistic.pLightObjPointCount;
        }
    }

    for (Transform::TransformIndex i = 0; i < parent.childrenNum(); ++i) {
        calculateVerticiesAndFaces(*dynamic_cast<const Transform*>(parent.childAt(i)));
    }
}

//-------------------------------------------------------------------------

void ObjWriter::printGlobalInformation(AbstractWriter & writer, const ObjMain & objRoot) {
    // write header
    writer.printLine("I\n800\nOBJ\n");
    mWriteGlobAttr.write(&writer, &objRoot);
    mStatistic.pGlobAttrCount += mWriteGlobAttr.count();

    writer.printEol();
    std::stringstream stream;
    stream << "POINT_COUNTS " << static_cast<uint32_t>(mStatistic.pMeshVerticesCount) << " "
            << mStatistic.pLineVerticesCount << " "
            << mStatistic.pLightObjPointCount << " "
            << (mStatistic.pMeshFacesCount * 3);
    writer.printLine(stream.str());
}

/********************************************************************************************************/
//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
/********************************************************************************************************/

void ObjWriter::printObjects(AbstractWriter & writer, const Transform & parent) {

    //-------------------------------------------------------------------------

    mAnimationWritter.printAnimationStart(writer, parent);

    //-------------------------------------------------------------------------

    for (auto & objBase : parent.objList()) {
        // order attr and manip is important.
        mWriteAttr.write(&writer, objBase.get());
        mObjWriteManip.write(&writer, objBase.get());

        //--------------

        mStatistic.pCustomLinesCount += printObjCustomData(writer, objBase->dataBefore());

        if (mObjWriteGeometry.printMeshObject(writer, *objBase)) {
            mStatistic.pCustomLinesCount += printObjCustomData(writer, objBase->dataAfter());
            continue;
        }

        if (mObjWriteGeometry.printLightObject(writer, *objBase, parent)) {
            mStatistic.pCustomLinesCount += printObjCustomData(writer, objBase->dataAfter());
            continue;
        }

        if (mObjWriteGeometry.printSmokeObject(writer, *objBase)) {
            mStatistic.pCustomLinesCount += printObjCustomData(writer, objBase->dataAfter());
            continue;
        }

        if (mObjWriteGeometry.printDummyObject(writer, *objBase)) {
            mStatistic.pCustomLinesCount += printObjCustomData(writer, objBase->dataAfter());
            continue;
        }

        if (mObjWriteGeometry.printLineObject(writer, *objBase)) {
            mStatistic.pCustomLinesCount += printObjCustomData(writer, objBase->dataAfter());
            continue;
        }

        mObjWriteGeometry.printLightPointObject(writer, *objBase);
        mStatistic.pCustomLinesCount += printObjCustomData(writer, objBase->dataAfter());

        //--------------
    }

    //-------------------------------------------------------------------------

    // print child
    for (Transform::TransformIndex i = 0; i < parent.childrenNum(); ++i)
        printObjects(writer, *dynamic_cast<const Transform*>(parent.childAt(i)));

    //-------------------------------------------------------------------------

    mAnimationWritter.printAnimationEnd(writer, parent);

    //-------------------------------------------------------------------------
}

size_t ObjWriter::printObjCustomData(AbstractWriter & writer, const std::vector<std::string> & strings) {
    for (auto & str : strings) {
        writer.printLine(str);
    }
    return strings.size();
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
