# Cross-platform C++ Library for working with the X-Plane obj format
- The library is distributed under 
[BSD (3-Clause)](http://opensource.org/licenses/BSD-3-Clause) 
license for more information read the [license](license.txt) file.
- Versioning in accordance with the [semver](http://semver.org/)
- Minimum C++ standard is 14
- The versions from the master branch of this library 
    is available in the conan.io repository without pre-built packages.  
    ```XplnObj/X.Y.Z@steptosky/stable```   
    use ```--build=missing``` or ```--build=XplnObj``` during ```conan install```

# See also
- [release-checklist](doc/release-checklist.md) If you are making the release.
- [ChangeLog](changelog.md) - this file is filling during the release process.
- [how to build](doc/build.md)
- [how to build with the conan test_package](doc/conan-test-package.md)
- [dev notes](doc/dev-notes.md)

---

## Warning 
- As the library hasn't got the major version 
  the library's interface is not stable and can be changed at any time.
- The importing is still under developing and does not work correctly!


## Dependencies
##### Build
- [Cmake 3.7+](https://cmake.org) - build tool.
- [Conan 0.21+](https://www.conan.io) - dependency tool.
- [Python 2 or 3](https://www.python.org) - is needed for the Conan.
- [Doxygen](http://www.stack.nl/~dimitri/doxygen) - if you want to generate the documentation.

##### Developing
- [Gtest and Gmock 1.8](https://github.com/google/googletest) - testing (used through the Conan)  

---

## Copyright
Copyright (c) 2017, StepToSky team. All rights reserved.  
[www.steptosky.com](http://www.steptosky.com/)