# Build and create conan package.
# After finish the library will be available in the local conan cache.

conan create . steptosky/develop \
     -s compiler="apple-clang" \
     -s compiler.version=9.1 \
     -s build_type=Release \
     -o XplnObj:shared=False \
     -e CONAN_BUILD_TESTING=1 \
     -e CTEST_OUTPUT_ON_FAILURE=1 \
    --build=XplnObj

conan create . steptosky/develop \
     -s compiler="apple-clang" \
     -s compiler.version=9.1 \
     -s build_type=Debug \
     -o XplnObj:shared=False \
     -e CONAN_BUILD_TESTING=1 \
     -e CTEST_OUTPUT_ON_FAILURE=1 \
    --build=XplnObj
