cmake_minimum_required(VERSION 3.17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

cmake_policy(SET CMP0100 NEW)

set(SOURCES
    button_widget.cc
    button_widget.hh
    chart_widget.cc
    chart_widget.hh
    compass_widget.cc
    compass_widget.hh
    number_value_widget.cc
    number_value_widget.hh
    spacer_widget.hh
    state_value_widget.cc
    state_value_widget.hh
    view_widget.cc
    view_widget.hh
    widget_factory.cc
    widget_factory.hh
    widget_grid.cc
    widget_grid.hh
    widget_group.cc
    widget_group.hh
    widget_group.hh
    widget.cc
    widget.hh
)

add_library(cute.widgets STATIC ${SOURCES} ${HEADERS} ${QT_SOURCES})
target_standard_compile_flags(cute.widgets)
target_link_libraries(cute.widgets PUBLIC cute.data cute.log cute.util CONAN_PKG::nlohmann_json CONAN_PKG::qt)
