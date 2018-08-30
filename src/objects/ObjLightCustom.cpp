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

#include "xpln/obj/ObjLightCustom.h"
#include "xpln/obj/Transform.h"

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////* Constructors/Destructor */////////////////////////////////////
/**************************************************************************************************/

ObjLightCustom::ObjLightCustom(const ObjLightCustom & copy)
    : ObjAbstractLight(copy),
      mColor(copy.mColor),
      mSize(copy.mSize),
      mTexture(copy.mTexture),
      mDataRef(copy.mDataRef) {}

ObjLightCustom::ObjLightCustom()
    : mSize(10.0f),
      mTexture(Point2(0.0f, 0.0f), Point2(1.0f, 1.0f)) {
    setObjectName("Light Custom");
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

void ObjLightCustom::applyTransform(const TMatrix & tm, const bool) {
    Point3 pos = mPosition;
    tm.transformPoint(pos);
    mPosition = pos;
}

/**************************************************************************************************/
///////////////////////////////////////////* Functions *////////////////////////////////////////////
/**************************************************************************************************/

eObjectType ObjLightCustom::objType() const {
    return OBJ_LIGHT_CUSTOM;
}

RectangleI ObjLightCustom::textureRect() const {
    return mTexture;
}

float ObjLightCustom::size() const {
    return mSize;
}

void ObjLightCustom::setSize(float size) {
    mSize = size;
}

Color ObjLightCustom::color() const {
    return mColor;
}

void ObjLightCustom::setColor(const Color & color) {
    mColor = color;
}

const std::string & ObjLightCustom::dataRef() const {
    return mDataRef;
}

void ObjLightCustom::setDataRef(const std::string & dataRef) {
    mDataRef = dataRef;
}

void ObjLightCustom::setTextureRect(const RectangleI & textureRect) {
    mTexture = textureRect;
}

/**************************************************************************************************/
//////////////////////////////////////////* Functions */////////////////////////////////////////////
/**************************************************************************************************/

ObjAbstract * ObjLightCustom::clone() const {
    return new ObjLightCustom(*this);
}

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
