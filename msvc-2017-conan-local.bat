:: Build and create conan package.
:: After finish the library will be available in the local conan cache.

call conan create . steptosky/develop ^
     -s compiler="Visual Studio" ^
     -s compiler.version=15 ^
     -s compiler.runtime=MD ^
     -s build_type=Release ^
     -o XplnObj:shared=False ^
     -e CONAN_BUILD_TESTING=1 ^
     -e CTEST_OUTPUT_ON_FAILURE=1 ^
    --build=XplnObj
    
call conan create . steptosky/develop ^
     -s compiler="Visual Studio" ^
     -s compiler.version=15 ^
     -s compiler.runtime=MDd ^
     -s build_type=Debug ^
     -o XplnObj:shared=False ^
     -e CONAN_BUILD_TESTING=1 ^
     -e CTEST_OUTPUT_ON_FAILURE=1 ^
    --build=XplnObj

pause
:: remove build dir in test package
rd /s/q "test_package/build"