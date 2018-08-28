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


# This class is helper.
# It retrieves and stores the vcs(git) data that is needed
# while building inside the conan repository
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
        fileHandle = open(file_path, "w")
        fileHandle.write('%s\n%s' % (self.vcs_branch, self.vcs_revision))
        fileHandle.close()

    def read_from_file(self, file_path):
        text_file = open(file_path, "r")
        out = text_file.read().split('\n')
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
            self.vcs_branch = os.environ.get("GIT_BRANCH")
            if not self.vcs_branch:
                print('[WARNING] Current branch name is HEAD and the GIT_BRANCH env var is not set. '
                      'Branch name will be set to \'detached\'')
                self.vcs_branch = "detached"
            else:
                print ("[VCS_INFO] ENV BRANCH: <%s>" % self.vcs_branch)
                print('[VCS_INFO] Branch name has been read from env variable: GIT_BRANCH')
        return self.has_actual_info()

    @staticmethod
    def isGitRepo():
        curDir = os.getcwd()
        while 1:
            dirList = os.listdir(curDir)
            if '.git' in dirList:
                print("[VCS_INFO] Found .git in: <%s>" % curDir)
                return True
            prevCurDir = curDir
            curDir = os.path.dirname(curDir)
            if curDir == prevCurDir:
                print("[VCS_INFO] .git is not found in the directory tree.")
                return False

    def load_vcs_info(self):
        if VcsInfo.isGitRepo():
            if self.read_from_vcs():
                self.write_to_file(self.vcs_info_file)
                print('[VCS_INFO] Loaded from VCS and writen to file %s'
                      % os.path.join(os.getcwd(), self.vcs_info_file))
            else:
                self.read_from_file(self.vcs_info_file)
                print('[VCS_INFO] Loaded from file %s' % os.path.join(os.getcwd(), self.vcs_info_file))
        else:
            self.read_from_file(self.vcs_info_file)
            print('[VCS_INFO] Loaded from file %s' % os.path.join(os.getcwd(), self.vcs_info_file))

    def __init__(self, workingDir='', vcsInfoFile=''):
        if workingDir:
            os.chdir(workingDir)
        if vcsInfoFile:
            self.vcs_info_file = vcsInfoFile

        print("[VCS_INFO] WorkDir: <%s>; VcsInfo File: <%s>" % (os.getcwd(), self.vcs_info_file))
        self.load_vcs_info()

# ----------------------------------------------------------------------------------#
# //////////////////////////////////////////////////////////////////////////////////#
# ----------------------------------------------------------------------------------#
