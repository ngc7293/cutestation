cmake_minimum_required(VERSION 3.17)

set(SOURCES
    src/fdbuf.cc
    src/socket.cc
    src/server.cc
)

set(HEADERS
    inc/net/socket.hh
    inc/net/stream.hh
    inc/net/server.hh
    src/fdbuf.hh
)

add_library(net STATIC ${SOURCES} ${HEADERS})
set_property(TARGET net PROPERTY CXX_STANDARD 20)
target_include_directories(net PUBLIC inc/ PRIVATE src/)
target_os_compile_options(TARGET net LINUX -Wall -Werror -Wpedantic)
target_link_libraries(net PUBLIC cute.log)

# Tests
set(TESTS
    tests/main.cc
    tests/test_stream.cc
    tests/test_tcp.cc
    tests/test_unix.cc
)

add_executable(net.test ${TESTS})
target_link_libraries(net.test PUBLIC net CONAN_PKG::gtest)
gtest_discover_tests(net.test)