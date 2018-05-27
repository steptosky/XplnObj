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

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/

#define DATAREF_DEFAULT_VAL "none"

#define POINT_COUNTS "POINT_COUNTS"

// objects
#define LINES "LINES"
#define VLINE "VLINE"
#define LIGHTS "LIGHTS"
#define VLIGHT "VLIGHT"
#define LIGHT_CUSTOM "LIGHT_CUSTOM"
#define LIGHT_NAMED "LIGHT_NAMED"
#define LIGHT_PARAM "LIGHT_PARAM"
#define LIGHT_SPILL_CUSTOM "LIGHT_SPILL_CUSTOM"
#define SMOKE_BLACK "smoke_black"
#define SMOKE_WHITE "smoke_white"

// objects' parts
#define MESH_VT "VT"
#define MESH_IDX "IDX"
#define MESH_TRIS "TRIS"
#define MESH_IDX10 "IDX10"

// global attributes
#define ATTR_GLOBAL_DEBUG "DEBUG"
#define ATTR_GLOBAL_WET "REQUIRE_WET"
#define ATTR_GLOBAL_DRY "REQUIRE_DRY"
#define ATTR_GLOBAL_TINT "GLOBAL_tint"
#define ATTR_GLOBAL_TILTED "TILTED"
#define ATTR_GLOBAL_TEXTURE "TEXTURE"
#define ATTR_GLOBAL_NO_BLEND "GLOBAL_no_blend"
#define ATTR_GLOBAL_SPECULAR "GLOBAL_specular"
#define ATTR_GLOBAL_NO_SHADOW "GLOBAL_no_shadow"
#define ATTR_GLOBAL_LOD_DRAPED "ATTR_LOD_draped"
#define ATTR_GLOBAL_COCKPIT_LIT "GLOBAL_cockpit_lit"
#define ATTR_GLOBAL_TEXTURE_LIT "TEXTURE_LIT"
#define ATTR_GLOBAL_LAYER_GROUP "ATTR_layer_group"
#define ATTR_GLOBAL_SLOPE_LIMIT "SLOPE_LIMIT"
#define ATTR_GLOBAL_BLEND_GLASS "BLEND_GLASS"
#define ATTR_GLOBAL_SHADOW_BLEND "GLOBAL_shadow_blend"
#define ATTR_GLOBAL_TEXTURE_NORMAL "TEXTURE_NORMAL"
#define ATTR_GLOBAL_COCKPIT_REGION "COCKPIT_REGION"
#define ATTR_GLOBAL_NORMAL_METALNESS "NORMAL_METALNESS"
#define ATTR_GLOBAL_SLUNG_LOAD_WEIGHT "slung_load_weight"
#define ATTR_GLOBAL_LAYER_GROUP_DRAPED "ATTR_layer_group_draped"

// object attributes
#define ATTR_LOD "ATTR_LOD"
#define ATTR_HARD "ATTR_hard"
#define ATTR_BLEND "ATTR_blend"
#define ATTR_SHADOW "ATTR_shadow"
#define ATTR_DRAPED "ATTR_draped"
#define ATTR_COCKPIT "ATTR_cockpit"
#define ATTR_POLY_OS "ATTR_poly_os"
#define ATTR_NO_HARD "ATTR_no_hard"
#define ATTR_NO_BLEND "ATTR_no_blend"
#define ATTR_SHINY_RAT "ATTR_shiny_rat"
#define ATTR_NO_DRAPED "ATTR_no_draped"
#define ATTR_HARD_DECK "ATTR_hard_deck"
#define ATTR_NO_SHADOW "ATTR_no_shadow"
#define ATTR_NO_COCKPIT "ATTR_no_cockpit"
#define ATTR_LIGHT_LEVEL "ATTR_light_level"
#define ATTR_DRAW_ENABLE "ATTR_draw_enable"
#define ATTR_DRAW_DISABLE "ATTR_draw_disable"
#define ATTR_SHADOW_BLEND "ATTR_shadow_blend"
#define ATTR_SOLID_CAMERA "ATTR_solid_camera"
#define ATTR_COCKPIT_REGION "ATTR_cockpit_region"
#define ATTR_NO_SOLID_CAMERA "ATTR_no_solid_camera"
#define ATTR_LIGHT_LEVEL_RESET "ATTR_light_level_reset"
#define ATTR_RESET "ATTR_reset"

// use these only for reading because these are depricated and should not be used for export
#define ATTR_AMBIENT_RGB "ATTR_ambient_rgb" // deprecated and ignored
#define ATTR_SPECULAR_RGB "ATTR_specular_rgb" // deprecated and ignored
#define ATTR_EMISSION_RGB "ATTR_emission_rgb"
#define ATTR_SHADE_FLAT "ATTR_shade_flat"
#define ATTR_SHADE_SMOOTH "ATTR_shade_smooth"
#define ATTR_NO_DEPTH "ATTR_no_depth"
#define ATTR_DEPTH "ATTR_depth"
#define ATTR_NO_CULL "ATTR_no_cull"
#define ATTR_CULL "ATTR_cull"

// manips
#define ATTR_MANIP_NONE "ATTR_manip_none"
#define ATTR_MANIP_WRAP "ATTR_manip_wrap"
#define ATTR_MANIP_PUSH "ATTR_manip_push"
#define ATTR_MANIP_NOOP "ATTR_manip_noop"
#define ATTR_MANIP_WHEEL "ATTR_manip_wheel"
#define ATTR_MANIP_DELTA "ATTR_manip_delta"
#define ATTR_MANIP_RADIO "ATTR_manip_radio"
#define ATTR_MANIP_TOGGLE "ATTR_manip_toggle"
#define ATTR_MANIP_COMMAND "ATTR_manip_command"
#define ATTR_MANIP_DRAG_XY "ATTR_manip_drag_xy"
#define ATTR_MANIP_AXIS_KNOB "ATTR_manip_axis_knob"
#define ATTR_MANIP_DRAG_AXIS "ATTR_manip_drag_axis"
#define ATTR_MANIP_COMMAND_AXIS "ATTR_manip_command_axis"
#define ATTR_MANIP_COMMAND_KNOB "ATTR_manip_command_knob"
#define ATTR_MANIP_DRAG_AXIS_PIX "ATTR_manip_drag_axis_pix"
#define ATTR_MANIP_SWITCH_UP_DOWN "ATTR_manip_switch_up_down"
#define ATTR_MANIP_SWITCH_LEFT_RIGHT "ATTR_manip_switch_left_right"
#define ATTR_MANIP_AXIS_SWITCH_UP_DOWN "ATTR_manip_axis_switch_up_down"
#define ATTR_MANIP_AXIS_SWITCH_LEFT_RIGHT "ATTR_manip_axis_switch_left_right"

// animation
#define ATTR_TRANS "ANIM_trans"
#define ATTR_ROTATE "ANIM_rotate"
#define ATTR_ANIM_END "ANIM_end"
#define ATTR_ANIM_HIDE "ANIM_hide"
#define ATTR_ANIM_SHOW "ANIM_show"
#define ATTR_TRANS_KEY "ANIM_trans_key"
#define ATTR_TRANS_END "ANIM_trans_end"
#define ATTR_ROTATE_KEY "ANIM_rotate_key"
#define ATTR_ROTATE_END "ANIM_rotate_end"
#define ATTR_ANIM_BEGIN "ANIM_begin"
#define ATTR_TRANS_BEGIN "ANIM_trans_begin"
#define ATTR_ROTATE_BEGIN "ANIM_rotate_begin"
#define ANIM_KEYFRAME_LOOP "ANIM_keyframe_loop"

/**************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************/
