cmake_minimum_required(VERSION 3.17)

set(SOURCES
    src/sampling_policy.cc
    src/series_factory.cc
    src/series.cc
    src/time_series.cc
)

set(HEADERS
    inc/data/series_factory.hh
    inc/data/series.hh
    inc/data/time_series.hh
    inc/data/sampling_policy.hh
    src/no_sampling_policy.hh
)

add_library(cute.data STATIC ${SOURCES} ${HEADERS})
set_property(TARGET cute.data PROPERTY CXX_STANDARD 20)
target_include_directories(cute.data PUBLIC inc/ PRIVATE src/)
target_os_compile_options(TARGET cute.data LINUX -Wall -Werror -Wpedantic -fPIC)
target_link_libraries(cute.data PUBLIC cute.log cute.proto topic cute.util CONAN_PKG::nlohmann_json CONAN_PKG::qt)

# Tests
set(TESTS
    tests/main.cc
    tests/test_time_series.cc
)

add_executable(cute.data.test ${TESTS})
target_link_libraries(cute.data.test PUBLIC cute.data topic CONAN_PKG::gtest)
gtest_discover_tests(cute.data.test)