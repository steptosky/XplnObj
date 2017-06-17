# Cross-platform C++ Library for working with the X-Plane obj format
- The library is distributed under 
[BSD (3-Clause)](http://opensource.org/licenses/BSD-3-Clause) 
license for more information read the [license](license.txt) file.
- [The X-Plane official website](http://www.x-plane.com/).
- [The X-Plane obj specification](http://developer.x-plane.com/?article=obj8-file-format-specification).
- [SemVer](http://semver.org/) is used for versioning.
- Minimum C++ standard is 14
- The versions from the master branch of this library 
    is available in the _conan-center https://conan.bintray.com_ repository without pre-built packages.  
    ```XplnObj/X.Y.Z@steptosky/stable```   
    use ```--build=missing``` or ```--build=XplnObj``` during ```conan install```  
    Although the _conanfile.py_ has _shared_ option it is not tested yet because 
    the library is designed to be built staticaly.

# See also
- [release-checklist](doc/release-checklist.md) If you are making the release.
- [changelog](doc/changelog.md) - this file is filling during the release process.
- [how to build](doc/build.md)
- [how to build with the conan test_package](doc/conan-test-package.md)
- [CI notes](doc/ci-notes.md)

---

## Warning 
- As the library hasn't got the major version 
  the library's interface and logic are not stable and can be changed at any time.
- The importing is still under developing and does not work correctly!


## Dependencies
- See [how to build](doc/build.md)

---

## Copyright
Copyright (c) 2017, StepToSky team. All rights reserved.  
[www.steptosky.com](http://www.steptosky.com/)