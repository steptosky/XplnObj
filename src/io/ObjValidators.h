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

#include "xpln/Export.h"
#include <string>

namespace xobj {

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ObjAbstract;
class ObjDummy;
class ObjLine;
class ObjLodGroup;
class ObjMain;
class ObjMesh;
class ObjSmoke;

class AttrGlobSet;

/*!
 * \details Hard polygons can only be used in the first LOD.
 *          So algorithms have to use this function to 
 *          check whether the object contains a hard polygons attribute.
 *          This function also prints information to the log
 *          if specified object contains a hard polygons attribute.
 * \param baseObj 
 * \param lodName 
 * \return True if specified object contains a hard polygons attribute, otherwise false.
 */
XpObjLib bool findHardPolygons(const ObjAbstract & baseObj, const std::string & lodName);

XpObjLib bool checkParameters(const AttrGlobSet & attrSet, const std::string & prefix);
XpObjLib bool checkParameters(const ObjAbstract & baseObj, const std::string & prefix);
XpObjLib bool checkParameters(const ObjDummy & obj, const std::string & prefix);
XpObjLib bool checkParameters(const ObjLine & obj, const std::string & prefix);
XpObjLib bool checkParameters(const ObjLodGroup & lodObj, const std::string & prefix);
XpObjLib bool checkParameters(const ObjMain & mainObj, const std::string & prefix);
XpObjLib bool checkParameters(const ObjMesh & obj, const std::string & prefix);
XpObjLib bool checkParameters(const ObjSmoke & obj, const std::string & prefix);

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class Transform;

XpObjLib bool checkParameters(const Transform & transform, const std::string & prefix);

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class AnimVisibilityKey;
class AnimTrans;
class AnimTransKey;
class AnimRotate;

XpObjLib bool checkParameters(const AnimVisibilityKey & key, const std::string & prefix);
XpObjLib bool checkParameters(const AnimTrans & anim, const std::string & prefix);
XpObjLib bool checkParameters(const AnimTransKey & key, const std::string & prefix);
XpObjLib bool checkParameters(const AnimRotate & anim, const std::string & prefix);

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

class ObjLightCustom;
class ObjLightNamed;
class ObjLightParam;
class ObjLightPoint;
class ObjLightSpillCust;

XpObjLib bool checkParameters(const ObjLightCustom & inVal, const std::string & inPrefix);
XpObjLib bool checkParameters(const ObjLightNamed & inVal, const std::string & inPrefix);
XpObjLib bool checkParameters(const ObjLightParam & inVal, const std::string & inPrefix);
XpObjLib bool checkParameters(const ObjLightPoint & inVal, const std::string & inPrefix);
XpObjLib bool checkParameters(const ObjLightSpillCust & inVal, const std::string & inPrefix);

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

}
