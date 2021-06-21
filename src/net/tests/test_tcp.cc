#include <gtest/gtest.h>

#include <future>
#include <thread>

#include <net/server.hh>
#include <net/socket.hh>
#include <util/test.hh>

TEST_WINDOWS(tcp_server, listen_succeeds)
{
    net::server server;

    std::future<bool> ret = std::async(std::launch::async, [&server]() {
        return server.listen<net::tcp>("0.0.0.0", 25000);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    server.close();

    EXPECT_TRUE(ret.get());
}

TEST_WINDOWS(tcp_server, sockets_can_connect)
{
    net::server server;
    net::socket socket;

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen<net::tcp>("0.0.0.0", 25001);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_TRUE(socket.connect<net::tcp>("127.0.0.1", 25001));

    server.close();
    a.wait();
}

TEST_WINDOWS(tcp_server, server_creates_new_socket)
{
    net::server server;
    net::socket socket;
    std::string line;

    server.on_connection([](net::socket* socket) {
        std::string line;

        *socket << "passed" << std::endl;
        std::getline(*socket, line);

        EXPECT_EQ(line, "passed");

        delete socket;
    });

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen<net::tcp>("0.0.0.0", 25002);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    socket.connect<net::tcp>("127.0.0.1", 25002);

    std::getline(socket, line);
    socket << "passed" << std::endl;

    EXPECT_EQ(line, "passed");

    server.close();
    a.wait();
}

TEST_WINDOWS(tcp_socket, socket_connect_fails_with_no_server)
{
    net::socket socket;

    EXPECT_FALSE(socket.connect<net::tcp>("127.0.0.1", 25003));
}