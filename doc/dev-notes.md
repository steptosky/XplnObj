## Jenkins CI item example
- Set the conan user and password, you can use _'Use secret text(s) or file(s)'_
  or _'Inject passwords to the build as environment variables'_ in the jenkins item (task).
  ```
  CONAN_USERNAME
  CONAN_PASS
  ```
- Generate enivironment variables from the project description
```
cd cmake
cmake -DCONTENT_PREFIX="Sts" -P StsProjectDescCiEnvGenerator.cmake 
```
- Use *inject environment variables* to set the list of environment variables which were generated
  on previous step and other manual ones.
```
cmake/variables.txt
```
```
test_report_dir=${WORKSPACE}/reports/conan-tests

# These varibles must be before the conan test_package
# because the conan test_package uses them
CONAN_CHANNEL=stable
CONAN_REMOTE=conan.io
CONAN_PACKAGE_VERSION=${StsProjectVersion}
```
- Clean up test report dir and print the environment variables
```
export -p
if [[ -d ${test_report_dir} ]]; then
    rm -r ${test_report_dir}
fi
```
- Set the conan user
```
conan user ${CONAN_USERNAME} -r ${CONAN_REMOTE} -p ${CONAN_PASS}
```

- Build with the conan's _test_package_. It builds and tests the sources.
```
conan test_package \
    -s build_type=Release \
    --scope ${StsProjectId}:testing=True \
    --scope ${StsProjectId}:test_report_dir=${test_report_dir} \
    --build=${StsProjectId}
```
```
conan test_package \
    -s build_type=Debug \
    --scope ${StsProjectId}:testing=True \
    --scope ${StsProjectId}:test_report_dir=${test_report_dir} \
    --build=${StsProjectId}
```
- Upload to the conan repository
```
conan remove ${StsProjectId}/${CONAN_PACKAGE_VERSION}@${CONAN_USERNAME}/${CONAN_CHANNEL} -s -b -f
conan upload ${StsProjectId}/${CONAN_PACKAGE_VERSION}@${CONAN_USERNAME}/${CONAN_CHANNEL} -r ${CONAN_REMOTE} --retry 3 --retry_wait 5
```