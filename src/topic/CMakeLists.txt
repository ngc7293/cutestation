cmake_minimum_required(VERSION 3.16.0)
project(cute)

## FILES
SET( HEADERS
    inc/topic/callback.hh
    inc/topic/publisher.hh
    inc/topic/subscribe_info.hh
    inc/topic/subscriber.hh
    src/global_topic_manager.hh
    src/local_topic_manager.hh
    src/topic_manager.hh
    src/topic.hh
)

set( SOURCES
    src/publisher.cc
    src/subscriber.cc
    src/local_topic_manager.cc
    src/global_topic_manager.cc
    src/topic_manager.cc
    src/topic.cc
)

## Target
add_library(topic STATIC ${SOURCES} ${HEADERS})

target_compile_features(topic PUBLIC cxx_std_17)
target_include_directories(topic PUBLIC inc PRIVATE src)
target_compile_options(topic PRIVATE -Wall -Werror -Wpedantic)

## Tests
set( TESTS
    tests/main.cc
    tests/test_pubsub.cc
)

add_executable(topic.test ${TESTS})
gtest_discover_tests(topic.test)

target_compile_options(topic.test PUBLIC )
target_link_options(topic.test PUBLIC )
target_link_libraries(topic.test PUBLIC topic gcov gtest)