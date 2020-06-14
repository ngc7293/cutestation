cmake_minimum_required(VERSION 3.13)

SET( PROTO
    packet.proto
)

protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTO})

set_property(SOURCE ${PROTO_HEADERS} PROPERTY SKIP_AUTOGEN ON)
set_property(SOURCE ${PROTO_SOURCES} PROPERTY SKIP_AUTOGEN ON)

add_library(cute.proto STATIC ${PROTO_SOURCES} ${PROTO_HEADERS})
target_include_directories(cute.proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(cute.proto PUBLIC protobuf::libprotobuf)
