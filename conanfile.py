# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
#
#  Copyright (C) 2017, StepToSky
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  1.Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#  2.Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and / or other materials provided with the distribution.
#  3.Neither the name of StepToSky nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
#  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  Contacts: www.steptosky.com
#
# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#

from conans import ConanFile, CMake
from conanfile_vcs import ConanVcs

vcs_data = ConanVcs()
vcs_data.load_vcs_data()


class LibConan(ConanFile):
    version = "0.5.0"
    name = 'XplnObj'
    url = 'https://github.com/steptosky/XplnObj'
    license = 'BSD 3-Clause'
    description = "This library is for working with the X-Plane's obj format. It uses C++ 14."
    author = 'StepToSky <info@steptosky.com>'
    settings = "os", "compiler", "build_type", "arch"
    options = {'shared': [True, False],
               'include_pdbs': [True, False],
               "fpic": [True, False]}
    default_options = 'shared=False', 'include_pdbs=False', 'gtest:shared=False', 'fpic=False'
    exports = 'vcs_data', 'conanfile_vcs.py'
    exports_sources = 'CMakeLists.txt', 'src/*', 'src-test/*', 'include/*', 'cmake/*', 'license*'
    generators = 'cmake'
    build_policy = 'missing'

    def configure(self):
        if self.settings.compiler == "Visual Studio" and float(str(self.settings.compiler.version)) < 14:
            raise Exception("Visual Studio >= 14 is required")

    def config_options(self):
        if self.settings.compiler != "Visual Studio":
            try:  # It might have already been removed if required by more than 1 package
                del self.options.include_pdbs
            except Exception:
                pass

    def requirements(self):
        if self.scope.dev or self.scope.testing:
            self.requires('gtest/1.8.0@lasote/stable', private=True)

    def build(self):
        cmake = CMake(self)
        vcs_data.setup_cmake(cmake)
        cmake.definitions["BUILD_TESTS"] = 'ON' if self.scope.testing else 'OFF'
        if self.scope.test_report_dir:
            cmake.definitions["TEST_REPORT_DIR"] = self.scope.test_report_dir
        if self.options.fpic:
            cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = "ON"
        cmake.configure()
        cmake.build()
        cmake.install()
        if self.scope.testing:
            cmake.test()

    def package(self):
        self.copy("license*", src=".", dst="licenses", ignore_case=True, keep_path=False)
        if self.settings.compiler == "Visual Studio" and self.options.include_pdbs:
            self.copy(pattern="*/%s.pdb" % self.name, dst='%s' % self.settings.build_type, src=".", keep_path=False)

    def package_info(self):
        self.cpp_info.libdirs = ['%s' % self.settings.build_type]
        self.cpp_info.libs = [self.name]

# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
