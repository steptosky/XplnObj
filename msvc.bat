::==========================================================
@echo off
set dir="msvc"
if not exist %dir% mkdir %dir%
cd %dir%
::==========================================================
::call conan user userName -r remote -p password
call conan install .. --profile ../conan-profiles/vs2017MD-Release -e CONAN_BUILD_TESTING=1 -g cmake_multi --build=missing
call conan install .. --profile ../conan-profiles/vs2017MD-Debug -e CONAN_BUILD_TESTING=1 -g cmake_multi --build=missing
::==========================================================
call cmake -G "Visual Studio 15 Win64" ../ ^
	-DCMAKE_INSTALL_PREFIX=../output ^
	-DBUILD_TESTS=ON
:: Keep it commented if you want to generate VS project only
:: (without building), otherwise uncomment it.
::call cmake --build . --target install --config Release
::call cmake --build . --target install --config Debug
cd ../
    pause
::==========================================================