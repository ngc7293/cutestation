cmake_minimum_required(VERSION 3.17)

set(SOURCES
    average_value.cc
    average_value.hh
    dynamic_value.cc
    dynamic_value.hh
    no_sampling_policy.hh
    sampling_policy.hh
    series_factory.cc
    series_factory.hh
    series.hh
    time_series.cc
    time_series.hh
    value.hh
    value_factory.hh
    value_factory.cc
)

add_library(cute.data STATIC ${SOURCES})
target_standard_compile_flags(cute)
target_link_libraries(cute.data PUBLIC cute.log cute.proto topic cute.util CONAN_PKG::nlohmann_json CONAN_PKG::qt)

# Tests
set(TESTS
    tests/main.cc
    tests/test_time_series.cc
    tests/test_dynamic_value.cc
    tests/test_value_factory.cc
)

add_executable(cute.data.test ${TESTS})
target_standard_compile_flags(cute.data.test)
target_link_libraries(cute.data.test PUBLIC cute.data topic CONAN_PKG::gtest)
gtest_discover_tests(cute.data.test)