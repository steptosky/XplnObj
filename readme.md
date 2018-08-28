# Cross-platform C++ Library for working with the X-Plane obj format
- The library is distributed under 
[BSD (3-Clause)](http://opensource.org/licenses/BSD-3-Clause) 
license for more information read the [license](license.txt) file.
- [The X-Plane official website](http://www.x-plane.com/).
- [The X-Plane obj specification](http://developer.x-plane.com/?article=obj8-file-format-specification).
- [SemVer](http://semver.org/) is used for versioning.
- The library requires C++ 14
- The versions from the master branch of this library is available in the _conan-center https://conan.bintray.com_  remote  
    without pre-built packages. ```XplnObj/X.Y.Z@steptosky/stable```   

## Conan additional arguments
- scope _testing_ - enables or disables tests building and runing. Default value is False.
- scope _test_report_dir_ - a path for storing tests results. Default value is specified in the cmake script.

# See also
- [release-checklist](doc/release-checklist.md) If you are making the release.
- [changelog](doc/changelog.md) - this file is filling during the release process or when a feature is added.
- [how to build](doc/build.md)
- [how to build with the conan 'create'](doc/conan-create.md)
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