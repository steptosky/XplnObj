#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
#
#  Copyright (C) 2017, StepToSky
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

set(PROJECT ${ProjectId})
project(${PROJECT} VERSION ${ProjectVersion} LANGUAGES "CXX")

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

add_library(${PROJECT} ${CM_FILES})

#----------------------------------------------------------------------------------#
# linkage 

target_include_directories(${PROJECT} 
	PRIVATE "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
	PRIVATE "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>"
	PUBLIC  "$<INSTALL_INTERFACE:include>"
)	
		
#----------------------------------------------------------------------------------#
# compile options

target_compile_options(${PROJECT} 
	PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/W4>"
	PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:-D_CRT_SECURE_NO_WARNINGS>"
	
	PUBLIC "$<$<CXX_COMPILER_ID:AppleClang>:-std=c++1y>"
	PUBLIC  "$<$<CXX_COMPILER_ID:AppleClang>:-stdlib=libc++>"
	PRIVATE "$<$<CXX_COMPILER_ID:AppleClang>:-Wno-unknown-pragmas>"
	PRIVATE "$<$<CXX_COMPILER_ID:AppleClang>:-pedantic>"
	
	PUBLIC "$<$<CXX_COMPILER_ID:Clang>:-std=c++1y>"
	PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-Wno-unknown-pragmas>"
	PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-pedantic>"
	
	PUBLIC "$<$<CXX_COMPILER_ID:GNU>:-std=c++1y>"
	PRIVATE "$<$<CXX_COMPILER_ID:GNU>:-Wno-unknown-pragmas>"
	PRIVATE "$<$<CXX_COMPILER_ID:GNU>:-pedantic>"
)

#----------------------------------------------------------------------------------#
# installation

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/" DESTINATION "include") 
install(TARGETS ${PROJECT} EXPORT ${PROJECT} DESTINATION "$<CONFIG>")
install(EXPORT ${PROJECT} NAMESPACE "${PROJECT}::" 
	DESTINATION "cmake" FILE "${PROJECT}Config.cmake"
)

export(EXPORT ${PROJECT} NAMESPACE "${PROJECT}::" 
	FILE "${CMAKE_SOURCE_DIR}/output-dev/${PROJECT}Config.cmake"
)
export(PACKAGE ${PROJECT})

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# export header file

include(GenerateExportHeader)
generate_export_header(${PROJECT} 
	EXPORT_MACRO_NAME "XpObjLib" 
	EXPORT_FILE_NAME ${CMAKE_SOURCE_DIR}/include/xpln/XplnObjExport.h
	DEPRECATED_MACRO_NAME "XpObjLibDeprecated"
	STATIC_DEFINE "XPLN_OBJ_STATIC_COMPILATION"
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#