cmake_minimum_required(VERSION 3.1.0)
project(cute)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set( SOURCES
    src/app.cc
    src/data/node.cc
    src/data/tree.cc
    src/data/node_finder.cc
    src/main.cc
    src/policies/average_sampling_policy.cc
    src/policies/no_sampling_policy.cc
    src/policies/sampling_policy.cc
    src/proto/packet.pb.cc
    src/data/series.cc
    src/data/time_series.cc
    src/socket/socket_connector.cc
    src/socket/socket_dispatcher.cc
    src/util.cc
    src/widgets/chart_widget.cc
    src/widgets/widget.cc
)

SET( HEADERS
    inc/app.h
    inc/data/node.h
    inc/data/tree.h
    inc/data/node_finder.h
    inc/message_ingestor.h
    inc/policies/average_sampling_policy.h
    inc/policies/no_sampling_policy.h
    inc/policies/sampling_policy.h
    inc/proto/packet.pb.h
    inc/data/series.h
    inc/data/time_series.h
    inc/socket/socket_connector.h
    inc/socket/socket_dispatcher.h
    inc/util.h
    inc/widgets/chart_widget.h
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

# Protobuf, for messages
find_package(Protobuf REQUIRED)

# Nlohmann JSON, for config
find_package(nlohmann_json 3.7.0 REQUIRED)

add_executable(cute ${SOURCES} ${HEADERS} ${UI})
set_property(TARGET cute PROPERTY CXX_STANDARD 11)
target_link_libraries(cute Qt5::Widgets Qt5::Network Qt5::Charts protobuf::libprotobuf gcov nlohmann_json::nlohmann_json)
target_include_directories(cute PRIVATE inc)
target_compile_options(cute PRIVATE -Wall -Wpedantic)
