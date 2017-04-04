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
#
#   Version: 0.1.0 (02.04.2017)
#
# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#


import os
import subprocess


# This class is helper.
# It retrieves and stores the vcs(git) data that is needed
# while building inside the conan repository
class ConanVcs:
    vcs_branch = ''
    vcs_revision = ''

    def cmake_args(self):
        return '-Dvcs_branch=%s -Dvcs_revision=%s ' % (self.vcs_branch, self.vcs_revision)

    def has_valid_data(self):
        if len(self.vcs_branch) == 0 or len(self.vcs_revision) == 0:
            return False
        return True

    def write_to_file(self, filepath):
        file = open(filepath, "w")
        file.write('%s\n%s' % (self.vcs_branch, self.vcs_revision))
        file.close()

    def read_from_file(self, filepath):
        text_file = open(filepath, "r")
        out = text_file.read().split('\n')
        if len(out) < 2:
            self.clear_data()
        else:
            self.vcs_branch = out[0]
            self.vcs_revision = out[1]
        text_file.close()

    def clear_data(self):
        self.vcs_branch = ''
        self.vcs_revision = ''

    def read_vcs_data(self):
        self.clear_data()
        self.vcs_branch = subprocess.check_output(['git', 'rev-parse', '--abbrev-ref', 'HEAD']).decode("utf-8").strip()
        self.vcs_revision = subprocess.check_output(['git', 'log', '-1', '--pretty=format:%h']).decode("utf-8").strip()
        return self.has_valid_data()

    def load_vcs_data(self):
        if not self.read_vcs_data():
            self.read_from_file('vcs_data')
        else:
            self.write_to_file('vcs_data')

# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
