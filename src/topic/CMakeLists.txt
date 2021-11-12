cmake_minimum_required(VERSION 3.17.0)

set(SOURCES
    callback.hh
    global_topic_manager.cc
    global_topic_manager.hh
    local_topic_manager.cc
    local_topic_manager.hh
    publisher.cc
    publisher.hh
    subscribe_info.hh
    subscriber.cc
    subscriber.hh
    topic_manager.cc
    topic_manager.hh
    topic.cc
    topic.hh
)

# Target
add_library(topic STATIC ${SOURCES} ${HEADERS})
target_standard_compile_flags(topic)

# Tests
set(TESTS
    tests/main.cc
    tests/test_pubsub.cc
)

add_executable(topic.test ${TESTS})
target_standard_compile_flags(topic.test)
target_link_libraries(topic.test PUBLIC topic CONAN_PKG::GTest)
gtest_discover_tests(topic.test)