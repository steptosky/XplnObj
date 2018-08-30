## Release checklist

- Check whether the [change log](changelog.md) is correct. Make sure the date and version are correct as well.
- Check whether the `doxygen` does not have unexpected warnings and errors while generating the documentation.
- Check whether the dependencies and their version are described correctly in the [readme.md](readme.md) file. 

#### [StsProjectDesc.cmake](cmake/StsProjectDesc.cmake)
- Set the correct version in the file and check other information there.

#### [conanfile.py](conanfile.py)
- Set the correct version.
- Check whether the file uses the correct dependencies and their version.
- Check whether the conan ```test_package``` works correctly.
