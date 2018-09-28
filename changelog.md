StepToSky: X-Plane Obj Library
---------------------------------------------------------------------------
#### Next

- **Added** Ability to use tool-tip in ATTR_manip_noop.
- **Added** Ability to use text variables in the param light's parameters string.
- **Fixed** Sorting algorithm for LODs.

##### Breaking backward compatibility
- **Changes:** Methods for accessing to the LODs.
- **Changes:** Changed named light's methods.
- **Changes:** Changed param light's methods.
- **Changes:** Changed Transform's methods.
- **Changes:** Draped geometry got its own class and attribute set.
- **Removed:** ELightNamed and ELightParams. 
               For getting light names use `X-Plane Root/Resources/bitmaps/world/lites/lights.txt`
 
---------------------------------------------------------------------------
#### 0.6.2-beta (31.08.2018)

- **Updated** Some manipulators UI text to be shorter.
- **Fixed** The library signature printing.
- **Fixed** Some items converting to string in `EManipulator`.

---------------------------------------------------------------------------
#### 0.6.1-beta (30.08.2018)

- **Changed** Enabling policy for `AttrAxisDetented` and `AttrManipWheel` manipulators.  

---------------------------------------------------------------------------
#### 0.6.0-beta (30.08.2018)

- **Added:** Ability to specifying strings that are printed before and after object.  
             This allows you to use new attributes manually until
             it is supported by the library or writing notes.
             This can be applied to any object types.
- **Added:** New manipulators:  
             `ATTR_manip_command_switch_left_right2`,  
             `ATTR_manip_command_switch_up_down2`,  
             `ATTR_manip_command_knob2`,  
             `ATTR_manip_drag_rotate`,  
             `ATTR_axis_detented`,  
             `ATTR_axis_detent_range`,  
             `ATTR_manip_keyframe`
- **Updated:** Some methods of manipulators were renamed/corrected according to .the obj specification. The old ones got the deprecated attribute.
- **Updated:** Building scripts and their documentation.
- **Fixed:** Printing incorrect attribute name for the
             `ATTR_manip_command_switch_up_down` and `ATTR_manip_command_switch_left_right`.
##### Breaking backward compatibility
- **Changes:** The wheel manipulator is composed now.  

---------------------------------------------------------------------------
#### 0.5.0-beta (05.10.2017)

- **Added:** Error if any LOD except the first one contains hard polygons.
- **Added:** Auto-flip normals for objects with mirrored transformation.
- **Fixed:** Creating two sided mesh.
- **Fixed:** Printing custom name of the `LIGHT_PARAM`.

---------------------------------------------------------------------------
#### 0.4.1-beta (24.08.2017)

- **Added:** Printing error if texture name contains illegal symbols.
- **Improved:** Build scripts.
- **Fixed:** Build scripts.

---------------------------------------------------------------------------
#### 0.4.0-beta (17.06.2017)

- **Added:** Smoke object printing. Although there was the smoke object before, 
             it could not be used. So it can be used now.
- **Added:** Export option for the smoke marking `XOBJ_EXP_MARK_SMOKE`.
- **Added:** Panel-Click manipulator. This manipulator should be used for 
             the cockpit geometry (`ATTR_cockpit`) when 
             you want to enable the panel manipulators.
- **Added:** Jenkins pipeline script.
- **Fixed:** Manipulators' state machine. There were some problems in the state machine 
             one of them could lead to undefined behavior it was fixed now, also 
             there was changed the default behavior. 
             By default all the manipulators are **disabled now**, 
             so you must put the manipulator to the objects explicitly.

---------------------------------------------------------------------------
#### 0.3.1-beta (16.05.2017)

- **Added:** Loop animation for the visibility keys.
- **Fixed:** Loop animation printing.

---------------------------------------------------------------------------