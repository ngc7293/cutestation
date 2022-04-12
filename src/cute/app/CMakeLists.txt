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

install(TARGETS cute DESTINATION bin)

if (UNIX)
    install(
        FILES
            ${CONAN_QT_ROOT}/lib/libQt6Charts.so.6        ${CONAN_QT_ROOT}/lib/libQt6Charts.so.6.2.4
            ${CONAN_QT_ROOT}/lib/libQt6Core.so.6          ${CONAN_QT_ROOT}/lib/libQt6Core.so.6.2.4
            ${CONAN_QT_ROOT}/lib/libQt6DBus.so.6          ${CONAN_QT_ROOT}/lib/libQt6DBus.so.6.2.4
            ${CONAN_QT_ROOT}/lib/libQt6Gui.so.6           ${CONAN_QT_ROOT}/lib/libQt6Gui.so.6.2.4
            ${CONAN_QT_ROOT}/lib/libQt6OpenGL.so.6        ${CONAN_QT_ROOT}/lib/libQt6OpenGL.so.6.2.4
            ${CONAN_QT_ROOT}/lib/libQt6OpenGLWidgets.so.6 ${CONAN_QT_ROOT}/lib/libQt6OpenGLWidgets.so.6.2.4
            ${CONAN_QT_ROOT}/lib/libQt6Widgets.so.6       ${CONAN_QT_ROOT}/lib/libQt6Widgets.so.6.2.4
            ${CONAN_QT_ROOT}/lib/libQt6XcbQpa.so.6        ${CONAN_QT_ROOT}/lib/libQt6XcbQpa.so.6.2.4
        DESTINATION
            share/cute/lib
    )

    install(
        FILES
            ${CONAN_QT_ROOT}/res/archdatadir/plugins/platforms/libqxcb.so
        DESTINATION
            share/cute/bin/archdatadir/plugins/platforms
    )

    install(
        FILES
            ${CONAN_QT_ROOT}/res/archdatadir/plugins/xcbglintegrations/libqxcb-glx-integration.so
        DESTINATION
           share/cute/bin/archdatadir/plugins/xcbglintegrations
    )
elseif(MSVC)
    install(
        FILES
            ${CONAN_QT_ROOT}/bin/Qt6Charts.dll
            ${CONAN_QT_ROOT}/bin/Qt6Core.dll
            ${CONAN_QT_ROOT}/bin/Qt6Gui.dll
            ${CONAN_QT_ROOT}/bin/Qt6OpenGL.dll
            ${CONAN_QT_ROOT}/bin/Qt6OpenGLWidgets.dll
            ${CONAN_QT_ROOT}/bin/Qt6Widgets.dll
        DESTINATION
            bin
    )

    install(
        FILES
            ${CONAN_QT_ROOT}/res/archdatadir/plugins/platforms/qwindows.dll
        DESTINATION
            bin/platforms
    )

    install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION bin)
endif()