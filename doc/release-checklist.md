## Documentation
- Check whether this release-checklist is correct.
- Check whether the changelog is correct.
- Check whether the doxygen does not have unexpected warnings and errors while generating the documentation.
- Check whether the variables of the build system (CMake) are described correctly if they were changed, deleted, added.
- Check whether the dependencies and their version are described correctly in the [readme.md](../readme.md) file. 

## Version
- Set the correct version in the [StsProjectDesc.cmake](cmake/StsProjectDesc.cmake)
- Set the correct version in the [conanfile.py](../conanfile.py)
- Set the correct version in the [test_package/conanfile.py](../test_package/conanfile.py)

## Cmake
- Check whether the information in the [StsProjectDesc.cmake](cmake/StsProjectDesc.cmake) file is correct.

## Conan
- Check whether the [conanfile.py](../conanfile.py) is corresponding to cmake settings and options, 
  if something was changed in the cmake scripts.
- Check whether the [conanfile.py](../conanfile.py) uses the correct dependencies and their version.
- Check the test_package works correctly ``` conan test_package ```.
