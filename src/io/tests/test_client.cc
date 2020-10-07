#include <gtest/gtest.h>

#include <future>
#include <string>
#include <sstream>
#include <functional>

#include <io/client.hh>
#include <log/log.h>
#include <net/unix_socket.h>
#include <net/unix_server.h>
#include <proto/packet.h>
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
    net::unix_server server;
    std::shared_ptr<net::socket> server_socket;

    server.on_connection([&server_socket](net::unix_socket* s) {
        std::shared_ptr<net::socket> ios(s);
        server_socket = ios;

        cute::io::Client client(ios);
        client.run();
    });

    auto a = std::async(std::launch::async, [&server]() {
        if (!server.listen("/tmp/cute.io.test")) {
            EXPECT_TRUE(false);
            return false;
        }
        return true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    cute::proto::Packet packet;
    cute::proto::Handshake handshake;
    cute::proto::Data data;
    cute::proto::DelimitedPacketStream stream(packet);

    net::unix_socket client_socket;
    EXPECT_TRUE(client_socket.connect("/tmp/cute.io.test"));

    packet.set_allocated_handshake(&handshake);
    cute::proto::makeHandshake(handshake, "test", {{"cute.io.test.command.bool", typeid(bool)}});
    client_socket << stream << std::flush;
    packet.release_handshake();

    int count = 0;
    MockSubscriber subscriber;
    subscriber.callSubscribe<bool>("cute.io.test.bool", [&count](const auto& t, const auto& v) {
        EXPECT_TRUE(v);
        EXPECT_EQ(t.count(), 1000000);
        count++;
    });

    packet.set_allocated_data(&data);
    cute::proto::makeData(data, {{"cute.io.test.bool", 1, true}});
    client_socket << stream << std::flush;

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    packet.release_data();

    EXPECT_EQ(count, 1);

    client_socket.close();
    server.close();
    a.wait();
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

TEST(Client, server_closes)
{
    net::unix_server server;
    std::shared_ptr<net::socket> server_socket;

    server.on_connection([&server_socket](net::unix_socket* s) {
        EXPECT_TRUE(false);
        std::shared_ptr<net::socket> ios(s);
        server_socket = ios;

        cute::io::Client client(ios);
        client.run();
    });

    auto a = std::async(std::launch::async, [&server]() {
        if (!server.listen("/tmp/cute.io.test")) {
            EXPECT_TRUE(false);
            return false;
        }
        return true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    server.close();
    a.wait();
}