#include <gtest/gtest.h>

#include <future>
#include <thread>

#include <net/tcp_server.hh>
#include <net/tcp_socket.hh>

TEST(tcp_server, listen_succeeds)
{
    net::tcp_server server;

    std::future<bool> ret = std::async(std::launch::async, [&server]() {
        return server.listen("0.0.0.0", 25000);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    server.close();

    EXPECT_TRUE(ret.get());
}

TEST(tcp_server, sockets_can_connect)
{
    net::tcp_server server;
    net::tcp_socket socket;

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("0.0.0.0", 25000);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_TRUE(socket.connect("127.0.0.1", 25000));

    server.close();
    a.wait();
}

TEST(tcp_server, server_creates_new_socket)
{
    net::tcp_server server;
    net::tcp_socket socket;
    std::string line;

    server.on_connection([](net::tcp_socket* socket) {
        std::string line;

        *socket << "passed" << std::endl;
        std::getline(*socket, line);

        EXPECT_EQ(line, "passed");

        delete socket;
    });

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("0.0.0.0", 25000);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    socket.connect("127.0.0.1", 25000);

    std::getline(socket, line);
    socket << "passed" << std::endl;

    EXPECT_EQ(line, "passed");

    server.close();
    a.wait();
}

TEST(tcp_socket, socket_connect_fails_with_no_server)
{
    net::tcp_socket socket;

    EXPECT_FALSE(socket.connect("127.0.0.1", 25000));
}