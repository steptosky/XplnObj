## Build with the conan 'create'

You can build the project with the ```conan create```
It also will put the result into the conan cache.

### Build scripts examples:
This is just the example for the windows!  
Probably you will need to adjust it for your purposes.
```
::call conan user userName -r remote -p password
conan create steptosky/develop ^
    --profile ./conan-profiles/vs2015MD-Release ^
    --scope XplnObj:testing=True ^
    --scope XplnObj:test_report_dir="reports/conan-tests" ^
    --build=XplnObj ^
    --build=outdated

conan create steptosky/develop ^
    --profile ./conan-profiles/vs2015MD-Debug ^
     -o XplnObj:include_pdbs=True ^
    --scope XplnObj:testing=True ^
    --scope XplnObj:test_report_dir="reports/conan-tests" ^
    --build=XplnObj ^
    --build=outdated
	
pause
```
After building the package will be available in the conan local cache,
so you can use it in other projects.  
You can change some default parameters by the environment variable,
see the the [test_package/conanfile.py](../test_package/conanfile.py) 
file of the _test_package_ for more information.
