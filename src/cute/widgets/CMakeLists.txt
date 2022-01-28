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
    range_mapping.cc
    range_mapping.hh
    spacer_widget.hh
    value_widget.cc
    value_widget.hh
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

set(TESTS
    tests/main.cc
    tests/test_range_mapping.cc
)

add_executable(cute.widgets.test ${TESTS})
target_standard_compile_flags(cute.widgets.test)
target_link_libraries(cute.widgets.test PUBLIC cute.widgets cute.log CONAN_PKG::protobuf CONAN_PKG::gtest)
gtest_discover_tests(cute.widgets.test)