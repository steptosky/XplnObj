## Build
### Build scripts examples:
These scripts are just examples!

#### Windows (.bat)
```
::==========================================================
@echo off
set dir="msvc"
if not exist %dir% mkdir %dir%
cd %dir%
::==========================================================
call conan install .. --profile vs2015-Release -g cmake_multi --build=missing
call conan install .. --profile vs2015-Debug -g cmake_multi --build=missing
::==========================================================
call cmake -G "Visual Studio 14 Win64" ../ ^
	-DCMAKE_INSTALL_PREFIX=../output ^
	-DUSE_CONAN_CMAKE_MULTI=ON ^
	-DBUILD_TESTS=ON ^
	-DBUILD_SHARED_LIBS=OFF
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
conan install .. -s compiler="gcc" -s compiler.libcxx="libstdc++11" \
                 -s build_type=Release --build=missing
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DUSE_CONAN_CMAKE_MULTI=OFF \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON \
    -DBUILD_SHARED_LIBS=OFF
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
conan install .. -s compiler="apple-clang" -s compiler.libcxx="libc++" \
                 -s build_type=Release --build=missing
#===========================================================
cmake -G"Unix Makefiles" ../ \
    -DCMAKE_BUILD_TYPE="Release" \
    -DUSE_CONAN_CMAKE_MULTI=OFF \
    -DCMAKE_INSTALL_PREFIX=../output \
    -DBUILD_TESTS=ON \
    -DBUILD_SHARED_LIBS=OFF
cmake --build . --target install
cd ../
#===========================================================
```
