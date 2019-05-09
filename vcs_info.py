# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
#
#  Copyright (C) 2018, StepToSky
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
# This class is helper.
# It retrieves and stores the vcs(git) data that is needed
# while building inside the conan repository.
#
# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#

import os
import subprocess
import re


class VcsInfo:
    vcs_branch = ''
    vcs_revision = ''
    vcs_info_file = 'vcs_data'
    vcs_branch_env_var = 'GIT_BRANCH'

    def setup_cmake(self, cmake):
        if self.has_actual_info():
            cmake.definitions["vcs_branch"] = self.vcs_branch
            cmake.definitions["vcs_revision"] = self.vcs_revision

    def has_actual_info(self):
        if len(self.vcs_branch) == 0 or len(self.vcs_revision) == 0:
            return False
        return True

    def write_to_file(self, file_path):
        if os.path.dirname(file_path) and not os.path.exists(os.path.dirname(file_path)):
            os.makedirs(os.path.dirname(file_path))
        file_handle = open(file_path, "wb")
        file_handle.write(('%s\n%s' % (self.vcs_branch, self.vcs_revision)).encode('utf-8'))
        file_handle.close()

    def read_from_file(self, file_path):
        text_file = open(file_path, "rb")
        out = text_file.read().decode("utf-8").split('\n')
        if len(out) < 2:
            self.clear()
        else:
            self.vcs_branch = out[0]
            self.vcs_revision = out[1]
        text_file.close()

    def clear(self):
        self.vcs_branch = ''
        self.vcs_revision = ''

    def read_from_vcs(self):
        self.clear()
        try:
            self.vcs_branch = subprocess.check_output(['git', 'rev-parse', '--abbrev-ref', 'HEAD']) \
                .decode("utf-8").strip()
            self.vcs_revision = subprocess.check_output(['git', 'log', '-1', '--pretty=format:%h']) \
                .decode("utf-8").strip()
        except Exception as ex:
            print("[ERROR] Cannot get git repo info. Reason: %s" % ex)
            raise ex
        if re.search(r'HEAD', self.vcs_branch, re.IGNORECASE):
            branch_from_env = os.environ.get(self.vcs_branch_env_var)
            if branch_from_env:
                self.vcs_branch = branch_from_env
                print('[VCS_INFO] Branch name <%s> has been read from env variable <%s>' %
                      (self.vcs_branch, self.vcs_branch_env_var))
            else:
                print('[VCS_INFO] [WARNING] Current branch name is HEAD and <%s> env variable is not set.' %
                      self.vcs_branch_env_var)
        return self.has_actual_info()

    @staticmethod
    def is_git_repo():
        curr_dir = os.getcwd()
        while 1:
            dir_list = os.listdir(curr_dir)
            if '.git' in dir_list:
                print("[VCS_INFO] Found .git in: <%s>" % curr_dir)
                return True
            prev_curr_dir = curr_dir
            curr_dir = os.path.dirname(curr_dir)
            if curr_dir == prev_curr_dir:
                print("[VCS_INFO] .git is not found in the directory tree.")
                return False

    #
    def load_vcs_info(self):
        if VcsInfo.is_git_repo():
            if self.read_from_vcs():
                self.write_to_file(self.vcs_info_file)
                print('[VCS_INFO] Loaded from VCS and writen to file %s'
                      % os.path.join(os.getcwd(), self.vcs_info_file))
            else:
                self.read_from_file(self.vcs_info_file)
                print('[VCS_INFO] Loaded from file %s' % os.path.join(os.getcwd(), self.vcs_info_file))
        else:
            if os.path.exists(self.vcs_info_file):
                self.read_from_file(self.vcs_info_file)
                print('[VCS_INFO] Loaded from file %s' % os.path.join(os.getcwd(), self.vcs_info_file))
            else:
                self.vcs_branch = 'undefined'
                self.vcs_revision = 'undefined'
                print("[VCS_INFO] [WARNING] <%s> isn't a git repository and file <%s> isn't found "
                      "the result is: branch and revision are 'undefined'" %
                      (os.getcwd(), self.vcs_info_file))

    def __init__(self, working_dir='', vcs_info_file=''):
        if working_dir:
            os.chdir(working_dir)
        if vcs_info_file:
            self.vcs_info_file = vcs_info_file

        print("[VCS_INFO] Working dir: <%s>" % os.getcwd())
        print("[VCS_INFO] File: <%s>" % self.vcs_info_file)
        self.load_vcs_info()

# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
