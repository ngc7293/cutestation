#include <gtest/gtest.h>

#include <future>
#include <thread>

#include <net/unix_server.h>
#include <net/unix_socket.h>

TEST(unix_server, listen_succeeds)
{
    net::unix_server server;

    std::future<bool> ret = std::async(std::launch::async, [&server]() {
        return server.listen("/tmp/cute.net.test");
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    server.close();

    EXPECT_TRUE(ret.get());
}

TEST(unix_server, sockets_can_connect)
{
    net::unix_server server;
    net::unix_socket socket;

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("/tmp/cute.net.test");
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_TRUE(socket.connect("/tmp/cute.net.test"));

    server.close();
    a.wait();
}

TEST(unix_server, server_creates_new_socket)
{
    net::unix_server server;
    net::unix_socket socket;
    std::string line;

    server.on_connection([](net::unix_socket* socket) {
        std::string line;

        *socket << "passed" << std::endl;
        std::getline(*socket, line);

        EXPECT_EQ(line, "passed");

        delete socket;
    });

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("/tmp/cute.net.test");
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    socket.connect("/tmp/cute.net.test");

    std::getline(socket, line);
    socket << "passed" << std::endl;

    EXPECT_EQ(line, "passed");

    server.close();
    a.wait();
}

TEST(unix_socket, socket_connect_fails_with_no_server)
{
    net::unix_socket socket;

    EXPECT_FALSE(socket.connect("/tmp/cute.net.test"));
}