StepToSky: X-Plane Obj Library
---------------------------------------------------------------------------
#### next

- **Added** Particle system support.
- **Added** Constraint for macos deployment target - 10.14, because of [error: call to unavailable function 'visit': introduced in macOS 10.14 std::visit].
- **Added** Checking if a normal map is specified but the attributes GLOBAL_specular or ATTR_shiny_rat aren't set.
- **Added** Checking if the ATTR_cockpit_device doesn't have a device name.
- **Added** Checking if mesh has the attribute ATTR_cockpit_region but the attribute COCKPIT_REGION isn't set.
- **Added** Helper for converting quaternion sequence to animation rotate.
- **Added** Parser for the [X-Plane Root/Resources/bitmaps/world/lites/lights.txt] file.
- **Fixed** Normals of mirrored objects.

##### Breaking backward compatibility:
- **Changed** Code style: public variable now have the prefix m instead of p.
- **Changed** Attribute sets use std::optional now.
- **Changed** Tree attribute location. It is presented as a parameter of the mesh object now.
- **Changed** Manipulator use std::variant for its type now.
- **Removed** `enable/disable` flags from the attributes as the std::option is used.

---------------------------------------------------------------------------
#### 0.9.0-beta (27.11.2018)
##### Breaking backward compatibility:
- **Changed** Custom DataRefs and Commands format. The symbol ':' must immediate fallow ID.

---------------------------------------------------------------------------
#### 0.8.0-beta (25.10.2018)

- **Added** Classes for reading/writing datarefs and commands files.
- **Added** Context for importing/exporting.
- **Fixed** Fixed bug for attribute printing:  
            `AttrShiny`  
            `AttrBlend`  
            Default/disabled values were not printed when those attributes were enabled and then disabled.

##### Breaking backward compatibility:
- **Changed:** Methods for export/import in ObjMain.
- **Changed:** Under windows (MSVC) `std::wstring` is used as a path.
- **Removed:** Signature methods from the `ExportOptions`. Those methods are in the `ExportContext` now.

---------------------------------------------------------------------------
#### 0.7.0-beta (10.10.2018)

- **Added** Ability to use tool-tip in ATTR_manip_noop.
- **Added** Ability to use text variables in the param light's parameters string.
- **Added** ATTR_cockpit_device attribute.
- **Fixed** Sorting algorithm for LODs.

##### Breaking backward compatibility:
- **Changed:** Methods for accessing to the LODs.
- **Changed:** Changed named light's methods.
- **Changed:** Changed param light's methods.
- **Changed:** Changed Transform's methods.
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