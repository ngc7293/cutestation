cmake_minimum_required(VERSION 3.17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

cmake_policy(SET CMP0100 NEW)

set(SOURCES
    src/button_widget.cc
    src/control_widget.cc
    src/single_value_widget.cc
    src/widget_factory.cc
    src/widget.cc
    src/chart_widget.cc
)

set(HEADERS
    inc/widgets/button_widget.hh
    inc/widgets/chart_widget.hh
    inc/widgets/control_widget.hh
    inc/widgets/single_value_widget.hh
    inc/widgets/widget_factory.hh
    inc/widgets/widget.hh
)

add_library(cute.widgets STATIC ${SOURCES} ${HEADERS})
set_property(TARGET cute.widgets PROPERTY CXX_STANDARD 20)
target_include_directories(cute.widgets PUBLIC inc/ PRIVATE src/)
target_compile_options(cute.widgets PRIVATE -Wall -Wpedantic -Werror)
target_link_libraries(cute.widgets PUBLIC cute.data cute.log cute.util nlohmann_json::nlohmann_json Qt5::Core Qt5::Widgets Qt5::Charts)
