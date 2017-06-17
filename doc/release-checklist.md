## Documentation
- Check whether this release-checklist is correct.
- Check whether the changelog is correct.
- Check whether the doxygen does not have unexpected warnings and errors while generating the documentation.
- Check whether the variables of the build system (CMake) in the file [Build.md](Build.md) are described correctly if they were changed, deleted, added.
- Check whether the dependencies and their version are described correctly in the [build.md](build.md) file. 

## Version and Description
- Set the correct version in the [StsProjectDesc.cmake](../cmake/StsProjectDesc.cmake)
- Set the correct version in the [conanfile.py](../conanfile.py)
- Set the correct version in the [test_package/conanfile.py](../test_package/conanfile.py)

## Cmake
- Check whether the information in the [StsProjectDesc.cmake](../cmake/StsProjectDesc.cmake) file is correct.

## Conan
- Check whether the [conanfile.py](../conanfile.py) is corresponding to cmake settings and options, 
  if they were changed in the cmake scripts.
- Check whether the [conanfile.py](../conanfile.py) uses the correct dependencies and their version.
- Check the _test_package_ works correctly, run ``` conan test_package ``` or see [how to build with the conan test_package](conan-test-package.md).
