cmake_minimum_required(VERSION 3.13)

set(SOURCES
    src/button_widget.cc
    src/chart_widget.cc
    src/control_widget.cc
    src/single_value_widget.cc
    src/widget_factory.cc
    src/widget.cc
)

set(HEADERS
    inc/widgets/button_widget.h
    inc/widgets/chart_widget.h
    inc/widgets/control_widget.h
    inc/widgets/single_value_widget.h
    inc/widgets/widget_factory.h
    inc/widgets/widget.h
)

add_library(cute.widgets STATIC ${SOURCES} ${HEADERS})
set_property(TARGET cute.widgets PROPERTY CXX_STANDARD 20)
target_include_directories(cute.widgets PUBLIC inc/ PRIVATE src/)
target_compile_options(cute.widgets PRIVATE -Wall -Wpedantic -Werror)
target_link_libraries(cute.widgets cute.data cute.log cute.util Qt5::Core Qt5::Widgets Qt5::Charts)
