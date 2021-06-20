#include <gtest/gtest.h>

#include <thread>

#include <io/socket_dispatcher.hh>
#include <net/socket.hh>
#include <topic/subscriber.hh>

TEST(SocketDispatcher, creates_a_valid_unix_socket)
{
    cute::io::SocketDispatcher dispatcher;

    dispatcher.set_socket_path("/tmp/cute.io.test.socket_dispatcher");
    dispatcher.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    net::socket socket;
    EXPECT_TRUE(socket.connect<net::unix>("/tmp/cute.io.test.socket_dispatcher"));

    dispatcher.close();
}

TEST(SocketDispatcher, DISABLED_creates_a_valid_tcp_socket)
{
    cute::io::SocketDispatcher dispatcher;

    dispatcher.set_socket_address("0.0.0.0", 25000);
    dispatcher.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    net::socket socket;
    EXPECT_TRUE(socket.connect<net::tcp>("127.0.0.1", 25000));

    dispatcher.close();
}

TEST(SocketDispatcher, wont_start_if_already_running)
{
    cute::io::SocketDispatcher dispatcher;
    net::socket socket;

    dispatcher.set_socket_path("/tmp/cute.io.test.socket_dispatcher");
    dispatcher.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    dispatcher.set_socket_path("/tmp/cute.io.test.socket_dispatcher.bad");
    dispatcher.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_FALSE(socket.connect<net::unix>("/tmp/cute.io.test.socket_dispatcher.bad"));
    dispatcher.close();
}

TEST(SocketDispatcher, creates_a_valid_client)
{
    int count = 0;
    topic::Subscriber subscriber;

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    cute::io::SocketDispatcher dispatcher;
    net::socket socket;

    cute::proto::makeData(*packet.mutable_data(), {{"cute.io.test.topic", 1, true}});
    subscriber.subscribe<bool>("cute.io.test.topic", [&count](const auto& t, const bool& /*v*/) {
        count = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(t).count());
    });

    dispatcher.set_socket_path("/tmp/cute.io.test.socket_dispatcher");
    dispatcher.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_TRUE(socket.connect<net::unix>("/tmp/cute.io.test.socket_dispatcher"));
    socket << stream << std::flush;

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_EQ(count, 1);
    dispatcher.close();
}