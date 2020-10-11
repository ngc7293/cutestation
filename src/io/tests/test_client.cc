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
    int count = 0;

    MockSubscriber subscriber;

    std::shared_ptr<net::closeable> ios = std::make_shared<net::stringstream>();
    cute::io::Client client(ios);

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

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
    MockPublisher publisher;

    std::shared_ptr<net::closeable> ios = std::make_shared<net::stringstream>();
    cute::io::Client client(ios);

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    cute::proto::makeHandshake(*packet.mutable_handshake(), "test", {{"cute.io.test.int.command", typeid(int)}});
    *ios << stream;
    client.run();
    ios->clear(); // Reset EOF flag

    publisher.callPublish("cute.io.test.int.command", 57);

    *ios >> stream;
    EXPECT_EQ(packet.data().measurements().size(), 1);
    EXPECT_EQ(packet.data().measurements(0).value_case(), cute::proto::Measurement::ValueCase::kInt);
    EXPECT_EQ(packet.data().measurements(0).int_(), 57);
}

TEST(Client, handles_receiving_multiple_types)
{
    bool b = false;
    int i = 0;
    double f = 0.0f;
    std::string s = "";

    MockSubscriber subscriber;

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    std::shared_ptr<net::closeable> ios = std::make_shared<net::stringstream>();
    cute::io::Client client(ios);

    subscriber.callSubscribe<bool>("cute.io.test.bool", [&b](const auto& t, const auto& v) { b = v; });
    subscriber.callSubscribe<int>("cute.io.test.int", [&i](const auto& t, const auto& v) { i = v; });
    subscriber.callSubscribe<double>("cute.io.test.float", [&f](const auto& t, const auto& v) { f = v; });
    subscriber.callSubscribe<std::string>("cute.io.test.string", [&s](const auto& t, const auto& v) { s = v; });

    cute::proto::makeData(*packet.mutable_data(), {
        {"cute.io.test.bool", 1, true},
        {"cute.io.test.int", 1, 87},
        {"cute.io.test.float", 1, 3.1415},
        {"cute.io.test.string", 1, "cute"}
    });

    *ios << stream;
    client.run();

    EXPECT_EQ(b, true);
    EXPECT_EQ(i, 87);
    EXPECT_EQ(f, 3.1415);
    EXPECT_EQ(s, "cute");
}

TEST(Client, handles_sending_multiple_types)
{
    MockPublisher publisher;

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    std::shared_ptr<net::closeable> ios = std::make_shared<net::stringstream>();
    cute::io::Client client(ios);

    cute::proto::makeHandshake(*packet.mutable_handshake(), "test", {
        {"cute.io.test.bool", typeid(bool)},
        {"cute.io.test.int", typeid(int)},
        {"cute.io.test.float", typeid(double)},
        {"cute.io.test.string", typeid(std::string)}
    });
    *ios << stream;
    client.run();
    ios->clear();  // Reset EOF flag

    publisher.callPublish<bool>("cute.io.test.bool", true);
    publisher.callPublish<int>("cute.io.test.int", 87);
    publisher.callPublish<double>("cute.io.test.float", 3.1415);
    publisher.callPublish<std::string>("cute.io.test.string", "cute");

    *ios >> stream;
    EXPECT_EQ(packet.data().measurements(0).bool_(), true);
    *ios >> stream;
    EXPECT_EQ(packet.data().measurements(0).int_(), 87);
    *ios >> stream;
    EXPECT_EQ(packet.data().measurements(0).float_(), 3.1415);
    *ios >> stream;
    EXPECT_EQ(packet.data().measurements(0).string(), "cute");
}

TEST(Client, is_type_safe)
{
    int count = 0;

    MockSubscriber subscriber;

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    std::shared_ptr<net::closeable> ios = std::make_shared<net::stringstream>();
    cute::io::Client client(ios);

    subscriber.callSubscribe<bool>("cute.io.test.bool", [&count](const auto& t, const auto& v) {
        EXPECT_TRUE(v);
        count++;
    });

    cute::proto::makeData(*packet.mutable_data(), {{"cute.io.test.bool", 1, true}});
    *ios << stream;
    client.run();

    EXPECT_EQ(count, 1);

    cute::proto::makeData(*packet.mutable_data(), {{"cute.io.test.bool", 1, "not a bool"}});
    *ios << stream;
    client.run();

    EXPECT_EQ(count, 1);
}
