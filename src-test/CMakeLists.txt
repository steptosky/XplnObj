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

cmake_minimum_required (VERSION 3.7.0)

set(TARGET test-${ProjectId})
project(${TARGET} VERSION ${ProjectVersion} LANGUAGES "CXX")

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# project files

file(GLOB_RECURSE CM_FILES 
    "*.h" "*.inl" "*.cpp"
)
include(StsGroupFiles)
groupFiles("${CM_FILES}")

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# targets 

add_executable(${TARGET} ${CM_FILES})
add_dependencies(${TARGET} ${ProjectId})
add_definitions(-DTESTING)

#----------------------------------------------------------------------------------#
# linkage 

target_include_directories(${TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(${TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/src-test")

target_link_libraries(${TARGET} ${ProjectId})
target_link_libraries(${TARGET} CONAN_PKG::gtest)

#----------------------------------------------------------------------------------#
# compile options

# pre-compile headers
set_source_files_properties(ph/stdafx.cpp
    PROPERTIES COMPILE_FLAGS $<$<CXX_COMPILER_ID:MSVC>:/Yc>
)

target_compile_options(${TARGET}
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/Yuph/stdafx.h>   # pre-compile headers
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/FIph/stdafx.h>   # pre-compile headers
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/MP4>             # multi-processor compilation
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
# copying the dynamic library

add_custom_command(TARGET ${TARGET} 
    POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -E copy_if_different 
    "$<TARGET_FILE:${ProjectId}>" "$<TARGET_FILE_DIR:${TARGET}>"
)

set_target_properties(${TARGET}
    PROPERTIES
    INSTALL_RPATH $<$<PLATFORM_ID:Darwin>:"@executable_path">
    INSTALL_RPATH $<$<PLATFORM_ID:Linux>:"$ORIGIN">
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# testing

add_test(NAME ${TARGET} 
    COMMAND $<TARGET_FILE:${TARGET}>  
    "--gtest_output=xml:${TESTING_REPORT_DIR}/${TARGET}-$<CONFIG>.xml"
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
