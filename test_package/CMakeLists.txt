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

cmake_minimum_required (VERSION 3.7.0)
PROJECT(ConanTest)
set(TARGET_NAME mytest)

#----------------------------------------------------------------------------------#

message(STATUS "== CONAN TEST PACKAGE ==========================================")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${TARGET_NAME} test_package.cpp)
target_link_libraries(${TARGET_NAME} CONAN_PKG::XplnObj)
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES)

target_compile_options(${TARGET_NAME} 
	PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/W4>"
    PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/WX>"
	
	PRIVATE "$<$<CXX_COMPILER_ID:AppleClang>:-Wno-unknown-pragmas>"
	PRIVATE "$<$<CXX_COMPILER_ID:AppleClang>:-pedantic>"
    PRIVATE  "$<$<CXX_COMPILER_ID:AppleClang>:-Werror>"
	
	PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-Wno-unknown-pragmas>"
	PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-pedantic>"
	PRIVATE  "$<$<CXX_COMPILER_ID:Clang>:-Werror>"

	PRIVATE "$<$<CXX_COMPILER_ID:GNU>:-Wno-unknown-pragmas>"
	PRIVATE "$<$<CXX_COMPILER_ID:GNU>:-pedantic>"
	PRIVATE  "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#