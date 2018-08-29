set CONAN_USERNAME=steptosky
set CONAN_CHANNEL=stable
set CONAN_BUILD_TESTING=1
set CONAN_BUILD_POLICY=outdated
set CONAN_VISUAL_VERSIONS=15
set CONAN_ARCHS=x86_64
set CTEST_OUTPUT_ON_FAILURE=1

call python build.py

:: uncomment next line if you want to remove all packages from all versions from specified channel
conan remove XplnObj/*@steptosky/testing -f

pause

:: remove build dir in test package
:: rd /s/q "test_package/build"