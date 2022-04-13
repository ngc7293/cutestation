cmake_minimum_required(VERSION 3.17)
project(cutestation VERSION 1.0.1)

include("${CMAKE_BINARY_DIR}/conan_paths.cmake")
include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

## Libraries
include(conan_qt_executables_variables)

if (UNIX)
    target_compile_options(CONAN_PKG::qt INTERFACE -fPIC)
elseif (WIN32)
    target_compile_options(CONAN_PKG::qt INTERFACE /wd5054)
endif()

find_package(GTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Installation stuff
if (UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "David Bourgault")
    set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/cutestation")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
elseif(MSVC)
    set(CPACK_GENERATOR "WIX")
endif()

include(CPack)
include(InstallRequiredSystemLibraries)

function(target_os_compile_options)
    cmake_parse_arguments(
        OS_COMPILE_OPTIONS
        ""
        "TARGET"
        "LINUX;WINDOWS;ALL"
        ${ARGN}
    )

    if (UNIX)
        target_compile_options(${OS_COMPILE_OPTIONS_TARGET} PRIVATE ${OS_COMPILE_OPTIONS_LINUX})
    endif()

    if (MSVC)
        target_compile_options(${OS_COMPILE_OPTIONS_TARGET} PRIVATE ${OS_COMPILE_OPTIONS_WINDOWS})
    endif()

    target_compile_options(${OS_COMPILE_OPTIONS_TARGET} PRIVATE ${OS_COMPILE_OPTIONS_ALL})
endfunction()

function(target_standard_compile_flags TARGET)
    target_os_compile_options(
        TARGET ${TARGET}
        LINUX -Wall -Werror -Wpedantic -Wno-unknown-pragmas
        WINDOWS /W4 /WX /wd4068
    )

    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        if (UNIX)
            target_compile_options(${TARGET} PRIVATE --coverage)
            target_link_options(${TARGET} PRIVATE --coverage)
            target_link_libraries(${TARGET} PUBLIC gcov)
        endif()
    endif()

    target_compile_features(${TARGET} PUBLIC cxx_std_20)
endfunction()

function(install_lib)
    cmake_parse_arguments(
        INSTALL_LIB
        ""
        "RPATH;DESTINATION;FILE;FROM"
        "ALIAS"
        ${ARGN}
    )

    set(INSTALL_LIB_FILES "")
    foreach(F ${INSTALL_LIB_FILE} ${INSTALL_LIB_ALIAS})
        list(APPEND INSTALL_LIB_FILES ${INSTALL_LIB_FROM}/${F})
    endforeach()

    install(FILES ${INSTALL_LIB_FILES} DESTINATION ${INSTALL_LIB_DESTINATION})

    if(INSTALL_LIB_RPATH)
        install(CODE "execute_process(COMMAND chrpath -r ${INSTALL_LIB_RPATH} ${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB_DESTINATION}/${INSTALL_LIB_FILE})")
    else()
        install(CODE "execute_process(COMMAND chrpath -d ${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB_DESTINATION}/${INSTALL_LIB_FILE})")
    endif()

endfunction()

function(install_qt)
    cmake_parse_arguments(
        INSTALL_QT
        ""
        ""
        "LIBS;LIBS_LINUX;LIBS_WINDOWS"
        ${ARGN}
    )

    if(UNIX)
        foreach(QTLIB ${INSTALL_QT_LIBS} ${INSTALL_QT_LIBS_LINUX})
            install_lib(
                FROM ${CONAN_QT_ROOT}/lib
                FILE libQt6${QTLIB}.so.6.2.4 ALIAS libQt6${QTLIB}.so.6
                DESTINATION lib
                RPATH "\$ORIGIN"
            )
            
        endforeach()

        install_lib(
            FROM ${CONAN_QT_ROOT}/res/archdatadir/plugins/platforms
            FILE libqxcb.so
            DESTINATION bin/platforms
            RPATH ${CMAKE_INSTALL_PREFIX}/lib
        )

        install_lib(
            FROM ${CONAN_QT_ROOT}/res/archdatadir/plugins/xcbglintegrations
            FILE libqxcb-glx-integration.so
            DESTINATION bin/xcbglintegrations
            RPATH ${CMAKE_INSTALL_PREFIX}/lib
        )
    endif()

    if(MSVC)
        foreach(QTLIB ${INSTALL_QT_LIBS} ${INSTALL_QT_LIBS_WINDOWS})
            install(FILES ${CONAN_QT_ROOT}/bin/Qt6${QTLIB}.dll DESTINATION bin)
        endforeach()

        install(
            FILES
                ${CONAN_QT_ROOT}/res/archdatadir/plugins/platforms/qwindows.dll
            DESTINATION
                bin/platforms
        )

        install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION bin)
    endif()
endfunction()

if (UNIX)
    add_custom_target(clean_gcda ALL COMMAND find -name "*.gcda" -delete COMMENT "Cleaning GCDA files")
    add_custom_target(coverage COMMAND gcovr -r ../src ./ -e ".*gtest.*" -e ".*/tests/.*" --html-details -o coverage.html)
endif()

add_subdirectory(src)
