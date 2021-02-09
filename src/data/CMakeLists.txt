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
target_compile_options(cute.data PRIVATE -Wall -Wpedantic -Werror --coverage)
target_link_libraries(cute.data PUBLIC cute.log cute.proto topic cute.util nlohmann_json::nlohmann_json Qt5::Core Qt5::Widgets Qt5::Charts)

## Tests
set( TESTS
tests/main.cc
tests/test_time_series.cc
)

add_executable(cute.data.test ${TESTS})
gtest_discover_tests(cute.data.test)

target_compile_options(cute.data.test PRIVATE --coverage)
target_link_options(cute.data.test PRIVATE --coverage)
target_link_libraries(cute.data.test PUBLIC cute.data topic gcov gtest)