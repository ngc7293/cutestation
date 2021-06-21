cmake_minimum_required(VERSION 3.17)

set(HEADERS
    inc/net/socket.hh
    inc/net/stream.hh
    inc/net/server.hh
    inc/net/net.hh
)

if (UNIX)
    set(SOURCES
        src/unix/sockbuf.cc
        src/unix/socket.cc
        src/unix/server.cc
        src/unix/sockbuf.hh
        src/unix/net.cc
    )
endif()

if (WIN32)
    set(SOURCES
        src/windows/sockbuf.cc
        src/windows/socket.cc
        src/windows/server.cc
        src/windows/sockbuf.hh
        src/windows/net.cc
    )
endif()

add_library(net STATIC ${SOURCES} ${HEADERS})
target_include_directories(net PUBLIC inc/ PRIVATE src/)
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