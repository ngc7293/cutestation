cmake_minimum_required(VERSION 3.13)

set(SOURCES
    src/fdbuf.cc
    src/tcp_server.cc
    src/tcp_socket.cc
    src/unix_server.cc
    src/unix_socket.cc
)

set(HEADERS
    inc/net/tcp_socket.h
    inc/net/tcp_server.h
    inc/net/unix_socket.h
    inc/net/unix_server.h
    src/fdbuf.h
)

add_library(net STATIC ${SOURCES} ${HEADERS})
set_property(TARGET net PROPERTY CXX_STANDARD 20)
target_include_directories(net PUBLIC inc/ PRIVATE src/)
target_compile_options(net PRIVATE -Wall -Wpedantic -Werror )
target_link_libraries(net PUBLIC cute.log)

## Tests
set( TESTS
    tests/main.cc
    tests/test_unix.cc
    tests/test_tcp.cc
)

add_executable(net.test ${TESTS})
add_test(NAME net COMMAND net.test)

target_compile_options(net.test PUBLIC )
target_link_options(net.test PUBLIC )
target_link_libraries(net.test PUBLIC net gcov gtest)