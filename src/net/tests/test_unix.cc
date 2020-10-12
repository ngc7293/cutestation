#include <gtest/gtest.h>

#include <future>
#include <thread>

#include <net/unix_server.hh>
#include <net/socket.hh>

#include <log/log.hh>

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
    net::socket socket;

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("/tmp/cute.net.test");
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_TRUE(socket.connect<net::unix>("/tmp/cute.net.test"));

    server.close();
    a.wait();
}

TEST(unix_socket, sockets_report_eof_after_closing)
{
    net::unix_server server;
    net::socket socket;

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("/tmp/cute.net.test");
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    EXPECT_TRUE(socket.connect<net::unix>("/tmp/cute.net.test"));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    socket.close();
    EXPECT_TRUE(socket.eof());

    server.close();
    a.wait();
}

TEST(unix_server, server_creates_new_socket)
{
    net::unix_server server;
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
        return server.listen("/tmp/cute.net.test");
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    socket.connect<net::unix>("/tmp/cute.net.test");

    std::getline(socket, line);
    socket << "passed" << std::endl;

    EXPECT_EQ(line, "passed");

    server.close();
    a.wait();
}

TEST(unix_socket, socket_connect_fails_with_no_server)
{
    net::socket socket;

    EXPECT_FALSE(socket.connect<net::unix>("/tmp/cute.net.test"));
}

TEST(unix_socket, socket_can_send_very_large_buffers)
{
    // Confirm that fdbuf's overflow() method works
    net::unix_server server;
    net::socket socket;
    char* buffer = new char[4096];
    int i = 0;
    for (; i < 4096; i++) {
        buffer[i] = 'a';
    }

    server.on_connection([](net::socket* socket) {
        std::string line;
        std::getline(*socket, line);

        EXPECT_EQ(line.size(), 4096);
        delete socket;
    });

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("/tmp/cute.net.test");
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    socket.connect<net::unix>("/tmp/cute.net.test");
    socket.write(buffer, 4096);
    socket << std::endl;
    server.close();
    a.wait();

    delete[] buffer;
}