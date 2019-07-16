ECHO "WARNING You are going to upload the conan recipe to bintray"
pause
::==========================================================
:: Sometimes conan asks you about to login to private repositories
:: if you have added ones. So you can put into the root repository folder
:: the file called 'set-conan-user.bat' and write there something like this:
::      conan user -p <api-key> -r sts-bintray <user>
if exist set-conan-user.bat call set-conan-user.bat
::==========================================================
conan export . steptosky/stable

:: For safe reason it is turned off by default
:: you have to uncomment it and set the CORRECT version.
::conan upload XplnObj/0.9.0@steptosky/stable -r sts-bintray -c --retry 2 --retry-wait 5
::==========================================================
pause