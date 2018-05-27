# Cross-platform C++ Library for working with the X-Plane obj format
- The library is distributed under 
[BSD (3-Clause)](http://opensource.org/licenses/BSD-3-Clause) 
license for more information read the [license](license.txt) file.
- [The X-Plane official website](http://www.x-plane.com/).
- [The X-Plane obj specification](http://developer.x-plane.com/?article=obj8-file-format-specification).
- [SemVer](http://semver.org/) is used for versioning.
- The library requires C++ 14
- The versions from the master branch of this library is available in the _https://api.bintray.com/conan/steptosky/conan-open-source_  remote  
    without pre-built packages. ```XplnObj/X.Y.Z@steptosky/stable```   
- We have our own CI server so this library is tested on some versions of Visual Studio (Windows), Clang (Linux), Xcode (MAC (apple clang)).

#### dependencies
- [Cmake 3.10+](https://cmake.org) - build tool.
- [Conan 1.3+](https://www.conan.io) - dependency tool.
- [Python 2 or 3](https://www.python.org) - is needed for the Conan.
- [Doxygen](http://www.stack.nl/~dimitri/doxygen) - if you want to generate the documentation.
- [Gtest and Gmock 1.8](https://github.com/google/googletest) - testing (used through the Conan)  

#### documentation
Run from the root folder ``` doxygen doxyfile ``` the result will be in the _doc-generated_ folder. The _doxygen_ must be accessible through your PATH environment variable.

#### conan evironment variables
- _CONAN_TEST_REPORT_DIR_=(string path) - a path for storing tests results. Default value is specified in the cmake script.
- _CONAN_TEST_LIB_=(0 or 1) - enables/disables building and running the tests. If you set BUILD_TESTS=ON as a parameter for cmake it will auto-set this variable to "1".

#### cmake variables
Sometimes you will need to delete the file _cmake/conan.cmake_ then the newer version of this file will be download from Internet.
This file is responsible for cmake and conan interaction.
- _BUILD_TESTS=(ON/OFF)_ - Enable or disable building the test projects.
- _TEST_REPORT_DIR_=(string path) - You can specify the directory for the tests reports it is useful for CI.  

#### Build scripts examples:
These scripts are just examples!  
Probably you will need to adjust them for your purposes.

##### Windows (.bat) For Visual Studio 2017
```
::==========================================================
@echo off
:: Fix problems with some symbols
REM change CHCP to UTF-8
CHCP 65001
CLS

set dir="msvc"
if not exist %dir% mkdir %dir%
cd %dir%
::==========================================================
::conan user userName -r remote -p password
::==========================================================
call cmake -G "Visual Studio 14 Win64" ../ ^
	-DCMAKE_INSTALL_PREFIX=../output ^
	-DBUILD_TESTS=ON
:: Keep it commented if you want to generate VS project only
:: (without building), otherwise uncomment it.
::call cmake --build . --target install --config Release
::call cmake --build . --target install --config Debug
::==========================================================
cd ../
pause
::==========================================================
```

##### Linux (.sh)
```
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
#conan user userName -r remote -p password
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON
cmake --build . --target install
cd ../
#===========================================================
```

##### Mac OS (.sh)
```
#===========================================================
dir_name="build-release"
#===========================================================
rm -r ${dir_name}
mkdir ${dir_name}
cd ${dir_name}
#===========================================================
#conan user userName -r remote -p password
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON
cmake --build . --target install
cd ../
#===========================================================
```


#### Build with the conan 'create' scripts examples:
This is just the example for the windows!  
Probably you will need to adjust it for your purposes.
```
::call conan user userName -r remote -p password
conan create . steptosky/develop ^
     -s compiler="Visual Studio" ^
     -s compiler.version=14 ^
     -s compiler.runtime=MD ^
     -s build_type=Release ^
     -o XplnObj:shared=True ^
     -e CONAN_TEST_REPORT_DIR="report/conan-test" ^
     -e CONAN_TEST_LIB=1 ^
    --build=XplnObj ^
    --build=outdated

pause
:: remove build dir
rd /s/q "test_package/build"
```
After building the package will be available in the conan local cache,
so you can use it in other projects.  

---

## For the library developers
- [release-checklist](release-checklist.md) If you are making the release.
- [changelog](changelog.md) - this file is filling during the release process or when a feature is added.
---

## Copyright
Copyright (c) 2017, StepToSky team. All rights reserved.  
[www.steptosky.com](http://www.steptosky.com/)