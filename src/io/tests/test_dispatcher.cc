#include <gtest/gtest.h>

#include <future>
#include <sstream>
#include <thread>

#include <io/dispatcher.hh>
#include <net/unix_socket.hh>
#include <net/unix_server.hh>

class MockDispatcher : public cute::io::Dispatcher {
public:
    void run() override { }

    void callAdd(std::shared_ptr<net::closeable> ios) {
        add(ios);
    }
};

TEST(Dispatcher, closes_doesnt_hang)
{
    // We expect dispatcher.close() to hang if the net::closeable stream cannot
    // be closed : read() is a blocking operation for some streams (net::socket)
    MockDispatcher dispatcher;
    net::unix_server server;
    net::unix_socket socket;

    server.on_connection([&dispatcher](net::unix_socket* socket) {
        std::shared_ptr<net::closeable> stream = std::shared_ptr<net::unix_socket>(socket);
        dispatcher.callAdd(stream);
    });

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen("/tmp/cute.io.test");
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    EXPECT_TRUE(socket.connect("/tmp/cute.io.test"));

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    dispatcher.close();

    server.close();
    a.wait();
}