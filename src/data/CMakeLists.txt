cmake_minimum_required(VERSION 3.13)

set(SOURCES
    src/no_sampling_policy.cc
    src/sampling_policy.cc
    src/series_factory.cc
    src/series.cc
    src/source.cc
    src/time_series.cc
)

set(HEADERS
    inc/data/series_factory.h
    inc/data/series.h
    inc/data/source.h
    inc/data/time_series.h
    src/no_sampling_policy.h
    inc/data/sampling_policy.h
)

add_library(cute.data STATIC ${SOURCES} ${HEADERS})
set_property(TARGET cute.data PROPERTY CXX_STANDARD 20)
target_include_directories(cute.data PUBLIC inc/ PRIVATE src/)
target_compile_options(cute.data PRIVATE -Wall -Wpedantic -Werror)
target_link_libraries(cute.data PUBLIC cute.log cute.proto cute.topic cute.util Qt5::Core Qt5::Widgets Qt5::Charts)
