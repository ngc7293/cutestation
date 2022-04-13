cmake_minimum_required(VERSION 3.17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

cmake_policy(SET CMP0100 NEW)

set(SOURCES
    app.hh
    window.hh
    window_factory.hh
    app.cc
    window.cc
    main.cc
    window_factory.cc
)

SET(UI
    ui/window.ui
)

add_executable(cute ${SOURCES} ${HEADERS})
target_standard_compile_flags(cute)
target_link_libraries(cute PUBLIC cute.widgets cute.data cute.io cute.log cute.util CONAN_PKG::nlohmann_json CONAN_PKG::qt)

set_target_properties(cute PROPERTIES INSTALL_RPATH "\$ORIGIN/../lib")
install(TARGETS cute DESTINATION bin)
install_qt(PLATFORM LIBS Charts Core Gui OpenGL OpenGLWidgets Widgets LIBS_LINUX DBus XcbQpa)