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
target_os_compile_options(TARGET cute.io LINUX -Wall -Werror -Wpedantic)
target_link_libraries(cute.io PUBLIC cute.log cute.util topic cute.proto net)

# Tests
set(TESTS
    tests/main.cc
    tests/test_client.cc
    tests/test_dispatcher.cc
    tests/test_socket_dispatcher.cc
)

add_executable(cute.io.test ${TESTS})
target_link_libraries(cute.io.test PUBLIC cute.io CONAN_PKG::gtest)
gtest_discover_tests(cute.io.test)