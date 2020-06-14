#include <gtest/gtest.h>

#include <topic/publisher.hh>
#include <topic/subscriber.hh>

class MockPublisher: public Publisher {
public:
    template <typename T>
    bool callPublish(const std::string& name, const T& value) { return publish(name, value); }
};

class MockSubscriber: public Subscriber {
public:
    template<typename T>
    bool callSubscribe(const std::string& name, std::function<void(const std::chrono::nanoseconds&, const T& value)> method) { return subscribe(name, method); }

    template<typename T>
    bool callUnsubscribe(const std::string& name) { return unsubscribe<T>(name); }
};

TEST(Publisher, publishes_works)
{
    MockSubscriber sub;
    MockPublisher pub;
    int count = 0;
    bool ret;

    ret = sub.callSubscribe<double>("topic.test.publisher.publishes_works", [&count](const auto& t, const auto& v) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = pub.callPublish<double>("topic.test.publisher.publishes_works", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, 1);
}

TEST(Publisher, publishes_works_on_multiple_types)
{
    MockPublisher pub;

    EXPECT_TRUE(pub.callPublish("topic.test.publisher.publishes_works_on_multiple_types.double", 1.0));
    EXPECT_TRUE(pub.callPublish("topic.test.publisher.publishes_works_on_multiple_types.string", "string"));
    EXPECT_TRUE(pub.callPublish("topic.test.publisher.publishes_works_on_multiple_types.nanoseconds", std::chrono::nanoseconds(0)));
    EXPECT_TRUE(pub.callPublish("topic.test.publisher.publishes_works_on_multiple_types.int", 1));
}

TEST(Publisher, publishes_works_on_user_defined_objects)
{
    MockPublisher pub;
    MockSubscriber sub;
    int value = 0;

    class Object {
        int foo;

    public:
        Object(int foo) : foo(foo) {}
        int bar() const { return foo; }
    };

    EXPECT_TRUE(sub.callSubscribe<Object>("topic.test.publisher.publishes_works_on_user_defined_objects", [&value](auto& t, auto& v) {
        value = v.bar();
    }));

    EXPECT_TRUE(pub.callPublish("topic.test.publisher.publishes_works_on_user_defined_objects", Object(2)));

    EXPECT_EQ(value, 2);
}

TEST(Publisher, publishes_fails_on_type_mismatch)
{
    MockSubscriber sub;
    MockPublisher pub;
    int count = 0;
    bool ret;

    ret = sub.callSubscribe<double>("topic.test.publisher.publishes_fails_on_type_mismatch", [&count](const auto& t, const auto& v) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = pub.callPublish<int>("topic.test.publisher.publishes_fails_on_type_mismatch", 1);
    EXPECT_FALSE(ret);

    EXPECT_EQ(count, 0);
}

TEST(Subscriber, unsubscribes_works)
{
    MockSubscriber sub;
    MockPublisher pub;
    int count = 0;
    bool ret;

    ret = sub.callSubscribe<double>("topic.test.subscriber.unsubscribe_works", [&count](const auto& t, const auto& v) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = sub.callUnsubscribe<double>("topic.test.subscriber.unsubscribe_works");
    EXPECT_TRUE(ret);

    ret = pub.callPublish<double>("topic.test.subscriber.unsubscribe_works", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, 0);
}

TEST(Subscriber, second_subscribe_fails)
{
    MockSubscriber sub;
    MockPublisher pub;
    int count = 0;
    bool ret;

    ret = sub.callSubscribe<double>("topic.test.subscriber.unsubscribe_works", [&count](const auto& t, const auto& v) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = sub.callSubscribe<double>("topic.test.subscriber.unsubscribe_works", [&count](const auto& t, const auto& v) {
        count--;
    });
    EXPECT_FALSE(ret);

    ret = pub.callPublish<double>("topic.test.subscriber.unsubscribe_works", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, 1);
}

TEST(Subscriber, subscribe_unsubscribe_subscribe)
{
    MockSubscriber sub;
    MockPublisher pub;
    int count = 0;
    bool ret;

    ret = sub.callSubscribe<double>("topic.test.subscriber.subscribe_unsubscribe_subscribe", [&count](const auto& t, const auto& v) {
        count++;
    });
    EXPECT_TRUE(ret);

    ret = sub.callUnsubscribe<double>("topic.test.subscriber.subscribe_unsubscribe_subscribe");
    EXPECT_TRUE(ret);

    ret = sub.callSubscribe<double>("topic.test.subscriber.subscribe_unsubscribe_subscribe", [&count](const auto& t, const auto& v) {
        count--;
    });
    EXPECT_TRUE(ret);

    ret = pub.callPublish<double>("topic.test.subscriber.subscribe_unsubscribe_subscribe", 1.0);
    EXPECT_TRUE(ret);

    EXPECT_EQ(count, -1);
}

TEST(Subscriber, subscriber_unsubscribes_on_delete)
{
    MockSubscriber* sub = new MockSubscriber;
    MockPublisher pub;
    bool ret;

    ret = sub->callSubscribe<double>("topic.test.subscriber.subscriber_unsubscribes_on_delete", [](const auto& t, const auto& v) {
        EXPECT_TRUE(false);
    });
    EXPECT_TRUE(ret);

    delete sub;
    ret = pub.callPublish<double>("topic.test.subscriber.subscriber_unsubscribes_on_delete", 1.0);
    EXPECT_TRUE(ret);
}

TEST(Subscriber, unsubscribe_fails_if_not_subscribed)
{
    MockSubscriber sub;
    MockPublisher pub;
    bool ret;

    ret = sub.callUnsubscribe<double>("topic.test.subscriber.subscriber_unsubscribes_on_delete");
    EXPECT_FALSE(ret);
}