#include <gtest/gtest.h>

#include <future>
#include <sstream>
#include <thread>

#include <cute/io/dispatcher.hh>
#include <net/socket.hh>
#include <net/server.hh>
#include <util/test.hh>

class MockDispatcher : public cute::io::Dispatcher {
public:
    void start() override { }

    void callAdd(std::shared_ptr<net::closeable> ios) {
        add(ios);
    }
};

TEST(Dispatcher, closes_doesnt_hang)
{
    // We expect dispatcher.close() to hang if the net::closeable stream cannot
    // be closed : read() is a blocking operation for some streams (net::socket)
    MockDispatcher dispatcher;
    net::server server;
    net::socket socket;

    server.on_connection([&dispatcher](net::socket* socket) {
        std::shared_ptr<net::closeable> stream = std::shared_ptr<net::socket>(socket);
        dispatcher.callAdd(stream);
    });

    auto a = std::async(std::launch::async, [&server]() {
        return server.listen<net::tcp>("0.0.0.0", 42857);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    EXPECT_TRUE(socket.connect<net::tcp>("127.0.0.1", 42857));

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    dispatcher.close();

    server.close();
    a.wait();
}