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
import os

username = os.getenv("CONAN_PACKAGE_USER", "steptosky")
channel = os.getenv("CONAN_PACKAGE_CHANNEL", "develop")
version = os.getenv("CONAN_PACKAGE_VERSION", "0.4.0")
artifact_name = os.getenv("CONAN_PACKAGE_NAME", "XplnObj")


class LibReuseConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "%s/%s@%s/%s" % (artifact_name, version, username, channel)
    options = {'shared': ['True', 'False'], 'include_pdbs': ['True', 'False']}
    default_options = 'shared=False','include_pdbs=False'
    generators = 'cmake'

    def config_options(self):
        if self.options.include_pdbs:
            self.options[artifact_name].include_pdbs = True
            self.options['gtest'].include_pdbs = True

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake %s %s' % (self.conanfile_directory, cmake.command_line))
        self.run('cmake --build . %s' % cmake.build_config)

    def test(self):
        self.run(os.sep.join([".", ("%s" % self.settings.build_type), "mytest"]))

# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
