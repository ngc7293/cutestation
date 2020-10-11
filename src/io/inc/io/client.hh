#ifndef CUTE_IO_CLIENT_HH_
#define CUTE_IO_CLIENT_HH_

#include <memory>

#include <net/stream.hh>
#include <proto/packet.hh>
#include <topic/publisher.hh>
#include <topic/subscriber.hh>

namespace cute::io {

class Client : public Subscriber, public Publisher {
public:
    Client(std::shared_ptr<net::closeable> socket);
    virtual ~Client();

    void run();
    void close();

private:
    void onData(const proto::Data& data);
    void onHandshake(const proto::Handshake& handshake);

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif