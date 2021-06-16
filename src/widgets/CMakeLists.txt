cmake_minimum_required(VERSION 3.17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

cmake_policy(SET CMP0100 NEW)

set(SOURCES
    src/button_widget.cc
    src/chart_widget.cc
    src/widget_factory.cc
    src/widget_group.cc
    src/widget_grid.cc
    src/widget.cc
    src/view_widget.cc
)

set(HEADERS
    inc/widgets/widget_group.hh
    inc/widgets/button_widget.hh
    inc/widgets/chart_widget.hh
    inc/widgets/widget_grid.hh
    inc/widgets/widget_group.hh
    inc/widgets/widget_factory.hh
    inc/widgets/view_widget.hh
    inc/widgets/widget.hh
)

add_library(cute.widgets STATIC ${SOURCES} ${HEADERS} ${QT_SOURCES})
set_property(TARGET cute.widgets PROPERTY CXX_STANDARD 20)
target_include_directories(cute.widgets PUBLIC inc/ PRIVATE src/)
target_os_compile_options(TARGET cute.widgets LINUX -Wall -Werror -Wpedantic -fPIC)
target_link_libraries(cute.widgets PUBLIC cute.data cute.log cute.util CONAN_PKG::nlohmann_json CONAN_PKG::qt)
