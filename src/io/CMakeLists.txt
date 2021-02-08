cmake_minimum_required(VERSION 3.17)

set(HEADERS
    inc/io/client.hh
    inc/io/dispatcher.hh
    inc/io/dispatcher_factory.hh
    inc/io/socket_dispatcher.hh
)

set(SOURCES
    src/client.cc
    src/dispatcher.cc
    src/dispatcher_factory.cc
    src/socket_dispatcher.cc
)

add_library(cute.io STATIC ${SOURCES} ${HEADERS})
set_property(TARGET cute.io PROPERTY CXX_STANDARD 20)
target_include_directories(cute.io PUBLIC inc/ PRIVATE src/)
target_compile_options(cute.io PRIVATE -Wall -Wpedantic -Werror --coverage)
target_link_libraries(cute.io PUBLIC cute.log cute.util topic cute.proto net)

# Tests
set( TESTS
    tests/main.cc
    tests/test_client.cc
    tests/test_dispatcher.cc
    tests/test_socket_dispatcher.cc
)

add_executable(cute.io.test ${TESTS})
gtest_discover_tests(cute.io.test)

target_compile_options(cute.io.test PUBLIC --coverage)
target_link_options(cute.io.test PUBLIC --coverage)
target_link_libraries(cute.io.test PUBLIC cute.io gcov gtest)