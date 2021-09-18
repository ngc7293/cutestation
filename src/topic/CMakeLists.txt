cmake_minimum_required(VERSION 3.17.0)

SET(HEADERS
    inc/topic/callback.hh
    inc/topic/publisher.hh
    inc/topic/subscribe_info.hh
    inc/topic/subscriber.hh
    src/global_topic_manager.hh
    src/local_topic_manager.hh
    src/topic_manager.hh
    src/topic.hh
)

set(SOURCES
    src/publisher.cc
    src/subscriber.cc
    src/local_topic_manager.cc
    src/global_topic_manager.cc
    src/topic_manager.cc
    src/topic.cc
)

# Target
add_library(topic STATIC ${SOURCES} ${HEADERS})
target_include_directories(topic PUBLIC inc PRIVATE src)
target_standard_compile_flags(topic)

# Tests
set(TESTS
    tests/main.cc
    tests/test_pubsub.cc
)

add_executable(topic.test ${TESTS})
target_standard_compile_flags(topic.test)
target_link_libraries(topic.test PUBLIC topic CONAN_PKG::gtest)
gtest_discover_tests(topic.test)