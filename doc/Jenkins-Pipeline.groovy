//====================================================================================================//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================//
//
//  Copyright (C) 2017, StepToSky
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1.Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//  2.Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and / or other materials provided with the distribution.
//  3.Neither the name of StepToSky nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  Contacts: www.steptosky.com
//
//====================================================================================================//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================//
//
// It is early version of pipeline script
//
//
// Version: 0.3.0 (24.07.2017)
//     - Changed: usage 'conan create' instead of 'conan test_package' for building.
//     - Added: printing more information.
//
// Version: 0.2.1 (07.07.2017)
//     - Fixed: error mail sending if post build is failed.
//
// Version: 0.2.0 (27.06.2017)
//     - Added: Credentials Id for the repository url. It allows you to use private repositories.
//
// Version: 0.1.0 (16.06.2017)
//
//
//
// Notes:
//    * Agent with the name 'master' is used for sending e-mails,
//      so you have to have an agent with such a name.
//
//====================================================================================================//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================//
//
// You have to set the following variables.
//
//
// You have to specify url to the GIT repository.
// You also can specify a credential id with semicolon separator
//     GIT_REPO_URL=https://github.com/steptosky/XplnObj
//     GIT_REPO_URL=credentialId;https://github.com/steptosky/XplnObj
//
// You have to specify regex for branches.
// Example: :^(?!.*master).*$  - all except master
//     GIT_BRANCH=feature/some-feature
//
// Agents for parallel building
//     BUILD_AGENTS=windows, linux-clang, mac
//
// Enable or disable uploading to the conan repo,
// it may not be specified at all
// in such a case it is considered as disabled.
//     CONAN_UPLOAD=1
//
// Conan package channel in the conan remote.
// It is used while uploading.
// project/version@user/__CHANNEL__
//     CONAN_PACKAGE_CHANNEL=develop
//
// Conan package user for the project.
// It is used while uploading.
// project/version@__USER__/channel
//     CONAN_PACKAGE_USER=steptosky
//
// Comma separated aliases for the remotes that are used for reading.
// You have to set Jenkins credential id with the colon separation.
//     CONAN_REMOTES_USERS=alias:credentialId
//
// Comma separated aliases for the remotes that are used for uploading.
// ATTENTION: The users for these remotes must be set before, see CONAN_REMOTES_USERS.
//     CONAN_UPLOAD_REMOTES=alias, alias
//
// Always send mail when successful to specified addresses.
// Comma separated e-mail addresses.
// If the variable is not presented no mails will be sent.
//     SUCCESSFUL_MAIL=mail, mail
//
//====================================================================================================//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================//
// Functions-Helpers

// Sets the user for specified conan's remote using Jenkins credential id.
def setConanUserWithCredentialId(remote, credential_id) {
    echo "[INFO] Start adding conan's remotes users"
    withCredentials([[$class          : 'UsernamePasswordMultiBinding', credentialsId: credential_id,
                      usernameVariable: 'CONAN_USERNAME', passwordVariable: 'CONAN_PASSWORD']]) {
        def str = "conan user ${env.CONAN_USERNAME} -r ${remote} -p ${env.CONAN_PASSWORD}"
        if (isUnix()) {
            sh str
        } else {
            bat str
        }
    }
    echo "[INFO] Finish adding conan's remotes users"
}

// Uploads the conan recipe to specified conan remote.
// It uploads only the recipe without pre-build packages.
def conanUpload(product_id, package_version, conan_user, conan_channel, conan_remote) {
    echo "[INFO] Start uploading to conan's remotes"
    def remStr = "conan remove ${product_id}/${package_version}@${conan_user}/${conan_channel} " +
            "-s -b -f"
    def uploadStr = "conan upload ${product_id}/${package_version}@${conan_user}/${conan_channel} " +
            "-r ${conan_remote} --retry 3 --retry_wait 5"
    if (isUnix()) {
        sh remStr
        sh uploadStr
    } else {
        bat remStr
        bat uploadStr
    }
    echo "[INFO] Finish uploading to conan's remotes"
}

class Remote implements Serializable {
    String remoteName
    String credentialsId
}

// Parses the variable that has following format:
// remote_var='alias:credentialId, alias:credentialId'
// remotes are separated with the comma.
// remote data is separated with the colon.
// returns array.
Remote[] parseRemoteUsers(remote_var) {
    echo "[INFO] Start parsing to conan's remotes users"
    def remoteOutList = []
    if (remote_var) {
        def remotes = remote_var.split(',')
        echo "[INFO] Found ${remotes.size()} users for the conan remotes"
        for (int i = 0; i < remotes.size(); ++i) {
            def data = remotes[i].split(":")
            if (data.size() == 2) {
                Remote r = new Remote()
                r.remoteName = data[0].trim()
                r.credentialsId = data[1].trim()
                remoteOutList.add(r)
            } else {
                echo "[INFO] Incorrect conan remote data <${remotes[i]}> at <${i}> position"
            }
        }
    } else {
        echo "[INFO] Conan remotes are not specified"
    }
    echo "[INFO] Parsed ${remoteOutList.size()} conan remotes"
    echo "[INFO] Finish parsing to conan's remotes users"
    return remoteOutList
}

// Generates variables from the project description cmake script
// then load it into the Map and return it
Map loadProjectVariables() {
    echo "[INFO] Start loading the project variables"
    def str = 'cmake -DCONTENT_PREFIX=Sts -P StsProjectDescCiEnvGenerator.cmake'
    Map result = [:]
    dir('cmake') {
        if (isUnix()) {
            sh str
        } else {
            bat 'call ' + str
        }
        def vars = readFile('variables.txt').split("\r?\n")
        for (item in vars) {
            def keyVal = item.split("=")
            if (keyVal.size() == 2) {
                result[keyVal[0]] = keyVal[1]
            }
        }
    }
    echo "[INFO] Finish loading the project variables"
    return result
}

// Builds the project and its tests with the conan's 'create' (test_package)
def buildWithConanTestPackage(build_type, product_id, test_report_dir) {
    echo "[INFO] Start building with the conan 'create' (test_package)"
    def str = 'conan create ' + env.CONAN_PACKAGE_USER + '/' + env.CONAN_PACKAGE_CHANNEL +
            ' -s build_type=' + build_type +
            ' --scope ' + product_id + ':testing=True' +
            ' --scope ' + product_id + ':test_report_dir=\"' + test_report_dir + '\"' +
            ' --build=' + product_id + ' --build=outdated'
    if (isUnix()) {
        sh str
    } else {
        bat str
    }
    echo "[INFO] Finish building with the conan 'create' (test_package)"
}

def printConanRemotes() {
    echo "[INFO] Start printing conan's remote list"
    def cmdRemote = 'conan remote list'
    if (isUnix()) {
        sh cmdRemote
    } else {
        bat cmdRemote
    }
    echo "[INFO] Finish printing conan's remote list"
}

def gitCheckout() {
    echo "[INFO] Start git checkout"
    def repoData = env.GIT_REPO_URL.split(";")
    if (repoData.size() == 2) {
        echo "[INFO] Git checkout with credentials"
        checkout([$class           : 'GitSCM', branches: [[name: env.GIT_BRANCH]], doGenerateSubmoduleConfigurations: false,
                  extensions       : [], submoduleCfg: [],
                  userRemoteConfigs: [[credentialsId: repoData[0].trim(), url: repoData[1].trim()]]])
    } else {
        echo "[INFO] Git checkout"
        checkout([$class           : 'GitSCM', branches: [[name: env.GIT_BRANCH]], doGenerateSubmoduleConfigurations: false,
                  extensions       : [], submoduleCfg: [],
                  userRemoteConfigs: [[url: env.GIT_REPO_URL]]])
    }
    echo "[INFO] Finish git checkout"
}

//====================================================================================================//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================//
// Nodes and stages

def runCommonPre(nodeName) {
    stage('"' + nodeName + '" Prepare') {
        //---------------------
        gitCheckout()
        //---------------------
        printConanRemotes()
        //---------------------
        if (env.CONAN_REMOTES_USERS) {
            echo "[INFO] Start processing conan users variable"
            Remote[] remoteReadList = parseRemoteUsers(env.CONAN_REMOTES_USERS)
            // foreach does not work in this place, bug or don't I know something?
            // Caused: java.io.NotSerializableException: java.util.AbstractList$Itr
            for (int i = 0; i < remoteReadList.size(); ++i) {
                Remote r = remoteReadList[i]
                setConanUserWithCredentialId(r.remoteName, r.credentialsId)
            }
            echo "[INFO] Finish processing conan users variable"
        }
        //---------------------
    }
}

def runCommonBuild(nodeName) {
    def test_report_dir = env.WORKSPACE + '/reports/conan-tests'
    stage('"' + nodeName + '" Build') {
        Map kv = loadProjectVariables()
        echo "[INFO] Start building Debug"
        buildWithConanTestPackage('Debug', kv['StsProjectId'], test_report_dir)
        echo "[INFO] Finish building Debug"
        echo "[INFO] Start building Release"
        buildWithConanTestPackage('Release', kv['StsProjectId'], test_report_dir)
        echo "[INFO] Finish building Release"
    }
}

def uploadToConan() {
    if (env.CONAN_UPLOAD == '1') {
        def instancesList = env.BUILD_AGENTS.split(",")
        if (instancesList.size() != 0) {
            if (env.CONAN_UPLOAD_REMOTES) {
                node(instancesList[0]) {
                    Map kv = loadProjectVariables()
                    def remoteList = env.CONAN_UPLOAD_REMOTES.split(",")
                    // foreach does not work in this place, bug or don't I know something?
                    // Caused: java.io.NotSerializableException: java.util.AbstractList$Itr
                    for (int i = 0; i < remoteList.size(); ++i) {
                        conanUpload(kv['StsProjectId'], kv['StsProjectVersion'],
                                env.CONAN_PACKAGE_USER, env.CONAN_PACKAGE_CHANNEL, remoteList[i].trim())
                    }
                }
            }
        }
    } else {
        echo "[INFO] Conan uploading is disabled"
    }
}

// Sends information that the build is successfully finished.
def successfulMail(nodeName) {
    node(nodeName) {
        if (env.SUCCESSFUL_MAIL) {
            mail(
                    body: "See ${env.BUILD_URL}",
                    subject: "Successful : ${env.JOB_NAME} #${env.BUILD_NUMBER}",
                    to: "${env.SUCCESSFUL_MAIL}"
            )
        }
    }
}

// Always sends mail if build is failed
// and mail "build is back to normal"
def sendMail(nodeName) {
    node(nodeName) {
        // It fixes the bug with the "back to normal" message
        // https://issues.jenkins-ci.org/browse/JENKINS-37171
        if (currentBuild.result == null) {
            currentBuild.result = 'SUCCESS'
        }
        def to = emailextrecipients([[$class: 'CulpritsRecipientProvider'],
                                     [$class: 'RequesterRecipientProvider'],
                                     [$class: 'FailingTestSuspectsRecipientProvider'],
                                     [$class: 'FirstFailingBuildSuspectsRecipientProvider'],
                                     [$class: 'UpstreamComitterRecipientProvider'],
                                     [$class: 'DevelopersRecipientProvider']])
        step([$class: 'Mailer', notifyEveryUnstableBuild: true, recipients: "${to}", sendToIndividuals: true])
    }
}

def runCommonPost() {
    try {
        def instancesList = env.BUILD_AGENTS.split(",")
        for (int i = 0; i < instancesList.size(); i++) {
            def instanceName = instancesList[i].trim()
            node(instanceName) {
                stage('"' + instanceName + '" Publish tests') {
                    junit healthScaleFactor: 100.0, testResults: 'reports/*/*.xml'
                }
            }
        }
    } finally {
        sendMail('master')
    }
}

//=====================================================================================================//
// Skeleton for dynamic nodes

Closure getNodeForInstance(String instanceName) {
    return {
        node(instanceName) {
            runCommonPre(instanceName)
            runCommonBuild(instanceName)
        }
    }
}

def parallelConverge(String instances) {
    if (instances) {
        def parallelNodes = [:]

        def instancesList = instances.split(",")
        for (int i = 0; i < instancesList.size(); i++) {
            def instanceName = instancesList[i].trim()
            parallelNodes[instanceName] = getNodeForInstance(instanceName)
        }

        parallel parallelNodes
    } else {
        echo "[INFO] There are no build agents specified"
    }
}

//=====================================================================================================//
// Skeleton

pipeline {
    agent none
    stages {
        stage('Run builds parallel') {
            steps {
                parallelConverge(env.BUILD_AGENTS)
            }
        }
        stage('Upload to conan') {
            steps {
                uploadToConan()
            }
        }
    }
    post {
        always {
            runCommonPost()
        }
        success {
            successfulMail('master')
            echo "[INFO] Finished ${env.JOB_NAME}:${env.BUILD_ID} on ${env.JENKINS_URL}"
        }
        failure { echo "[INFO] Finished with failure ${env.JOB_NAME}:${env.BUILD_ID} on ${env.JENKINS_URL}" }
    }
}

//====================================================================================================//
////////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================//