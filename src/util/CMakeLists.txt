cmake_minimum_required(VERSION 3.13)

set(HEADERS
    inc/util/util.h
)

set(SOURCES
    src/util.cc
)

add_library(cute.util STATIC ${SOURCES} ${HEADERS})
set_property(TARGET cute.util PROPERTY CXX_STANDARD 20)
target_include_directories(cute.util PUBLIC inc/ PRIVATE src/)
target_compile_options(cute.util PRIVATE -Wall -Wpedantic -Werror)
target_link_libraries(cute.util PUBLIC Qt5::Core)
