cmake_minimum_required(VERSION 3.7.0)
project(cute)

add_subdirectory(libs)

## Libraries
# Qt5
set(CMAKE_PREFIX_PATH /opt/Qt/5.14.1/gcc_64/)
find_package(Qt5 COMPONENTS Core Widgets Network Charts REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Protobuf, for messages
find_package(Protobuf REQUIRED)

# Nlohmann JSON, for config
find_package(nlohmann_json 3.7.0 REQUIRED)

# Google Tests
enable_testing()

# Uh
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

if (UNIX)
    add_custom_target(clean_gcda ALL COMMAND find -name "*.gcda" -delete COMMENT "Cleaning GCDA files")
    add_custom_target(coverage COMMAND gcovr -r ../src ./ -e ".*gtest.*" --html-details -o coverage.html)
endif()