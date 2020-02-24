cmake_minimum_required(VERSION 3.7.0)
project(cute)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

## FILES
set( SOURCES
    src/app.cc
    src/configurator.cc
    src/data/node_finder.cc
    src/data/node.cc
    src/data/series_factory.cc
    src/data/series.cc
    src/data/time_series.cc
    src/data/tree.cc
    src/log.cc
    src/main.cc
    src/policies/average_sampling_policy.cc
    src/policies/no_sampling_policy.cc
    src/policies/sampling_policy.cc
    src/socket/socket_connector.cc
    src/socket/socket_dispatcher.cc
    src/util.cc
    src/widgets/chart_widget.cc
    src/widgets/single_value_widget.cc
    src/widgets/widget_factory.cc
    src/widgets/widget.cc
)

SET( HEADERS
    inc/app.h
    inc/configurator.h
    inc/data/node_finder.h
    inc/data/node.h
    inc/data/series_factory.h
    inc/data/series.h
    inc/data/time_series.h
    inc/data/tree.h
    inc/log.h
    inc/policies/average_sampling_policy.h
    inc/policies/no_sampling_policy.h
    inc/policies/sampling_policy.h
    inc/socket/socket_connector.h
    inc/socket/socket_dispatcher.h
    inc/util.h
    inc/widgets/chart_widget.h
    inc/widgets/single_value_widget.h
    inc/widgets/widget_factory.h
    inc/widgets/widget.h
)

SET( UI
    ui/app.ui
)

SET( PROTO
    proto/packet.proto
)

## Libraries
# Qt5
set(CMAKE_PREFIX_PATH /opt/Qt/5.14.1/gcc_64/)
find_package(Qt5 COMPONENTS Core Widgets Network Charts REQUIRED)

# Protobuf, for messages
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTO})

set_property(SOURCE ${PROTO_HEADERS} PROPERTY SKIP_AUTOGEN ON)
set_property(SOURCE ${PROTO_SOURCES} PROPERTY SKIP_AUTOGEN ON)

# Nlohmann JSON, for config
find_package(nlohmann_json 3.7.0 REQUIRED)

## Target
add_executable(cute ${SOURCES} ${HEADERS} ${PROTO_SOURCES} ${PROTO_HEADERS} ${UI})

set_property(TARGET cute PROPERTY CXX_STANDARD 17)

target_link_libraries(cute Qt5::Widgets Qt5::Network Qt5::Charts protobuf::libprotobuf nlohmann_json::nlohmann_json)
target_include_directories(cute PRIVATE inc ${PROTOBUF_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(cute PRIVATE -Wall -Wpedantic)
