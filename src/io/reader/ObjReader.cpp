/*
**  Copyright(C) 2018, StepToSky
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

#include "sts/utilities/Compare.h"
#include "ObjReader.h"
#include "ObjReadParser.h"
#include "common/AttributeNames.h"
#include "common/Logger.h"
#include "sts/string/StringUtils.h"

#include "xpln/obj/attributes/AttrBlend.h"
#include "xpln/obj/attributes/AttrDrapedLayerGroup.h"
#include "xpln/obj/attributes/AttrHard.h"
#include "xpln/obj/attributes/AttrLayerGroup.h"
#include "xpln/obj/attributes/AttrLightLevel.h"
#include "xpln/obj/attributes/AttrDrapedLod.h"
#include "xpln/obj/attributes/AttrPolyOffset.h"
#include "xpln/obj/attributes/AttrShiny.h"
#include "xpln/obj/attributes/AttrSlopeLimit.h"
#include "xpln/obj/attributes/AttrSlungLoadWeight.h"
#include "xpln/obj/attributes/AttrSpecular.h"
#include "xpln/obj/attributes/AttrTint.h"
#include "xpln/obj/attributes/AttrWetDry.h"
#include "xpln/obj/attributes/AttrCockpitRegion.h"
#include "xpln/obj/attributes/AttrCockpit.h"
#include "xpln/obj/manipulators/AttrManipCmd.h"
#include "xpln/obj/manipulators/AttrManipCmdAxis.h"
#include "xpln/obj/manipulators/AttrManipDelta.h"
#include "xpln/obj/manipulators/AttrManipDragAxis.h"
#include "xpln/obj/manipulators/AttrManipDragRotate.h"
#include "xpln/obj/manipulators/AttrManipDragAxisPix.h"
#include "xpln/obj/manipulators/AttrManipDragXy.h"
#include "xpln/obj/manipulators/AttrManipNoop.h"
#include "xpln/obj/manipulators/AttrManipPush.h"
#include "xpln/obj/manipulators/AttrManipRadio.h"
#include "xpln/obj/manipulators/AttrManipToggle.h"
#include "xpln/obj/manipulators/AttrManipWrap.h"
#include "xpln/obj/manipulators/AttrManipCmdKnob.h"
#include "xpln/obj/manipulators/AttrManipCmdKnob2.h"
#include "xpln/obj/manipulators/AttrManipAxisSwitchLeftRight.h"
#include "xpln/obj/manipulators/AttrManipAxisSwitchUpDown.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchLeftRight.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchLeftRight2.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchUpDown.h"
#include "xpln/obj/manipulators/AttrManipCmdSwitchUpDown2.h"
#include "xpln/obj/manipulators/AttrManipAxisKnob.h"
#include "xpln/obj/manipulators/embeddable/AttrAxisDetented.h"
#include "xpln/obj/manipulators/embeddable/AttrAxisDetentRange.h"
#include "xpln/obj/manipulators/embeddable/AttrManipKeyFrame.h"

namespace xobj {

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ObjReader::readFile(ImportContext & context, ObjReaderListener & listener) {
    ObjReader reader;
    listener.reset();
    reader.mObjParserListener = &listener;
    try {
        // todo this path converting will work incorrectly for UNICODE path.
        // It is a temporary solution.
        return reader.readFile(sts::toMbString(context.objFile()));
    }
    catch (std::exception & e) {
        ULFatal << e.what();
        return false;
    }
}

bool ObjReader::readFile(const std::string & filePath) const {
    ObjReadParser * parser = new ObjReadParser(filePath);
    if (!parser->isValid()) {
        delete parser;
        return false;
    }

    if (!readHeader(*parser)) {
        delete parser;
        return false;
    }

    size_t meshVertexCount = 0;
    size_t meshIdxCount = 0;
    size_t lineCount = 0;
    size_t liteCount = 0;
    bool gotCount = false;
    while (!parser->isEnd()) {
        if (readGlobalAttribute(*parser)) {
            continue;
        }
        if (readCounts(*parser, meshVertexCount, lineCount, liteCount, meshIdxCount)) {
            gotCount = true;
            break;
        }
        parser->nextLine();
    }
    if (!gotCount) {
        ULError << "Could not read vertices and faces counts from file.";
        delete parser;
        return false;
    }

    ObjMesh::VertexList vertices(meshVertexCount);
    ObjReaderListener::FaceIndexArray idx(meshIdxCount);
    ObjReaderListener::Index currVertIndex = 0;
    ObjReaderListener::Index currIndicesIndex = 0;

    while (!parser->isEnd()) {
        if (!readVertex(*parser, vertices, currVertIndex)) {
            readIndexes(*parser, idx, currIndicesIndex);
        }
        if (vertices.size() == currVertIndex && idx.size() == currIndicesIndex) {
            break;
        }
        parser->nextLine();
    }

    if (vertices.size() != currVertIndex) {
        ULError << "The obj file contains incorrect vertex count.";
        delete parser;
        return false;
    }

    if (idx.size() != currIndicesIndex) {
        ULError << "The obj file contains incorrect index count.";
        delete parser;
        return false;
    }

    mObjParserListener->gotMeshVertices(vertices);
    if (!idx.empty()) {
        if (idx.size() % 3) {
            ULError << "The obj file doesn't contain multiple of 3 index count.";
            return false;
        }
        mObjParserListener->gotMeshFaces(idx);
    }
    else {
        const ObjReaderListener::FaceIndexArray empty;
        mObjParserListener->gotMeshFaces(empty);
    }

    while (!parser->isEnd()) {
        if (readTris(*parser))
            goto next;
        if (readAttribute(*parser))
            goto next;
        if (readAnimBegin(*parser))
            goto next;
        if (readAnimEnd(*parser))
            goto next;
        if (readTranslateAnim(*parser))
            goto next;
        if (readRotateAnim(*parser))
            goto next;
        if (readTranslateKeysAnim(*parser))
            goto next;
        if (readRotateKeysAnim(*parser))
            goto next;
        if (readManipulators(*parser))
            goto next;
        if (readHideAnim(*parser))
            goto next;
        if (readShowAnim(*parser))
            goto next;
        if (readLod(*parser))
            goto next;
        if (readGlobalAttribute(*parser))
            goto next;
    next:
        parser->nextLine();
    }

    delete parser;
    mObjParserListener->gotFinished();
    return true;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

bool ObjReader::readHeader(ObjReadParser & parser) {
    // LINE 1: A/I - who cares?!?
    std::string str = parser.extractWord();
    if (str.empty() || (str[0] != 'A' && str[0] != 'I')) {
        ULError << "Header LINE 1 (PC type) is incorrect! Must be I or A.";
        return false;
    }
    parser.nextLine();

    // LINE 2: version
    const int vers = parser.extractInt();
    if (vers != 800) {
        ULError << "Header LINE 2 (Version) is incorrect! Must be 800.";
        return false;
    }
    parser.nextLine();

    // LINE 3: "OBJ"
    if (!parser.isMatch("OBJ")) {
        ULError << "Header LINE 3 (Identification) is incorrect! Must be \"OBJ\".";
        return false;
    }
    parser.nextLine();
    return true;
}

bool ObjReader::readCounts(ObjReadParser & parser,
                           size_t & outVertices,
                           size_t & outLines,
                           size_t & outLites,
                           size_t & outFaces) {
    // POINT_COUNTS tris lines lites geometry indices
    if (parser.isMatch(POINT_COUNTS)) {
        parser.skipSpace();
        outVertices = parser.extractInt();
        parser.skipSpace();
        outLines = parser.extractInt();
        parser.skipSpace();
        outLites = parser.extractInt();
        parser.skipSpace();
        outFaces = parser.extractInt();
        return true;
    }
    return false;
}

bool ObjReader::readVertex(ObjReadParser & parser, ObjMesh::VertexList & outVert, ObjReaderListener::FaceIndex & inOutIndex) {
    // VT <x> <y> <z> <nx> <ny> <nz> <s> <t>
    if (parser.isMatch(MESH_VT)) {
        parser.skipSpace();
        outVert[inOutIndex].mPosition.x = parser.extractFloat();
        parser.skipSpace();
        outVert[inOutIndex].mPosition.y = parser.extractFloat();
        parser.skipSpace();
        outVert[inOutIndex].mPosition.z = parser.extractFloat();

        parser.skipSpace();
        outVert[inOutIndex].mNormal.x = parser.extractFloat();
        parser.skipSpace();
        outVert[inOutIndex].mNormal.y = parser.extractFloat();
        parser.skipSpace();
        outVert[inOutIndex].mNormal.z = parser.extractFloat();

        parser.skipSpace();
        outVert[inOutIndex].mTexture.x = parser.extractFloat();
        parser.skipSpace();
        outVert[inOutIndex].mTexture.y = parser.extractFloat();

        ++inOutIndex;
        return true;
    }
    return false;
}

bool ObjReader::readIndexes(ObjReadParser & parser, ObjReaderListener::FaceIndexArray & outIndexes, ObjReaderListener::FaceIndex & inOUtIndex) {
    // IDX <n>
    if (parser.isMatch(MESH_IDX)) {
        parser.skipSpace();
        outIndexes[inOUtIndex] = parser.extractInt();
        ++inOUtIndex;
        return true;
    }
    // IDX10 <n> x 10
    if (parser.isMatch(MESH_IDX10)) {
        for (int n = 0; n < 10; ++n) {
            parser.skipSpace();
            outIndexes[inOUtIndex] = parser.extractInt();
            ++inOUtIndex;
        }
        return true;
    }
    return false;
}

bool ObjReader::readLod(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_LOD)) {
        parser.skipSpace();
        const float near = parser.extractFloat();
        parser.skipSpace();
        const float far = parser.extractFloat();
        parser.skipSpace();
        mObjParserListener->gotLod(near, far, parser.extractLineTilEol());
        return true;
    }
    return false;
}

bool ObjReader::readGlobalAttribute(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_GLOBAL_BLEND_GLASS)) {
        mObjParserListener->gotGlobAttrBlendGlass();
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_NORMAL_METALNESS)) {
        mObjParserListener->gotGlobAttrNormalMetalness();
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_TEXTURE)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrTexture(parser.extractWord());
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_TEXTURE_LIT)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrTextureLit(parser.extractWord());
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_TEXTURE_NORMAL)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrTextureNormal(parser.extractWord());
        return true;
    }

    if (parser.isMatch(ATTR_GLOBAL_WET)) {
        mObjParserListener->gotGlobAttrWetDry(AttrWetDry(AttrWetDry::wet));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_DRY)) {
        mObjParserListener->gotGlobAttrWetDry(AttrWetDry(AttrWetDry::dry));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_TINT)) {
        parser.skipSpace();
        const float albedo = parser.extractFloat();
        parser.skipSpace();
        const float emissive = parser.extractFloat();
        mObjParserListener->gotGlobAttrTint(AttrTint(albedo, emissive));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_TILTED)) {
        mObjParserListener->gotGlobAttrTilted();
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_NO_BLEND)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrBlend(AttrBlend(AttrBlend::no_blend, parser.extractFloat()));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_SPECULAR)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrSpecular(AttrSpecular(parser.extractFloat()));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_NO_SHADOW)) {
        mObjParserListener->gotGlobAttrNoShadow();
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_LOD_DRAPED)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrDrapedLod(AttrDrapedLod(parser.extractFloat()));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_COCKPIT_LIT)) {
        mObjParserListener->gotGlobAttrCockpitLit();
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_LAYER_GROUP)) {
        parser.skipSpace();
        std::string group = parser.extractWord();
        parser.skipSpace();
        const int offset = parser.extractInt();
        mObjParserListener->gotGlobAttrLayerGroup(AttrLayerGroup(ELayer::fromString(group.c_str()), offset));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_SLOPE_LIMIT)) {
        parser.skipSpace();
        const float minPitch = parser.extractFloat();
        parser.skipSpace();
        const float maxPitch = parser.extractFloat();
        parser.skipSpace();
        const float minRoll = parser.extractFloat();
        parser.skipSpace();
        const float maxRoll = parser.extractFloat();
        mObjParserListener->gotGlobAttrSlopeLimit(AttrSlopeLimit(minPitch, maxPitch, minRoll, maxRoll));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_SHADOW_BLEND)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrBlend(AttrBlend(AttrBlend::shadow_blend, parser.extractFloat()));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_COCKPIT_REGION)) {
        parser.skipSpace();
        const int32_t left = parser.extractInt();
        parser.skipSpace();
        const int32_t bottom = parser.extractInt();
        parser.skipSpace();
        const int32_t right = parser.extractInt();
        parser.skipSpace();
        const int32_t top = parser.extractInt();
        mObjParserListener->gotGlobAttrCockpitRegion(AttrCockpitRegion(left, bottom, right, top));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_SLUNG_LOAD_WEIGHT)) {
        parser.skipSpace();
        mObjParserListener->gotGlobAttrSlungLoadWeight(AttrSlungLoadWeight(parser.extractFloat()));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_LAYER_GROUP_DRAPED)) {
        parser.skipSpace();
        std::string group = parser.extractWord();
        parser.skipSpace();
        const int offset = parser.extractInt();
        mObjParserListener->gotGlobAttrLayerGroupDraped(AttrDrapedLayerGroup(ELayer::fromString(group.c_str()), offset));
        return true;
    }
    if (parser.isMatch(ATTR_GLOBAL_DEBUG)) {
        mObjParserListener->gotGlobAttrDebug();
        return true;
    }
    return false;
}

bool ObjReader::readAttribute(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_SHADOW)) {
        mObjParserListener->gotTrisAttrShadow(true);
        return true;
    }
    if (parser.isMatch(ATTR_NO_SHADOW)) {
        mObjParserListener->gotTrisAttrShadow(false);
        return true;
    }
    if (parser.isMatch(ATTR_DRAPED)) {
        mObjParserListener->gotTrisAttrDraped(true);
        return true;
    }
    if (parser.isMatch(ATTR_NO_DRAPED)) {
        mObjParserListener->gotTrisAttrDraped(false);
        return true;
    }
    if (parser.isMatch(ATTR_DRAW_ENABLE)) {
        mObjParserListener->gotTrisAttrDrawEnable(true);
        return true;
    }
    if (parser.isMatch(ATTR_DRAW_DISABLE)) {
        mObjParserListener->gotTrisAttrDrawEnable(false);
        return true;
    }
    if (parser.isMatch(ATTR_SOLID_CAMERA)) {
        mObjParserListener->gotTrisAttrSolidCamera(true);
        return true;
    }
    if (parser.isMatch(ATTR_NO_SOLID_CAMERA)) {
        mObjParserListener->gotTrisAttrSolidCamera(false);
        return true;
    }

    //-----------------

    if (parser.isMatch(ATTR_BLEND)) {
        parser.skipSpace();
        mObjParserListener->gotTrisAttrBlend(AttrBlend());
        return true;
    }
    if (parser.isMatch(ATTR_NO_BLEND)) {
        parser.skipSpace();
        mObjParserListener->gotTrisAttrBlend(AttrBlend(AttrBlend::no_blend, parser.extractFloat()));
        return true;
    }
    if (parser.isMatch(ATTR_SHADOW_BLEND)) {
        parser.skipSpace();
        mObjParserListener->gotTrisAttrBlend(AttrBlend(AttrBlend::shadow_blend, parser.extractFloat()));
        return true;
    }

    //-----------------

    if (parser.isMatch(ATTR_COCKPIT)) {
        mObjParserListener->gotTrisAttrCockpit(AttrCockpit(AttrCockpit::cockpit));
        return true;
    }
    if (parser.isMatch(ATTR_COCKPIT_REGION)) {
        parser.skipSpace();
        const int32_t region = parser.extractInt();
        switch (region) {
            case 0: mObjParserListener->gotTrisAttrCockpit(AttrCockpit(AttrCockpit::region_1));
                break;
            case 1: mObjParserListener->gotTrisAttrCockpit(AttrCockpit(AttrCockpit::region_2));
                break;
            case 2: mObjParserListener->gotTrisAttrCockpit(AttrCockpit(AttrCockpit::region_3));
                break;
            case 3: mObjParserListener->gotTrisAttrCockpit(AttrCockpit(AttrCockpit::region_4));
                break;
            default:
                LError << "Incorrect region number: " << region;
                mObjParserListener->gotTrisAttrCockpit(AttrCockpit());
                break;
        }
        return true;
    }
    if (parser.isMatch(ATTR_NO_COCKPIT)) {
        mObjParserListener->gotTrisAttrCockpit(AttrCockpit());
        return true;
    }

    //-----------------

    if (parser.isMatch(ATTR_HARD)) {
        parser.skipSpace();
        std::string surface = parser.extractWord();
        if (surface.empty()) {
            mObjParserListener->gotTrisAttrHard(AttrHard(ESurface(ESurface::none)));
        }
        else {
            mObjParserListener->gotTrisAttrHard(AttrHard(ESurface::fromString(surface.c_str())));
        }
        return true;
    }
    if (parser.isMatch(ATTR_HARD_DECK)) {
        parser.skipSpace();
        std::string surface = parser.extractWord();
        if (surface.empty()) {
            mObjParserListener->gotTrisAttrHard(AttrHard(ESurface(ESurface::none), true));
        }
        else {
            mObjParserListener->gotTrisAttrHard(AttrHard(ESurface::fromString(surface.c_str()), true));
        }
        return true;
    }
    if (parser.isMatch(ATTR_NO_HARD)) {
        mObjParserListener->gotTrisAttrHard(AttrHard());
        return true;
    }

    //-----------------

    if (parser.isMatch(ATTR_LIGHT_LEVEL)) {
        AttrLightLevel ll;
        parser.skipSpace();
        ll.setVal1(parser.extractFloat());
        parser.skipSpace();
        ll.setVal2(parser.extractFloat());
        parser.skipSpace();
        ll.setDataref(parser.extractWord());
        mObjParserListener->gotTrisAttrLightLevel(ll);
        return true;
    }

    if (parser.isMatch(ATTR_LIGHT_LEVEL_RESET)) {
        mObjParserListener->gotTrisAttrLightLevel(AttrLightLevel());
        return true;
    }

    //-----------------

    if (parser.isMatch(ATTR_POLY_OS)) {
        parser.skipSpace();
        const float offset = parser.extractFloat();
        if (sts::isEqual(0.0f, offset, 0.001f)) {
            mObjParserListener->gotTrisAttrPolyOffset(AttrPolyOffset());
        }
        else {
            mObjParserListener->gotTrisAttrPolyOffset(AttrPolyOffset(offset));
        }
        return true;
    }
    if (parser.isMatch(ATTR_SHINY_RAT)) {
        parser.skipSpace();
        mObjParserListener->gotTrisAttrShiny(AttrShiny(parser.extractFloat()));
        return true;
    }

    //-----------------

    if (parser.isMatch(ATTR_RESET)) {
        mObjParserListener->gotTrisAttrReset();
        return true;
    }
    return false;
}

bool ObjReader::readManipulators(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_MANIP_NONE)) {
        mObjParserListener->gotTrisAttrManipNo();
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_AXIS_KNOB)) {
        AttrManipAxisKnob m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setMinimum(parser.extractFloat());
        parser.skipSpace();
        m.setMaximum(parser.extractFloat());
        parser.skipSpace();
        m.setClickDelta(parser.extractFloat());
        parser.skipSpace();
        m.setHoldDelta(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_AXIS_SWITCH_LEFT_RIGHT)) {
        AttrManipAxisSwitchLeftRight m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setMinimum(parser.extractFloat());
        parser.skipSpace();
        m.setMaximum(parser.extractFloat());
        parser.skipSpace();
        m.setClickDelta(parser.extractFloat());
        parser.skipSpace();
        m.setHoldDelta(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_AXIS_SWITCH_UP_DOWN)) {
        AttrManipAxisSwitchUpDown m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setMinimum(parser.extractFloat());
        parser.skipSpace();
        m.setMaximum(parser.extractFloat());
        parser.skipSpace();
        m.setClickDelta(parser.extractFloat());
        parser.skipSpace();
        m.setHoldDelta(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND)) {
        AttrManipCmd m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setCmd(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND_AXIS)) {
        AttrManipCmdAxis m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setDirectionX(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionY(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionZ(parser.extractFloat());
        parser.skipSpace();
        m.setCmdPositive(parser.extractWord());
        parser.skipSpace();
        m.setCmdNegative(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND_KNOB)) {
        AttrManipCmdKnob m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setCmdPositive(parser.extractWord());
        parser.skipSpace();
        m.setCmdNegative(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND_KNOB2)) {
        AttrManipCmdKnob2 m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setCmd(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT)) {
        AttrManipCmdSwitchLeftRight m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setCmdPositive(parser.extractWord());
        parser.skipSpace();
        m.setCmdNegative(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND_SWITCH_LEFT_RIGHT2)) {
        AttrManipCmdSwitchLeftRight2 m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setCmd(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND_SWITCH_UP_DOWN)) {
        AttrManipCmdSwitchUpDown m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setCmdPositive(parser.extractWord());
        parser.skipSpace();
        m.setCmdNegative(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_COMMAND_SWITCH_UP_DOWN2)) {
        AttrManipCmdSwitchUpDown2 m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setCmd(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_DELTA)) {
        AttrManipDelta m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setDown(parser.extractFloat());
        parser.skipSpace();
        m.setHold(parser.extractFloat());
        parser.skipSpace();
        m.setMinimum(parser.extractFloat());
        parser.skipSpace();
        m.setMaximum(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_DRAG_AXIS)) {
        AttrManipDragAxis m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setDirectionX(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionY(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionZ(parser.extractFloat());
        parser.skipSpace();
        m.setVal1(parser.extractFloat());
        parser.skipSpace();
        m.setVal2(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_DRAG_ROTATE)) {
        AttrManipDragRotate m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setOriginX(parser.extractFloat());
        parser.skipSpace();
        m.setOriginY(parser.extractFloat());
        parser.skipSpace();
        m.setOriginZ(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionX(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionY(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionZ(parser.extractFloat());
        parser.skipSpace();
        m.setAngle1(parser.extractFloat());
        parser.skipSpace();
        m.setAngle2(parser.extractFloat());
        parser.skipSpace();
        m.setLift(parser.extractFloat());
        parser.skipSpace();
        m.setV1Min(parser.extractFloat());
        parser.skipSpace();
        m.setV1Max(parser.extractFloat());
        parser.skipSpace();
        m.setV2Min(parser.extractFloat());
        parser.skipSpace();
        m.setV2Max(parser.extractFloat());
        parser.skipSpace();
        m.setDataref1(parser.extractWord());
        parser.skipSpace();
        m.setDataref2(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_DRAG_AXIS_PIX)) {
        AttrManipDragAxisPix m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setDxPix(parser.extractInt());
        parser.skipSpace();
        m.setStep(parser.extractInt());
        parser.skipSpace();
        m.setExp(parser.extractFloat());
        parser.skipSpace();
        m.setVal1(parser.extractFloat());
        parser.skipSpace();
        m.setVal2(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_DRAG_XY)) {
        AttrManipDragXy m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setX(parser.extractFloat());
        parser.skipSpace();
        m.setY(parser.extractFloat());
        parser.skipSpace();
        m.setXMin(parser.extractFloat());
        parser.skipSpace();
        m.setXMax(parser.extractFloat());
        parser.skipSpace();
        m.setYMin(parser.extractFloat());
        parser.skipSpace();
        m.setYMax(parser.extractFloat());
        parser.skipSpace();
        m.setXDataref(parser.extractWord());
        parser.skipSpace();
        m.setYDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_NOOP)) {
        mObjParserListener->gotTrisAttrManip(AttrManipNoop());
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_PUSH)) {
        AttrManipPush m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setDown(parser.extractFloat());
        parser.skipSpace();
        m.setUp(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_RADIO)) {
        AttrManipRadio m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setDown(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_TOGGLE)) {
        AttrManipToggle m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setOn(parser.extractFloat());
        parser.skipSpace();
        m.setOff(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_WRAP)) {
        AttrManipWrap m;
        parser.skipSpace();
        m.setCursor(ECursor::fromString(parser.extractWord().c_str()));
        parser.skipSpace();
        m.setDown(parser.extractFloat());
        parser.skipSpace();
        m.setHold(parser.extractFloat());
        parser.skipSpace();
        m.setMinimum(parser.extractFloat());
        parser.skipSpace();
        m.setMaximum(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        parser.skipSpace();
        m.setToolTip(parser.extractWord());
        mObjParserListener->gotTrisAttrManip(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_WHEEL)) {
        AttrManipWheel m;
        m.setEnabled(true);
        parser.skipSpace();
        m.setDelta(parser.extractFloat());
        mObjParserListener->gotTrisAttrManipWheel(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_KEYFRAME)) {
        AttrManipKeyFrame m;
        parser.skipSpace();
        m.setValue(parser.extractFloat());
        parser.skipSpace();
        m.setAngle(parser.extractFloat());
        mObjParserListener->gotTrisAttrManipKeyFrame(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_AXIS_DETENTED)) {
        AttrAxisDetented m;
        m.setEnabled(true);
        parser.skipSpace();
        m.setDirectionX(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionY(parser.extractFloat());
        parser.skipSpace();
        m.setDirectionZ(parser.extractFloat());
        parser.skipSpace();
        m.setVMin(parser.extractFloat());
        parser.skipSpace();
        m.setVMax(parser.extractFloat());
        parser.skipSpace();
        m.setDataref(parser.extractWord());
        mObjParserListener->gotTrisAttrManipAxisDetented(m);
        return true;
    }
    if (parser.isMatch(ATTR_MANIP_AXIS_DETENT_RANGE)) {
        AttrAxisDetentRange m;
        parser.skipSpace();
        m.setStart(parser.extractFloat());
        parser.skipSpace();
        m.setEnd(parser.extractFloat());
        parser.skipSpace();
        m.setHeight(parser.extractFloat());
        mObjParserListener->gotTrisAttrManipAxisDetentRange(m);
        return true;
    }
    return false;
}

bool ObjReader::readTris(ObjReadParser & parser) const {
    if (parser.isMatch(MESH_TRIS)) {
        parser.skipSpace();
        const ObjReaderListener::Index pos = parser.extractInt();
        parser.skipSpace();
        const ObjReaderListener::Index count = parser.extractInt();
        parser.skipSpace();
        mObjParserListener->gotTris(pos, count, parser.extractLineTilEol());
        return true;
    }
    return false;
}

bool ObjReader::readAnimBegin(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_ANIM_BEGIN)) {
        mObjParserListener->gotAnimBegin();
        return true;
    }
    return false;
}

bool ObjReader::readAnimEnd(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_ANIM_END)) {
        mObjParserListener->gotAnimEnd();
        return true;
    }
    return false;
}

bool ObjReader::readAnimLoop(ObjReadParser & parser, float & outVal) {
    parser.pushPosition();
    parser.skipUntillParam();
    if (!parser.isMatch(ANIM_KEYFRAME_LOOP)) {
        parser.popPosition(true);
        return false;
    }
    parser.popPosition(false);
    parser.skipSpace();
    outVal = parser.extractFloat();
    return true;
}

bool ObjReader::readHideAnim(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_ANIM_HIDE)) {
        AnimVisibility::Key k;
        k.mType = AnimVisibility::Key::HIDE;
        parser.skipSpace();
        k.mValue1 = parser.extractFloat();
        parser.skipSpace();
        k.mValue2 = parser.extractFloat();
        parser.skipSpace();
        k.mDrf = parser.extractWord();
        mObjParserListener->gotAnimHide(k);
        return true;
    }
    return false;
}

bool ObjReader::readShowAnim(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_ANIM_SHOW)) {
        AnimVisibility::Key k;
        k.mType = AnimVisibility::Key::SHOW;
        parser.skipSpace();
        k.mValue1 = parser.extractFloat();
        parser.skipSpace();
        k.mValue2 = parser.extractFloat();
        parser.skipSpace();
        k.mDrf = parser.extractWord();
        mObjParserListener->gotAnimShow(k);
        return true;
    }
    return false;
}

bool ObjReader::readTranslateAnim(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_TRANS)) {
        AnimTrans::KeyList keys(2);
        parser.skipSpace();
        keys[0].mPosition.x = parser.extractFloat();
        parser.skipSpace();
        keys[0].mPosition.y = parser.extractFloat();
        parser.skipSpace();
        keys[0].mPosition.z = parser.extractFloat();

        parser.skipSpace();
        keys[1].mPosition.x = parser.extractFloat();
        parser.skipSpace();
        keys[1].mPosition.y = parser.extractFloat();
        parser.skipSpace();
        keys[1].mPosition.z = parser.extractFloat();

        parser.skipSpace();
        keys[0].mDrfValue = parser.extractFloat();
        parser.skipSpace();
        keys[1].mDrfValue = parser.extractFloat();

        if (keys[0].mPosition == keys[1].mPosition) {
            keys.pop_back();
        }

        parser.skipSpace();
        std::string dataref = parser.extractWord();
        if (dataref == DATAREF_DEFAULT_VAL) {
            dataref.clear();
        }

        float loopVal = 0.0f;
        const bool hasLoop = readAnimLoop(parser, loopVal);
        mObjParserListener->gotTranslateAnim(keys, dataref, hasLoop ? std::optional<float>(loopVal) : std::nullopt);
        return true;
    }
    return false;
}

bool ObjReader::readRotateAnim(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_ROTATE)) {
        float vector[3];
        parser.skipSpace();
        vector[0] = parser.extractFloat();
        parser.skipSpace();
        vector[1] = parser.extractFloat();
        parser.skipSpace();
        vector[2] = parser.extractFloat();

        AnimRotate::KeyList keys(2);
        parser.skipSpace();
        keys[0].mAngleDegrees = parser.extractFloat();
        parser.skipSpace();
        keys[1].mAngleDegrees = parser.extractFloat();

        parser.skipSpace();
        keys[0].mDrfValue = parser.extractFloat();
        parser.skipSpace();
        keys[1].mDrfValue = parser.extractFloat();

        if (sts::isEqual(keys[0].mAngleDegrees, keys[1].mAngleDegrees) ||
            sts::isEqual(keys[0].mDrfValue, keys[1].mDrfValue)) {
            keys.pop_back();
        }

        parser.skipSpace();
        std::string dataref = parser.extractWord();
        if (dataref == DATAREF_DEFAULT_VAL)
            dataref.clear();

        float loopVal = 0.0f;
        const bool hasLoop = readAnimLoop(parser, loopVal);
        mObjParserListener->gotRotateAnim(keys, vector, dataref, hasLoop ? std::optional<float>(loopVal) : std::nullopt);
        return true;
    }
    return false;
}

bool ObjReader::readTranslateKeysAnim(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_TRANS_BEGIN)) {
        parser.skipSpace();
        std::string dataref = parser.extractWord();
        if (dataref == DATAREF_DEFAULT_VAL)
            dataref.clear();
        parser.nextLine();

        AnimTrans::KeyList keys;
        while (!parser.isEnd() && parser.isMatch(ATTR_TRANS_KEY)) {
            keys.emplace_back();
            parser.skipSpace();
            keys.back().mDrfValue = parser.extractFloat();
            parser.skipSpace();
            keys.back().mPosition.x = parser.extractFloat();
            parser.skipSpace();
            keys.back().mPosition.y = parser.extractFloat();
            parser.skipSpace();
            keys.back().mPosition.z = parser.extractFloat();
            parser.nextLine();
        }

        if (parser.isMatch(ATTR_TRANS_END)) {
            float loopVal = 0.0f;
            const bool hasLoop = readAnimLoop(parser, loopVal);
            mObjParserListener->gotTranslateAnim(keys, dataref, hasLoop ? std::optional<float>(loopVal) : std::nullopt);
        }
        else {
            ULError << "Incorrect translate key animation.";
        }

        return true;
    }
    return false;
}

bool ObjReader::readRotateKeysAnim(ObjReadParser & parser) const {
    if (parser.isMatch(ATTR_ROTATE_BEGIN)) {
        float vector[3];
        parser.skipSpace();
        vector[0] = parser.extractFloat();
        parser.skipSpace();
        vector[1] = parser.extractFloat();
        parser.skipSpace();
        vector[2] = parser.extractFloat();

        parser.skipSpace();
        std::string dataref = parser.extractWord();
        if (dataref == DATAREF_DEFAULT_VAL)
            dataref.clear();
        parser.nextLine();

        AnimRotate::KeyList keys;
        while (!parser.isEnd() && parser.isMatch(ATTR_ROTATE_KEY)) {
            keys.emplace_back();
            parser.skipSpace();
            keys.back().mDrfValue = parser.extractFloat();
            parser.skipSpace();
            keys.back().mAngleDegrees = parser.extractFloat();
            parser.nextLine();
        }

        if (parser.isMatch(ATTR_ROTATE_END)) {
            float loopVal = 0.0f;
            const bool hasLoop = readAnimLoop(parser, loopVal);
            mObjParserListener->gotRotateAnim(keys, vector, dataref, hasLoop ? std::optional<float>(loopVal) : std::nullopt);
        }
        else {
            ULError << "Incorrect rotate key animation.";
        }

        return true;
    }
    return false;
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
