cmake_minimum_required(VERSION 3.17)
project(cute)

add_subdirectory(libs)

## Libraries
# Qt5
set(CMAKE_PREFIX_PATH /opt/Qt/5.14.1/gcc_64/)
find_package(Qt5 COMPONENTS Core Widgets Network Charts REQUIRED)

# Protobuf, for messages
find_package(Protobuf REQUIRED)

# Nlohmann JSON, for config
find_package(nlohmann_json 3.9.0 REQUIRED)

# Google Tests
include(GoogleTest)
enable_testing()

# Uh
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

if (UNIX)
    add_custom_target(clean_gcda ALL COMMAND find -name "*.gcda" -delete COMMENT "Cleaning GCDA files")
    add_custom_target(coverage COMMAND gcovr -r ../src ./ -e ".*gtest.*" -e ".*/tests/.*" --html-details -o coverage.html)
endif()