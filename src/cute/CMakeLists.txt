cmake_minimum_required(VERSION 3.13)

set(HEADERS
    src/app.h
    src/configurator.h
    src/socket_dispatcher.h
    src/socket_connector.h
)

set(SOURCES
    src/app.cc
    src/main.cc
    src/configurator.cc
    src/socket_dispatcher.cc
    src/socket_connector.cc
)

SET(UI
    ui/app.ui
)

add_executable(cute ${SOURCES} ${HEADERS} ${UI})
set_property(TARGET cute PROPERTY CXX_STANDARD 20)
target_include_directories(cute PRIVATE src/)
target_link_libraries(cute PUBLIC cute.data cute.log cute.util cute.widgets Qt5::Core Qt5::Network Qt5::Widgets)
target_compile_options(cute PRIVATE -Wall -Wpedantic -Werror)
