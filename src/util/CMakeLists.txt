cmake_minimum_required(VERSION 3.17)

set(HEADERS
    inc/util/json.hh
    inc/util/time.hh
    inc/util/switch.hh
)

set(SOURCES
    src/json.cc
    src/switch.cc
)

add_library(cute.util STATIC ${SOURCES} ${HEADERS})
target_compile_features(cute.util PUBLIC cxx_std_20)
target_include_directories(cute.util PUBLIC inc/ PRIVATE src/)
target_os_compile_options(TARGET cute.util LINUX -Wall -Werror -Wpedantic -fPIC)
target_link_libraries(cute.util PUBLIC cute.log CONAN_PKG::nlohmann_json CONAN_PKG::qt)

# Tests
set(TESTS
    tests/main.cc
    tests/test_json.cc
    tests/test_switch.cc
)

add_executable(cute.util.test ${TESTS})
target_link_libraries(cute.util.test PUBLIC cute.util CONAN_PKG::gtest)
gtest_discover_tests(cute.util.test)