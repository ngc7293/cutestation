#include <gtest/gtest.h>

#include <thread>

#include <io/unix_dispatcher.hh>
#include <net/socket.hh>
#include <topic/mock.hh>

TEST(UnixDispatcher, creates_a_valid_unix_socket)
{
    cute::io::UnixDispatcher dispatcher("/tmp/cute.io.test.unix_dispatcher");
    dispatcher.run();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    net::socket socket;
    EXPECT_TRUE(socket.connect<net::unix>("/tmp/cute.io.test.unix_dispatcher"));

    dispatcher.close();
}

TEST(UnixDispatcher, creates_a_valid_client)
{
    int count = 0;
    MockSubscriber subscriber;

    cute::proto::Packet packet;
    cute::proto::DelimitedPacketStream stream(packet);

    cute::io::UnixDispatcher dispatcher("/tmp/cute.io.test.unix_dispatcher");
    net::socket socket;

    cute::proto::makeData(*packet.mutable_data(), {{"cute.io.test.topic", 1, true}});
    subscriber.callSubscribe<bool>("cute.io.test.topic", [&count](const auto& t, const bool& v) {
        count = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    });

    dispatcher.run();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_TRUE(socket.connect<net::unix>("/tmp/cute.io.test.unix_dispatcher"));
    socket << stream << std::flush;

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_EQ(count, 1);
    dispatcher.close();
}