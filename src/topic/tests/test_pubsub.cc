#include <gtest/gtest.h>

// #include <topic/mock.hh>
#include <topic/publisher.hh>
#include <topic/subscriber.hh>

TEST(Publisher, publishes_works)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    int count = 0;
    bool ret;

    ret = sub.subscribe<double>("topic.test.publisher.publishes_works", [&count](const auto& /*t*/, const auto& /*v*/) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = pub.publish<double>("topic.test.publisher.publishes_works", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, 1);
}

TEST(Publisher, publishes_works_on_multiple_types)
{
    topic::Publisher pub;

    EXPECT_TRUE(pub.publish("topic.test.publisher.publishes_works_on_multiple_types.double", 1.0));
    EXPECT_TRUE(pub.publish("topic.test.publisher.publishes_works_on_multiple_types.string", "string"));
    EXPECT_TRUE(pub.publish("topic.test.publisher.publishes_works_on_multiple_types.nanoseconds", topic::time(0)));
    EXPECT_TRUE(pub.publish("topic.test.publisher.publishes_works_on_multiple_types.int", 1));
}

TEST(Publisher, publishes_works_on_user_defined_objects)
{
    topic::Publisher pub;
    topic::Subscriber sub;
    int value = 0;

    class Object {
        int foo;

    public:
        Object(int foo) : foo(foo) {}
        int bar() const { return foo; }
    };

    EXPECT_TRUE(sub.subscribe<Object>("topic.test.publisher.publishes_works_on_user_defined_objects", [&value](auto& /*t*/, auto& v) {
        value = v.bar();
    }));

    EXPECT_TRUE(pub.publish("topic.test.publisher.publishes_works_on_user_defined_objects", Object(2)));

    EXPECT_EQ(value, 2);
}

TEST(Publisher, publishes_fails_on_type_mismatch)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    int count = 0;
    bool ret;

    ret = sub.subscribe<double>("topic.test.publisher.publishes_fails_on_type_mismatch", [&count](const auto& /*t*/, const auto& /*v*/) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = pub.publish<int>("topic.test.publisher.publishes_fails_on_type_mismatch", 1);
    EXPECT_FALSE(ret);

    EXPECT_EQ(count, 0);
}

TEST(Subscriber, unsubscribes_works)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    int count = 0;
    bool ret;

    ret = sub.subscribe<double>("topic.test.subscriber.unsubscribe_works", [&count](const auto& /*t*/, const auto& /*v*/) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = sub.unsubscribe("topic.test.subscriber.unsubscribe_works");
    EXPECT_TRUE(ret);

    ret = pub.publish<double>("topic.test.subscriber.unsubscribe_works", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, 0);
}

TEST(Subscriber, second_subscribe_fails)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    int count = 0;
    bool ret;

    ret = sub.subscribe<double>("topic.test.subscriber.unsubscribe_works", [&count](const auto& /*t*/, const auto& /*v*/) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = sub.subscribe<double>("topic.test.subscriber.unsubscribe_works", [&count](const auto& /*t*/, const auto& /*v*/) {
        count--;
    });
    EXPECT_FALSE(ret);

    ret = pub.publish<double>("topic.test.subscriber.unsubscribe_works", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, 1);
}

TEST(Subscriber, subscribe_unsubscribe_subscribe)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    int count = 0;
    bool ret;

    ret = sub.subscribe<double>("topic.test.subscriber.subscribe_unsubscribe_subscribe", [&count](const auto& /*t*/, const auto& /*v*/) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = sub.unsubscribe("topic.test.subscriber.subscribe_unsubscribe_subscribe");
    EXPECT_TRUE(ret);

    ret = sub.subscribe<double>("topic.test.subscriber.subscribe_unsubscribe_subscribe", [&count](const auto& /*t*/, const auto& /*v*/) {
        count--;
    });
    EXPECT_TRUE(ret);

    ret = pub.publish<double>("topic.test.subscriber.subscribe_unsubscribe_subscribe", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, -1);
}

TEST(Subscriber, subscriber_unsubscribes_on_delete)
{
    topic::Subscriber* sub = new topic::Subscriber;
    topic::Publisher pub;
    bool ret;

    ret = sub->subscribe<double>("topic.test.subscriber.subscriber_unsubscribes_on_delete", [](const auto& /*t*/, const auto& /*v*/) {
        EXPECT_TRUE(false);
    });
    EXPECT_TRUE(ret);

    delete sub;
    ret = pub.publish<double>("topic.test.subscriber.subscriber_unsubscribes_on_delete", 1.0);
    EXPECT_TRUE(ret);
}

TEST(Subscriber, unsubscribe_fails_if_not_subscribed)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    bool ret;

    ret = sub.unsubscribe("topic.test.subscriber.subscriber_unsubscribes_on_delete");
    EXPECT_FALSE(ret);
}

TEST(Subscriber, cannot_subscribe_on_type_mistmatch)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    bool ret;
    int count = 0;

    ret = sub.subscribe<bool>("topic.test.topic_manager.topics_can_be_replaced_if_no_subscribers", [&count](const auto& /*t*/, const auto& /*v*/) {
        count++;
    });

    ret = sub.subscribe<int>("topic.test.topic_manager.topics_can_be_replaced_if_no_subscribers", [](const auto& /*t*/, const auto& /*v*/) {
        EXPECT_TRUE(false);
    });
    EXPECT_FALSE(ret);

    pub.publish<bool>("topic.test.topic_manager.topics_can_be_replaced_if_no_subscribers", 1);
    EXPECT_EQ(count, 1);
}

TEST(TopicManager, topics_can_be_replaced_if_no_subscribers)
{
    topic::Subscriber sub;
    topic::Publisher pub;
    int count = 0;

    EXPECT_TRUE(sub.subscribe<bool>("topic.test.topic_manager.topics_can_be_replaced_if_no_subscribers", [](const auto& /*t*/, const auto& /*v*/) {
        EXPECT_TRUE(false);
    }));

    EXPECT_TRUE(sub.unsubscribe("topic.test.topic_manager.topics_can_be_replaced_if_no_subscribers"));

    EXPECT_TRUE(sub.subscribe<int>("topic.test.topic_manager.topics_can_be_replaced_if_no_subscribers", [&count](const auto& /*t*/, const auto& /*v*/) {
        count++;
    }));

    pub.publish<int>("topic.test.topic_manager.topics_can_be_replaced_if_no_subscribers", 1);
    EXPECT_EQ(count, 1);
}