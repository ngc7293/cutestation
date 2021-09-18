cmake_minimum_required(VERSION 3.17)
project(cute VERSION 1.0.0)

include("${CMAKE_BINARY_DIR}/conan_paths.cmake")
include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

## Libraries
include(conan_qt_executables_variables)
include(Qt5CoreMacros)
include(Qt5WidgetsMacros)

if (UNIX)
    target_compile_options(CONAN_PKG::qt INTERFACE -fPIC)
endif()

if (WIN32)
    target_compile_options(CONAN_PKG::qt INTERFACE /wd5054)
endif()

find_package(GTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Installation stuff
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "David Bourgault")
include(CPack)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/share/cute/lib")

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

    if (${CMAKE_BUILD_TYPE} MATCHES Debug)
        if (UNIX)
            target_compile_options(${TARGET} PRIVATE --coverage)
            target_link_options(${TARGET} PRIVATE --coverage)
            target_link_libraries(${TARGET} PUBLIC gcov)
        endif()
    endif()

    target_compile_features(${TARGET} PUBLIC cxx_std_20)
endfunction()

if (UNIX)
    add_custom_target(clean_gcda ALL COMMAND find -name "*.gcda" -delete COMMENT "Cleaning GCDA files")
    add_custom_target(coverage COMMAND gcovr -r ../src ./ -e ".*gtest.*" -e ".*/tests/.*" --html-details -o coverage.html)
endif()

add_subdirectory(src)