#ifndef CUTE_IO_CLIENT_H_
#define CUTE_IO_CLIENT_H_

#include <memory>

#include <proto/packet.h>
#include <topic/publisher.hh>
#include <topic/subscriber.hh>

namespace cute::io {

class Client : public Subscriber, public Publisher {
public:
    Client(std::shared_ptr<std::iostream> socket);
    virtual ~Client();

    void run();

private:
    void onData(const proto::Data& data);
    void onHandshake(const proto::Handshake& handshake);

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif