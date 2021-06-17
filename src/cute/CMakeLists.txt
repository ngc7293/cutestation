cmake_minimum_required(VERSION 3.17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

cmake_policy(SET CMP0100 NEW)

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

add_executable(cute ${SOURCES} ${HEADERS})
target_include_directories(cute PRIVATE src/)
target_standard_compile_flags(cute)
target_link_libraries(cute PUBLIC cute.widgets cute.data cute.io cute.log cute.util CONAN_PKG::nlohmann_json CONAN_PKG::qt)
