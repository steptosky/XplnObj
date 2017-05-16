## Build with the conan test_package
### Build scripts examples:
This is just the example!
```
conan test_package \
	--profile vs2015-Debug \
	 -o include_pdbs=True \
	--scope XplnObj:testing=True \
	--scope XplnObj:test_report_dir="reports/conan-tests" \
	--build=outdated
```
After the building the package is available in the conan local repository,
so you can use it in other projects.  
You can change some default parameter by the environment variable,
see the [conan.py](../conanfile.py) file and the [test_package/conanfile.py](../test_package/conanfile.py) 
file of the _test_package_ for more information.
