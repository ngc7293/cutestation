#include <gtest/gtest.h>

#include <future>
#include <string>
#include <sstream>
#include <functional>

#include <io/client.hh>
#include <proto/packet.hh>
#include <topic/subscriber.hh>

class MockSubscriber: public Subscriber {
public:
    template <typename T>
    bool callSubscribe(const std::string& name, std::function<void(const std::chrono::nanoseconds& t, const T& v)> callback)
    {
        return subscribe<T>(name, callback);
    }
};

class MockPublisher: public Publisher {
public:
    template <typename T>
    bool callPublish(const std::string& name, const T& v, const std::chrono::nanoseconds& t = std::chrono::high_resolution_clock::now().time_since_epoch())
    {
        return publish<T>(name, v, t);
    }
};

TEST(Client, publishes_data_when_receives_packet)
{
    std::shared_ptr<std::stringstream> ios = std::make_shared<std::stringstream>();
    cute::io::Client client(ios);

    cute::proto::Packet packet;
    cute::proto::Data data;
    cute::proto::DelimitedPacketStream stream(packet);

    int count = 0;
    MockSubscriber subscriber;
    subscriber.callSubscribe<bool>("cute.io.test.bool", [&count](const auto& t, const auto& v) {
        EXPECT_TRUE(v);
        EXPECT_EQ(t.count(), 1000000);
        count++;
    });

    cute::proto::makeData(*packet.mutable_data(), {{"cute.io.test.bool", 1, true}});
    *ios << stream;
    client.run();

    EXPECT_EQ(count, 1);
}

TEST(Client, sends_commands_on_callback)
{
    std::shared_ptr<std::stringstream> ios = std::make_shared<std::stringstream>();
    cute::io::Client client(ios);

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    cute::proto::makeHandshake(*packet.mutable_handshake(), "test", {{"cute.io.test.int.command", typeid(int)}});
    *ios << stream;
    client.run();
    ios->clear(); // Reset EOF flag

    MockPublisher publisher;
    publisher.callPublish("cute.io.test.int.command", 57);

    *ios >> stream;
    EXPECT_EQ(packet.data().measurements(0).int_(), 57);
}


TEST(Client, is_type_safe)
{
    std::shared_ptr<std::stringstream> ios = std::make_shared<std::stringstream>();
    cute::io::Client client(ios);

    int count = 0;
    MockSubscriber subscriber;
    subscriber.callSubscribe<bool>("cute.io.test.bool", [&count](const auto& t, const auto& v) {
        EXPECT_TRUE(v);
        count++;
    });

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    cute::proto::makeData(*packet.mutable_data(), {{"cute.io.test.bool", 1, true}});
    *ios << stream;
    client.run();

    EXPECT_EQ(count, 1);

    cute::proto::makeData(*packet.mutable_data(), {{"cute.io.test.bool", 1, std::string("not a bool")}});
    *ios << stream;
    client.run();

    EXPECT_EQ(count, 1);
}