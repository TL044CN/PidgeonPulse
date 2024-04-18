
pipeline {
    agent none
    stages {
        stage('initialize submodules') {
            agent {
                label 'generic'
            }
            steps {
                script {
                    sh 'git submodule update --init --recursive'
                    if (fileExists('vendor/FlockFlow')) {
                        stash name: "vendor", includes: 'vendor/FlockFlow/**'
                    } else {
                        echo 'vendor/FlockFlow directory not found.'
                        currentBuild.result = 'UNSTABLE'
                    }
                }
            }
        }
        stage('Build') {
            matrix {
                axes {
                    axis {
                        name 'PLATFORM'
                        values /*'windows',*/ 'linux'/*, 'macos'*/
                    }
                    axis {
                        name 'COMPILER'
                        values 'gcc', 'clang'/*, 'msvc'*/
                    }
                    axis {
                        name 'BUILD_TYPE'
                        values 'Release', 'Debug'/*, 'MinSizeRel', 'RelWithDebInfo'*/
                    }
                }

                stages {
                    stage('Select Agent'){
                        agent {
                            label "${PLATFORM}&&${COMPILER}"
                        }
                        stages {
                            stage('Retrieving Artifacts') {
                                steps {
                                    script{
                                        try {
                                            unstash 'vendor'
                                        } catch(Exception e) {

                                        }
                                        try {
                                            unarchive (mapping: [
                                                'vendor/FlockFlow': 'vendor/FlockFlow',
                                                "build-${PLATFORM}-${COMPILER}/": "build"
                                            ])
                                            artifactsRetrieved = true
                                        } catch (Exception e) {

                                        }
                                    }
                                }
                            }
                            stage('Build') {
                                steps {
                                    sh """
                                    cmake -B build/ -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
                                    cmake --build build/ --config=${BUILD_TYPE} -j
                                    """
                                }
                            }
                            stage('Run Tests'){
                                steps {
                                    sh """
                                    cmake -B build/ -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
                                    cmake --build build/ --config=${BUILD_TYPE} --target coverage -j
                                    """
                                }
                            }
                            stage('Archiving Artifacts') {
                                steps {
                                    sh 'mv build "build-${PLATFORM}-${COMPILER}"'
                                    archiveArtifacts (artifacts: 'vendor/FlockFlow/', allowEmptyArchive: true, onlyIfSuccessful: true, fingerprint: true)
                                    archiveArtifacts (artifacts: "build-${PLATFORM}-${COMPILER}/", allowEmptyArchive: true, onlyIfSuccessful: true, fingerprint: true)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
