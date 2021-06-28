cmake_minimum_required(VERSION 3.17)

set(SOURCES
    src/series_factory.cc
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
target_include_directories(cute.data PUBLIC inc/ PRIVATE src/)
target_standard_compile_flags(cute)
target_link_libraries(cute.data PUBLIC cute.log cute.proto topic cute.util CONAN_PKG::nlohmann_json CONAN_PKG::qt)

# Tests
set(TESTS
    tests/main.cc
    tests/test_time_series.cc
)

add_executable(cute.data.test ${TESTS})
target_standard_compile_flags(cute.data.test)
target_link_libraries(cute.data.test PUBLIC cute.data topic CONAN_PKG::gtest)
gtest_discover_tests(cute.data.test)