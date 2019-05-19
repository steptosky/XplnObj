::==========================================================
:: Sometimes conan asks you about to login to private repositories
:: if you have added ones. So you can put into the root repository folder
:: the file called 'set-conan-user.bat' and write there something like this:
::      call conan user -p <password> -r <remote alias> <user name>
if exist set-conan-user.bat call set-conan-user.bat
::==========================================================
set CONAN_USERNAME=steptosky
set CONAN_CHANNEL=testing
set CONAN_BUILD_TESTING=1
set CONAN_BUILD_POLICY=outdated
set CONAN_VISUAL_VERSIONS=16
set CONAN_ARCHS=x86_64
::==========================================================

call python build.py

:: uncomment next line if you want to remove all packages from all versions from specified channel
:: call conan remove XplnObj/*steptosky/testing -f

pause

:: remove build dir in test package
rd /s/q "test_package/build"
