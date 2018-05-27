## Release checklist
- Check whether this release-checklist is correct.
- Check whether the change log is correct.
- Check whether the doxygen does not have unexpected warnings and errors while generating the documentation.
- Check whether the variables of the build system (CMake) in the file [readme.md](readme.md) are described correctly if they were changed, deleted, added.
- Check whether the dependencies and their version are described correctly in the [readme.md](readme.md) file. 

#### [StsProjectDesc.cmake](cmake/StsProjectDesc.cmake)
- Set the correct version in the file and check other information there.

## Cmake
- Check whether the information in the [StsProjectDesc.cmake](../cmake/StsProjectDesc.cmake) file is correct.

#### [conanfile.py](conanfile.py)
- Set the correct version.
- Check whether the file is corresponding to cmake settings and options, 
  if they were changed in the cmake scripts.
- Check whether the file uses the correct dependencies and their version.
- Check whether the _test_package_ works correctly, see [readme.md](readme.md).
