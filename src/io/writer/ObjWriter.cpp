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
#include <sstream>

#include "xpln/obj/ObjMain.h"
#include "io/ObjValidators.h"

#include "xpln/Info.h"
#include "Writer.h"
#include "xpln/obj/ObjLine.h"
#include "sts/utilities/Compare.h"
#include "sts/string/StringUtils.h"
#include "converters/ObjString.h"
#include "ObjWriteOptimize.h"
#include "io/ObjTransformation.h"
#include "ObjWriteInstancing.h"

namespace xobj {

	/**************************************************************************************************/
	////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
	/**************************************************************************************************/

	ObjWriter::ObjWriter()
		: mAnimationWritter(&mExportOptions, &mStatistic),
		mObjWriteGeometry(&mExportOptions, &mStatistic) {

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

	bool ObjWriter::writeFile(ObjMain * inRoot, const std::string & inPath, const std::string & inSignature,
							IOStatistic & outStat, const TMatrix & inTm) {
		try {
			reset(); // reset all data that needs to be recalculated

			if (inRoot == nullptr || !checkParameters(*inRoot, inRoot->objectName()))
				return false;

			if (inRoot->pExportOptions.isEnabled(XOBJ_EXP_DEBUG)) {
				ULMessage << "File: " << inPath;
			}

			mMain = inRoot;
			mExportOptions = inRoot->pExportOptions;

			Writer writer;
			if (!writer.openFile(inPath))
				return false;

			writer.spaceEnable(mExportOptions.isEnabled(XOBJ_EXP_MARK_TREE_HIERARCHY));
			//-------------------------------------------------------------------------

			if (mExportOptions.isEnabled(XOBJ_EXP_CHECK_INSTANCE)) {
				ObjWriteInstancing::check(*mMain);
			}

			if (!ObjWritePreparer::prepare(*mMain)) {
				return false;
			}
			ObjWriteOptimize::optimize(*mMain);
			ObjTransformation::correctExportTransform(*mMain, inTm, mExportOptions.isEnabled(XOBJ_EXP_APPLY_LOD_TM));

			//-------------------------------------------------------------------------
			// calculate count
			size_t lodCount = mMain->lodCount();
			for (size_t i = 0; i < lodCount; ++i) {
				calculateVerticiesAndFaces(mMain->lod(i).transform());
			}

			// print global
			printGlobalInformation(writer, *mMain);

			// print mesh vertex 
			if (mStatistic.pMeshVerticesCount) {
				for (size_t i = 0; i < lodCount; ++i)
					mObjWriteGeometry.printMeshVerticiesRecursive(writer, mMain->lod(i).transform());
			}

			// print line vertex 
			if (mStatistic.pLineVerticesCount) {
				for (size_t i = 0; i < lodCount; ++i)
					mObjWriteGeometry.printLineVerticiesRecursive(writer, mMain->lod(i).transform());
			}

			// print VLIGHT vertex 
			if (mStatistic.pLightObjPointCount) {
				for (size_t i = 0; i < lodCount; ++i)
					mObjWriteGeometry.printLightPointVerticiesRecursive(writer, mMain->lod(i).transform());
			}

			writer.printEol();

			// print mesh faces 
			if (mStatistic.pMeshVerticesCount) {
				mObjWriteGeometry.printMeshFaceRecursive(writer, *mMain);
			}

			writer.printEol();
			writer.printEol();

			// print animation and objects
			for (size_t i = 0; i < lodCount; ++i) {
				const ObjLodGroup & currLod = mMain->lod(i);

				if (currLod.transform().hasAnim()) {
					ULError << currLod.objectName() << " - Lod can't be animated.";
				}

				//-------------------------------------------------------------------------

				printLOD(writer, currLod, lodCount);
				printObjects(writer, currLod.transform());
				writer.printEol();
			}

			mStatistic.pTrisManipCount += mObjWriteManip.count();
			mStatistic.pTrisAttrCount += mWriteAttr.count();

			if (mMain->pAttr.isDebug()) {
				++mStatistic.pGlobAttrCount;
				writer.printLine("DEBUG");
				writer.printEol();
			}

			printSignature(writer, inSignature);
			writer.closeFile();
			outStat = mStatistic;
			return true;
		}
		catch (std::exception & e) {
			ULFatal << e.what();
			return false;
		}
	}

	void ObjWriter::printLOD(AbstractWriter & writer, const ObjLodGroup & inLOD, size_t inCount) const {
		if (inCount < 2 && sts::isEqual(inLOD.nearVal(), inLOD.farVal(), 0.1f)) {
			return;
		}
		writer.printLine(toObjString(inLOD));
	}

	/********************************************************************************************************/
	//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
	/********************************************************************************************************/

	inline std::string currentDateTime() {
		time_t now = time(0);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		//strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
		strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
		return buf;
	}

	void ObjWriter::printSignature(AbstractWriter & writer, const std::string & signature) {
		if (signature.size()) {
			writer.printEol();
			std::string s("## ");
			s.append(signature);
			sts::MbStrUtils::replace(s, "\r\n", "\n## ");
			writer.printLine(s);
		}
		std::string msg("## ");
		msg.append(XOBJ_ORGANIZATION_NAME).append(" ").append(XOBJ_PROJECT_SHORT_NAME);
		msg.append(": ").append(XOBJ_VERSION_STRING).append("-").append(XOBJ_RELEASE_TYPE);
		msg.append("+[").append(XOBJ_COMPILE_DATE).append("]");
		writer.printLine(msg);
		writer.printLine(std::string("## Object created: ").append(currentDateTime()));
	}

	/********************************************************************************************************/
	//////////////////////////////////////////////* Functions *///////////////////////////////////////////////
	/********************************************************************************************************/

	void ObjWriter::calculateVerticiesAndFaces(const Transform & inParent) {
		static const ObjMesh * mobj = nullptr;
		static const ObjLine * lobj = nullptr;
		for (auto obj : inParent.objList()) {
			if (obj->objType() == OBJ_MESH) {
				mobj = static_cast<const ObjMesh*>(obj);
				mStatistic.pMeshVerticesCount += mobj->pVertices.size();
				mStatistic.pMeshFacesCount += mobj->pFaces.size();
			}
			else if (obj->objType() == OBJ_LINE) {
				lobj = static_cast<const ObjLine*>(obj);
				mStatistic.pLineVerticesCount += lobj->verticesList().size();
			}
			else if (obj->objType() == OBJ_LIGHT_POINT) {
				++mStatistic.pLightObjPointCount;
			}
		}

		for (Transform::TransformIndex i = 0; i < inParent.childrenCount(); ++i) {
			calculateVerticiesAndFaces(*dynamic_cast<const Transform*>(inParent.childAt(i)));
		}
	}

	//-------------------------------------------------------------------------

	void ObjWriter::printGlobalInformation(AbstractWriter & writer, const ObjMain & ROOT) {
		// write header
		writer.printLine("I\n800\nOBJ\n");
		mWriteGlobAttr.write(&writer, &ROOT);
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

	void ObjWriter::printObjects(AbstractWriter & writer, const Transform & inParent) {

		//-------------------------------------------------------------------------

		mAnimationWritter.printAnimationStart(writer, inParent);

		//-------------------------------------------------------------------------

		for (auto objBase : inParent.objList()) {
			mWriteAttr.write(&writer, objBase);
			mObjWriteManip.write(&writer, objBase);

			//--------------

			if (mObjWriteGeometry.printMeshObject(writer, *objBase)) {
				continue;
			}

			if (mObjWriteGeometry.printLightObject(writer, *objBase, inParent)) {
				continue;
			}

			if (mObjWriteGeometry.printDummyObject(writer, *objBase)) {
				continue;
			}

			if (mObjWriteGeometry.printLineObject(writer, *objBase)) {
				continue;
			}

			mObjWriteGeometry.printLightPointObject(writer, *objBase);

			//--------------
		}

		//-------------------------------------------------------------------------

		// print child
		for (Transform::TransformIndex i = 0; i < inParent.childrenCount(); ++i)
			printObjects(writer, *dynamic_cast<const Transform*>(inParent.childAt(i)));

		//-------------------------------------------------------------------------

		mAnimationWritter.printAnimationEnd(writer, inParent);

		//-------------------------------------------------------------------------
	}

	/**************************************************************************************************/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************/

}
