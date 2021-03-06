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

#include "AbstractWriter.h"

#include "xpln/obj/ExportOptions.h"
#include "xpln/obj/IOStatistic.h"

#include "ObjWriteGlobAttr.h"
#include "ObjWriteAttr.h"
#include "ObjWritePreparer.h"
#include "ObjWriteAnim.h"
#include "ObjWriteGeometry.h"
#include "ObjWriteManip.h"

namespace xobj {

class ObjMain;
class ObjAbstract;
class ObjAbstractLight;
class ObjLodGroup;
class Transform;

/**********************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************/
/*!
 *	\brief X-Plane obj writer
 *	\details X-Plane obj writer
 */
class ObjWriter {
public:

    bool writeFile(ObjMain * root, ExportContext & context, const TMatrix & tm);

    void reset();
    ObjWriter();
    ~ObjWriter();

private:

    ExportOptions mExportOptions;
    IOStatistic mStatistic;

    ObjWriteAnim mAnimationWritter;
    ObjWriteGeometry mObjWriteGeometry;
    ObjWriteManip mObjWriteManip;
    ObjWriteGlobAttr mWriteGlobAttr;
    ObjWriteAttr mWriteAttr;

    ObjMain * mMain;

    void calculateVerticiesAndFaces(const Transform & parent);
    void printGlobalInformation(AbstractWriter & writer, const ObjMain & objRoot);
    void printObjects(AbstractWriter & writer, const Transform & parent);

    static void printSignature(AbstractWriter & writer, const std::string & signature);
    void printLOD(AbstractWriter & writer, const ObjLodGroup & lod, size_t count) const;

    static size_t printObjCustomData(AbstractWriter & writer, const std::vector<std::string> & strings);

};

/**********************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************/
}
