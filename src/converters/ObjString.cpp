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

#include "ObjString.h"
#include "converters/StringStream.h"

#include "common/AttributeNames.h"

#include "xpln/obj/MeshVertex.h"
#include "xpln/obj/LineVertex.h"

#include "xpln/obj/ObjLightCustom.h"
#include "xpln/obj/ObjLightNamed.h"
#include "xpln/obj/ObjLightParam.h"
#include "xpln/obj/ObjLightPoint.h"
#include "xpln/obj/ObjEmitter.h"
#include "xpln/obj/ObjLightSpillCust.h"

#include "xpln/obj/ObjLodGroup.h"
#include "xpln/obj/ObjSmoke.h"
#include "xpln/obj/ObjDummy.h"

#include "io/writer/AbstractWriter.h"

#include "Defines.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void printObj(const MeshVertex & vertex, AbstractWriter & writer, const bool isTree) {
    StringStream out;
    out << MESH_VT << " " << vertex.mPosition.toString(PRECISION) << "  ";

    if (isTree)
        out << 0.0f << " " << 1.0f << " " << 0.0f;
    else
        out << vertex.mNormal.normalized().toString(PRECISION);

    out << "  " << vertex.mTexture.toString(PRECISION);
    writer.printLine(out.str());
}

void printObj(const LineVertex & vertex, AbstractWriter & writer) {
    StringStream out;
    out << VLINE
            << " " << vertex.mPosition.toString(PRECISION)
            << " " << vertex.mColor.red()
            << " " << vertex.mColor.green()
            << " " << vertex.mColor.blue();
    writer.printLine(out.str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void printObj(const ObjLodGroup & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    out << ATTR_LOD << " " << obj.nearVal() << " " << obj.farVal();
    if (printName) {
        out << " ## " << obj.objectName();
    }
    writer.printLine(out.str());
}

void printObj(const ObjSmoke & obj, AbstractWriter & writer, const bool printName) {
    if (obj.smokeType() == ObjSmoke::none) {
        // todo maybe warning about none?
        return;
    }
    StringStream out;
    out << (obj.smokeType() == ObjSmoke::white ? SMOKE_WHITE : SMOKE_BLACK)
            << " " << obj.position().toString(PRECISION)
            << " " << obj.size();
    if (printName) {
        out << " ## " << obj.objectName();
    }
    writer.printLine(out.str());
}

void printObj(const ObjDummy & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    if (printName) {
        out << "## Dummy: " << obj.objectName();
        writer.printLine(out.str());
    }
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

void printObj(const ObjLightCustom & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    if (printName) {
        out << "## " << obj.objectName() << std::endl;
    }
    out << LIGHT_CUSTOM
            << " " << obj.position().toString(PRECISION)
            << " " << obj.color().toString(PRECISION)
            << " " << obj.size()
            << " " << obj.textureRect().point1().toString(PRECISION)
            << " " << obj.textureRect().point2().toString(PRECISION)
            << " " << (obj.dataRef().empty() ? "none" : writer.actualDataref(obj.dataRef()).c_str());
    writer.printLine(out.str());
}

//-------------------------------------------------------------------------

void printObj(const ObjLightNamed & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    if (printName) {
        out << "## " << obj.objectName() << std::endl;
    }
    out << LIGHT_NAMED
            << " " << obj.name()
            << " " << obj.position().toString(PRECISION);
    writer.printLine(out.str());
}

//-------------------------------------------------------------------------

void printObj(const ObjLightParam & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    if (printName) {
        out << "## " << obj.objectName() << std::endl;
    }
    out << LIGHT_PARAM
            << " " << obj.name()
            << " " << obj.position().toString(PRECISION)
            << " " << obj.params();
    writer.printLine(out.str());
}

//-------------------------------------------------------------------------

void printObj(const ObjLightPoint & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    if (printName) {
        out << "## " << obj.objectName() << std::endl;
    }
    const Color & c = obj.color();
    out << VLIGHT << " " << obj.position().toString(PRECISION) << " "
            << c.red() << " " << c.green() << " " << c.blue();
    writer.printLine(out.str());
}

//-------------------------------------------------------------------------

void printObj(const ObjEmitter & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    if (printName) {
        out << "## " << obj.objectName() << std::endl;
    }
    out << ATTR_EMITTER
            << " " << obj.objectName()
            << " " << obj.position().toString(PRECISION);

    auto [psi, the, phi] = obj.orientation();
    out << " " << psi
            << " " << the
            << " " << phi;

    const auto index = obj.index();
    if (index != 0) {
        out << " " << index;
    }
    writer.printLine(out.str());
}

//-------------------------------------------------------------------------

void printObj(const ObjLightSpillCust & obj, AbstractWriter & writer, const bool printName) {
    StringStream out;
    if (printName) {
        out << "## " << obj.objectName() << std::endl;
    }
    out << LIGHT_SPILL_CUSTOM
            << " " << obj.position().toString(PRECISION)
            << " " << obj.color().toString(PRECISION)
            << " " << obj.size()
            << " " << obj.direction().toString(PRECISION)
            << " " << obj.semiRaw()
            << " " << (obj.dataRef().empty() ? "none" : writer.actualDataref(obj.dataRef()).c_str());
    writer.printLine(out.str());
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
