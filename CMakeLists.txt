cmake_minimum_required(VERSION 3.1.0)
project(test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set( SOURCES
    src/app.cc
    src/data_node.cc
    src/data_tree.cc
    src/displayer.cc
    src/main.cc
    src/policies/no_sampling_policy.cc
    src/policies/sampling_policy.cc
    src/proto/packet.pb.cc
    src/series/series.cc
    src/series/time_series.cc
    src/socket/socket_connector.cc
    src/socket/socket_dispatcher.cc
    src/widgets/widget.cc
)

SET( HEADERS
    inc/app.h
    inc/data_node.h
    inc/data_tree.h
    inc/displayer.h
    inc/message_ingestor.h
    inc/policies/no_sampling_policy.h
    inc/policies/sampling_policy.h
    inc/proto/packet.pb.h
    inc/series/series.h
    inc/series/time_series.h
    inc/socket/socket_connector.h
    inc/socket/socket_dispatcher.h
    inc/util.h
    inc/widgets/widget.h
)

SET( UI
    ui/app.ui
)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Qt5
set (CMAKE_PREFIX_PATH /opt/Qt/5.12.1/gcc_64/)
find_package(Qt5 COMPONENTS Core Widgets Network Charts REQUIRED)

# Protobuf
find_package(Protobuf REQUIRED)

add_executable(test ${SOURCES} ${HEADERS} ${UI})
set_property(TARGET test PROPERTY CXX_STANDARD 11)
target_link_libraries(test Qt5::Widgets Qt5::Network Qt5::Charts protobuf::libprotobuf gcov)
target_include_directories(test PRIVATE inc)
