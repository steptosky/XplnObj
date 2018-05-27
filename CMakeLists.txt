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
# init

cmake_minimum_required (VERSION 3.10)

message(STATUS "==============================================")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
 
#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# Solution

project("XplnObj" LANGUAGES "CXX")

#----------------------------------------------------------------------------------#
# Info file

include(StsProjectDesc)
include(StsInfoFilesGenerator)
genInfoFile(StsProjectDesc "${CMAKE_SOURCE_DIR}/include/xpln/Info.h")

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# options 

if (NOT TEST_REPORT_DIR)
	set(TEST_REPORT_DIR ${CMAKE_SOURCE_DIR}/reports/tests)
endif()

if (NOT BUILD_SHARED_LIBS)
	set (BUILD_SHARED_LIBS OFF)
endif()

option(BUILD_TESTS "Build all of it's own tests." OFF) 

message(STATUS "==============================================")
if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "Build type = multi configuration or undefined")
else()
	message(STATUS "Build type = ${CMAKE_BUILD_TYPE}")
endif()
message(STATUS "Build tests = ${BUILD_TESTS}")
message(STATUS "Shared lib = ${BUILD_SHARED_LIBS}")
message(STATUS "Test report dir = ${TEST_REPORT_DIR}")
message(STATUS "Installation prefix = ${CMAKE_INSTALL_PREFIX}")
message(STATUS "==============================================")

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# conan.io this must be after options.

include(StsConan)
conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP CMAKE_TARGETS
                BUILD outdated)				
				
#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#		
# help targets

add_custom_target("Clean-Install-Dir"
	COMMAND cmake -E remove_directory ${CMAKE_INSTALL_PREFIX}
)

add_custom_target("Clean-Tests-Report"
	COMMAND cmake -E remove_directory ${TEST_REPORT_DIR}
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# sub projects

add_subdirectory(src)
if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(src-test)
endif()

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
# make package config version

include(CMakePackageConfigHelpers)
set(LIB_CONFIG_VER "${CMAKE_CURRENT_BINARY_DIR}/${ProjectId}ConfigVersion.cmake")
# COMPATIBILITY (AnyNewerVersion|SameMajorVersion|ExactVersion)
write_basic_package_version_file(
	${LIB_CONFIG_VER}
	VERSION ${ProjectVersion} 
	COMPATIBILITY SameMajorVersion
)

install(FILES ${LIB_CONFIG_VER} DESTINATION cmake)								

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
