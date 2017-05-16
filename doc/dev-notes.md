## Jenkins CI item example
- Use _"Inject passwords to the build as environment variables"_ for the conan password
  ```
  CONAN_PASS
  ```
- Generate enivironment variables from the project description
```
cd cmake
cmake -DCONTENT_PREFIX="Sts" -P StsProjectDescCiEnvGenerator.cmake 
```
- Use *inject environment variables* to set the list of environment variables
    and other manual ones
```
cmake/variables.txt
```
```
test_report_dir=${WORKSPACE}/reports/conan-tests

# These varibles must be before the conan test_package
# because the conan test_package uses them
CONAN_USERNAME=steptosky
CONAN_CHANNEL=stable
CONAN_REMOTE=conan.io
CONAN_PACKAGE_VERSION=${StsProjectVersion}
```
- Clean test report dir and print the environment variables
```
export -p
if [[ -d ${test_report_dir} ]]; then
    rm -r ${test_report_dir}
fi
```
- Build
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
- Upload to conan.io
```
conan user ${CONAN_USERNAME} -r ${CONAN_REMOTE} -p ${CONAN_PASS}
conan remove ${StsProjectId}/${CONAN_PACKAGE_VERSION}@${CONAN_USERNAME}/${CONAN_CHANNEL} -s -b -f
conan upload ${StsProjectId}/${CONAN_PACKAGE_VERSION}@${CONAN_USERNAME}/${CONAN_CHANNEL} -r conan.io --retry 3 --retry_wait 5
```
## Local pc
On your local PC you can use option *include_pdbs*, on CI it doesn't make a sense.  
Windows bat
```
conan test_package ^
    --profile vs2015-Release ^
    --scope XplnObj:testing=True ^
    --scope XplnObj:test_report_dir="reports/conan-tests" ^
    --build=outdated
	
conan test_package ^
    --profile vs2015-Debug ^
     -o include_pdbs=True ^
    --scope XplnObj:testing=True ^
    --scope XplnObj:test_report_dir="reports/conan-tests" ^
    --build=outdated
	
pause
```