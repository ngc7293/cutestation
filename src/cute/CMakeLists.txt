cmake_minimum_required(VERSION 3.13)

set(HEADERS
    src/app.hh
    src/window.hh
    src/window_factory.hh
)

set(SOURCES
    src/app.cc
    src/window.cc
    src/main.cc
    src/window_factory.cc
)

SET(UI
    ui/window.ui
)

add_executable(cute ${SOURCES} ${HEADERS} ${UI})
set_property(TARGET cute PROPERTY CXX_STANDARD 20)
target_include_directories(cute PRIVATE src/)
target_compile_options(cute PRIVATE -Wall -Wpedantic -Werror --coverage)
target_link_options(cute PRIVATE --coverage)
target_link_libraries(cute PUBLIC cute.widgets cute.data cute.io cute.log cute.util Qt5::Core Qt5::Network Qt5::Widgets)
