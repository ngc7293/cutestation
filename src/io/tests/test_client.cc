#include <gtest/gtest.h>

#include <future>


#include <io/client.h>
#include <log/log.h>
#include <net/unix_socket.h>
#include <net/unix_server.h>
#include <proto/packet.h>

TEST(Client, pass)
{
    net::unix_server server;
    std::shared_ptr<net::socket> server_socket;

    server.on_connection([&server_socket](net::unix_socket* s) {
        std::shared_ptr<net::socket> ios(s);
        server_socket = ios;

        cute::io::Client client(ios);
        client.run();
        Log::info("socket", "returned from connection");
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
    cute::proto::DelimitedProtobufStream<cute::proto::Packet> stream(packet);


    net::unix_socket client_socket;
    EXPECT_TRUE(client_socket.connect("/tmp/cute.io.test"));

    packet.set_allocated_handshake(&handshake);
    handshake.set_name("test");
    client_socket << stream << std::flush;
    packet.release_handshake();

    packet.set_allocated_data(&data);
    data.add_measurements()->set_int_(56);
    client_socket << stream << std::flush;
    packet.release_data();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    server_socket->close();
    client_socket.close();
    server.close();
    a.wait();
}