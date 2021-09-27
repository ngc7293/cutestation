cmake_minimum_required(VERSION 3.17)

set(SOURCES
    json.hh
    time.hh
    switch.hh
    thread.hh
    type.hh
    json.cc
    switch.cc
    thread.cc
)

add_library(cute.util STATIC ${SOURCES} ${HEADERS})
target_standard_compile_flags(cute.util)
target_link_libraries(cute.util PUBLIC cute.log CONAN_PKG::nlohmann_json CONAN_PKG::qt CONAN_PKG::gtest)

# Tests
set(TESTS
    tests/main.cc
    tests/test_json.cc
    tests/test_switch.cc
    tests/test_type.cc
)

add_executable(cute.util.test ${TESTS})
target_standard_compile_flags(cute.util.test)
target_link_libraries(cute.util.test PUBLIC cute.util CONAN_PKG::gtest)
gtest_discover_tests(cute.util.test)