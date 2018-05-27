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

set(PROJECT test-${ProjectId})
project(${PROJECT} VERSION ${ProjectVersion} LANGUAGES "CXX")

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

add_executable(${PROJECT} ${CM_FILES})
add_dependencies(${PROJECT} ${ProjectId})
add_definitions(-DTESTING)

#----------------------------------------------------------------------------------#
# linkage 

target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT} CONAN_PKG::gtest)
target_link_libraries(${PROJECT} ${ProjectId})
target_link_libraries(${PROJECT} "$<$<CXX_COMPILER_ID:GNU>:pthread>")
target_link_libraries(${PROJECT} "$<$<CXX_COMPILER_ID:Clang>:pthread>")

#----------------------------------------------------------------------------------#
# compile options

target_compile_options(${PROJECT} 
	PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/W4>"
    #PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/WX>"
	
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
# testing

add_test(NAME ${PROJECT} COMMAND $<TARGET_FILE:${PROJECT}>  
	"--gtest_output=xml:${TEST_REPORT_DIR}/${PROJECT}-$<CONFIG>.xml"
)

#----------------------------------------------------------------------------------#
#//////////////////////////////////////////////////////////////////////////////////#
#----------------------------------------------------------------------------------#
