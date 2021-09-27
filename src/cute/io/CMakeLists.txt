cmake_minimum_required(VERSION 3.17)

set(SOURCES
    client.cc
    client.hh
    dispatcher_factory.cc
    dispatcher_factory.hh
    dispatcher.cc
    dispatcher.hh
    socket_dispatcher.cc
    socket_dispatcher.hh
)

add_library(cute.io STATIC ${SOURCES})
target_standard_compile_flags(cute.io)
target_link_libraries(cute.io PUBLIC cute.log cute.util topic cute.proto net)

# Tests
set(TESTS
    tests/main.cc
    tests/test_client.cc
    tests/test_dispatcher.cc
    tests/test_socket_dispatcher.cc
)

add_executable(cute.io.test ${TESTS})
target_standard_compile_flags(cute.io.test)
target_link_libraries(cute.io.test PUBLIC cute.io cute.log CONAN_PKG::protobuf CONAN_PKG::gtest)
gtest_discover_tests(cute.io.test)