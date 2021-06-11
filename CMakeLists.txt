cmake_minimum_required(VERSION 3.17)
project(cute)

include("${CMAKE_BINARY_DIR}/conan_paths.cmake")
include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

## Libraries
include(conan_qt_executables_variables)
include(Qt5CoreMacros)
include(Qt5WidgetsMacros)

find_package(GTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

# if (UNIX)
#     add_custom_target(clean_gcda ALL COMMAND find -name "*.gcda" -delete COMMENT "Cleaning GCDA files")
#     add_custom_target(coverage COMMAND r -r ../src ./ -e ".*gtest.*" -e ".*/tests/.*" --html-details -o coverage.html)
# endif()