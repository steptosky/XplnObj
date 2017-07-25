## Build

## Dependencies
###### Build
- [Cmake 3.7+](https://cmake.org) - build tool.
- [Conan 0.25+](https://www.conan.io) - dependency tool.
- [Python 2 or 3](https://www.python.org) - is needed for the Conan.
- [Doxygen](http://www.stack.nl/~dimitri/doxygen) - if you want to generate the documentation.

###### Developing
- [Gtest and Gmock 1.8](https://github.com/google/googletest) - testing (used through the Conan)  

-------------------------------------------------------------------------------------

#### See also [Build with the conan 'create'](conan-create.md)

-------------------------------------------------------------------------------------

## cmake variables
- **BUILD_TESTS=ON/OFF** - Enable or disable building the test projects.
- **TEST_REPORT_DIR** - You can specify the directory for the tests reports it is useful for CI.
##### Memo
- **CMAKE_BUILD_TYPE** - It will be set to _Release_ if it is not specified.
- **CMAKE_INSTALL_PREFIX** - Installation directory.

-------------------------------------------------------------------------------------

### Build documentation
You have to have [doxygen](http://www.stack.nl/~dimitri/doxygen/) installed and added to your _PATH_ environment variable.  
Run from root folder ``` doxygen doc/doxygen.cnf ``` the result will be in the _doc/generated_ folder.

-------------------------------------------------------------------------------------

### Build project scripts examples:
These scripts are just examples!  
Probably you will need to adjust them for your purposes.

#### Windows (.bat) For Visual Studio 2015 (14)
```
::==========================================================
@echo off
set dir="msvc"
if not exist %dir% mkdir %dir%
cd %dir%
::==========================================================
::call conan user userName -r remote -p password
call conan install .. --profile ../conan-profiles/vs2015MD-Release -g cmake_multi --build=missing
call conan install .. --profile ../conan-profiles/vs2015MD-Debug -g cmake_multi --build=missing
::==========================================================
call cmake -G "Visual Studio 14 Win64" ../ ^
	-DCMAKE_INSTALL_PREFIX=../output ^
	-DBUILD_TESTS=ON
:: Keep it commented if you want to generate VS project only
:: (without building), otherwise uncomment it.
::call cmake --build . --target install --config Release
::call cmake --build . --target install --config Debug
cd ../
::==========================================================
```

#### Linux (.sh)
```
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
#conan user userName -r remote -p password
conan install .. -s compiler="gcc" -s compiler.libcxx="libstdc++11" \
                 -s build_type=Release --build=missing
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON
cmake --build . --target install
cd ../
#===========================================================
```

#### Mac OS (.sh)
```
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
#conan user userName -r remote -p password
conan install .. -s compiler="apple-clang" -s compiler.libcxx="libc++" \
                 -s build_type=Release --build=missing
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON
cmake --build . --target install
cd ../
#===========================================================
```
