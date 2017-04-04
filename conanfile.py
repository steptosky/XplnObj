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

import os
from conans import ConanFile, CMake
from conanfile_vcs import ConanVcs

vcs_data = ConanVcs()
vcs_data.load_vcs_data()


class XUpdaterLibConan(ConanFile):
    version = "0.3.0"
    name = 'XplnObj'
    url = 'https://github.com/steptosky/XplnObj'
    license = 'BSD 3-Clause'
    description = "This library is for working with the x-plane's obj format."
    author = 'StepToSky (info@steptosky.com)'
    settings = "os", "compiler", "build_type", "arch"
    options = {'shared': ['True', 'False'], 'include_pdbs': ['True', 'False']}
    default_options = 'shared=False', 'include_pdbs=False', 'gtest:shared=False'
    exports = 'vcs_data', 'conanfile_vcs.py'
    exports_sources = 'CMakeLists.txt', 'src/*', 'src-test/*', 'include/*', 'cmake/*'
    generators = 'cmake'

    def config_options(self):
        if self.settings.compiler != "Visual Studio":
            try:  # It might have already been removed if required by more than 1 package
                del self.options.include_pdbs
            except:
                pass

    def requirements(self):
        if self.scope.dev or self.scope.testing:
            self.requires('gtest/1.8.0@lasote/stable', private=True)

    def build(self):
        target_test = 'run_tests' if self.settings.compiler == 'Visual Studio' else 'test'
        cmake = CMake(self.settings)
        args = ['-DBUILD_SHARED_LIBS="%s"' % ('ON' if self.options.shared else 'OFF')]
        args += ['-DBUILD_TESTS="%s"' % ('ON' if self.scope.testing else 'OFF')]
        args += ['-DCMAKE_INSTALL_PREFIX="%s"' % self.package_folder]
        if self.scope.test_report_dir:
            args += ['-DTEST_REPORT_DIR="%s"' % self.scope.test_report_dir]
        if vcs_data.has_valid_data():
            args += [vcs_data.cmake_args()]
        self.run('cmake %s %s %s' % (self.conanfile_directory, cmake.command_line, ' '.join(args)))
        self.run('cmake --build . --target install %s' % cmake.build_config)
        if self.scope.testing:
            self.run('cmake --build . --target %s %s' % (target_test, cmake.build_config))

    def package(self):
        if self.settings.compiler == "Visual Studio" and self.options.include_pdbs:
            self.copy(pattern="*/%s.pdb" % self.name, dst='%s' % self.settings.build_type, src=".", keep_path=False)

    def package_info(self):
        self.cpp_info.libdirs = ['%s' % self.settings.build_type]
        self.cpp_info.libs = [self.name]

# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
