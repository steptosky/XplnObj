#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
#
#  Copyright (C) 2018, StepToSky
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  1.Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#  2.Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and / or other materials provided with the distribution.
#  3.Neither the name of StepToSky nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
#  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  Contacts: www.steptosky.com
#
#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# project

cmake_minimum_required (VERSION 3.14.3)

set(TARGET ${ProjectId})
project(${TARGET} VERSION ${ProjectVersion} LANGUAGES "CXX")

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# project files

file(GLOB_RECURSE CM_FILES 
    "*.h" "*.inl" "*.cpp" 
    "${CMAKE_SOURCE_DIR}/include/*.h" 
    "${CMAKE_SOURCE_DIR}/include/*.inl" 
    "${CMAKE_SOURCE_DIR}/include/*.cpp"
)

include(StsGroupFiles)
groupFiles("${CM_FILES}")

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# targets

add_library(${TARGET} ${CM_FILES})

#----------------------------------------------------------------------------------#
# cxx standard 

set_target_properties(${TARGET} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
target_compile_features(${TARGET} PUBLIC cxx_std_17)

#----------------------------------------------------------------------------------#
# linkage 

target_include_directories(${TARGET} 
    PRIVATE "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    PRIVATE "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>"
    PUBLIC  "$<INSTALL_INTERFACE:include>"
)

#----------------------------------------------------------------------------------#
# compile options

# pre-compile headers
set_source_files_properties(stdafx.cpp
    PROPERTIES COMPILE_FLAGS $<$<CXX_COMPILER_ID:MSVC>:/Yc>
)

target_compile_options(${TARGET} 
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/Yustdafx.h>  # pre-compile headers
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/FIstdafx.h>  # pre-compile headers
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/MP>          # multi-processor compilation
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:-D_CRT_SECURE_NO_WARNINGS>

    PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-Wno-unknown-pragmas>
    PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-pedantic -Werror>

    PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wno-unknown-pragmas>
    PRIVATE $<$<CXX_COMPILER_ID:Clang>:-pedantic -Werror>

    PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wno-unknown-pragmas>
    PRIVATE $<$<CXX_COMPILER_ID:GNU>:-pedantic -Werror>
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# installation

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/" DESTINATION "include")
install(TARGETS ${TARGET} EXPORT ${TARGET} DESTINATION "$<CONFIG>")
install(EXPORT ${TARGET} NAMESPACE "${ProjectGroupId}::" 
    DESTINATION "cmake" FILE "${TARGET}Config.cmake"
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# export header file

include(GenerateExportHeader)
generate_export_header(${TARGET} 
    EXPORT_MACRO_NAME "XpObjLib" 
    EXPORT_FILE_NAME ${CMAKE_SOURCE_DIR}/include/xpln/Export.h
    DEPRECATED_MACRO_NAME "XpObjLibDeprecated"
    STATIC_DEFINE "XPLN_OBJ_STATIC_COMPILATION"
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#