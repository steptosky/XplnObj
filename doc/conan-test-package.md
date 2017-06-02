## Build with the conan test_package

You can build the project with the ```conan test_package```
It also will put the result into the conan repository.

### Build scripts examples:
This is just the example for the windows!
```
conan test_package ^
    --profile ./conan-profiles/vs2015MD-Release ^
    --scope XplnObj:testing=True ^
    --scope XplnObj:test_report_dir="reports/conan-tests" ^
    --build=outdated
	
conan test_package ^
    --profile ./conan-profiles/vs2015MD-Debug ^
     -o include_pdbs=True ^
    --scope XplnObj:testing=True ^
    --scope XplnObj:test_report_dir="reports/conan-tests" ^
    --build=outdated
	
pause
```
After the building the package is available in the conan local repository,
so you can use it in other projects.  
You can change some default parameters by the environment variable,
see the the [test_package/conanfile.py](../test_package/conanfile.py) 
file of the _test_package_ for more information.
