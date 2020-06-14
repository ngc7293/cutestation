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
    src/node.hh
)

set( SOURCES
    src/publisher.cc
    src/subscriber.cc
    src/local_topic_manager.cc
    src/global_topic_manager.cc
    src/topic_manager.cc
    src/topic.cc
    src/node.cc
)

## Target
add_library(cute.topic STATIC ${SOURCES} ${HEADERS})

target_compile_features(cute.topic PUBLIC cxx_std_17)
target_include_directories(cute.topic PUBLIC inc PRIVATE src)
target_compile_options(cute.topic PRIVATE -Wall -Werror -Wpedantic)

## Tests
set( TESTS
    tests/main.cc
    tests/test_pubsub.cc
)

add_executable(cute.topic.test ${TESTS})
add_test(NAME cute.topic COMMAND cute.topic.test)

target_compile_options(cute.topic.test PUBLIC --coverage)
target_link_options(cute.topic.test PUBLIC --coverage)
target_link_libraries(cute.topic.test PUBLIC cute.topic gcov ${GTEST_LIBRARIES})

