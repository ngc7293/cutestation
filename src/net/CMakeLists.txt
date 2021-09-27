cmake_minimum_required(VERSION 3.17)

set(HEADERS
    socket.hh
    stream.hh
    server.hh
    net.hh
)

if (UNIX)
    set(SOURCES
        unix/sockbuf.cc
        unix/socket.cc
        unix/server.cc
        unix/sockbuf.hh
        unix/net.cc
    )
endif()

if (WIN32)
    set(SOURCES
        windows/sockbuf.cc
        windows/socket.cc
        windows/server.cc
        windows/sockbuf.hh
        windows/net.cc
    )
endif()

add_library(net STATIC ${SOURCES} ${HEADERS})
target_standard_compile_flags(net)
target_link_libraries(net PUBLIC cute.log)

# Tests
set(TESTS
    tests/main.cc
    tests/test_stream.cc
    tests/test_tcp.cc
    tests/test_unix.cc
)

add_executable(net.test ${TESTS})
target_standard_compile_flags(net.test)
target_link_libraries(net.test PUBLIC net cute.util cute.log CONAN_PKG::gtest)
gtest_discover_tests(net.test)