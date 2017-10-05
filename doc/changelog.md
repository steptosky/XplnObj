
X-Plane Obj Library
---------------------------------------------------------------------------
#### Next

- **Added:** Auto-flip normals for objects with mirrored transformation.
- **Fixed:** Creating two sided mesh.
- **Fixed:** Printing custom name of the LIGHT_PARAM.

---------------------------------------------------------------------------
#### 0.4.1-beta (24.08.2017)

- **Added:** Printing error if texture name contains illegal symbols.
- **Improved:** Build scripts.
- **Fixed:** Build scripts.

---------------------------------------------------------------------------
#### 0.4.0-beta (17.06.2017)

- **Added:** Smoke object printing. Although there was the smoke object before, 
             it could not be used. So it can be used now.
- **Added:** Export option for the smoke marking XOBJ_EXP_MARK_SMOKE.
- **Added:** Panel-Click manipulator. This manipulator should be used for 
             the cockpit geometry (ATTR_cockpit) when 
             you want to enable the panel manipulators.
- **Added:** Jenkins pipeline script.
- **Fixed:** Manipulators' state machine. There were some problems in the state machine 
             one of them could lead to undefined behavior it was fixed now, also 
             there was changed the default behaviour. 
             By default all the manipulators sre **disabled now**, 
             so you must put the manipulator to the objects explicitly.

---------------------------------------------------------------------------
#### 0.3.1-beta (16.05.2017)

- **Added:** Loop animation for the visisbility keys.
- **Fixed:** Loop animation printing.

---------------------------------------------------------------------------