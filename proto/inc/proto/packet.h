#ifndef CUTE_PROTO_PACKET_H_
#define CUTE_PROTO_PACKET_H_

#include <packet.pb.h>

namespace cute::proto {

template <class T>
class DelimitedProtobufStream {
public:
    DelimitedProtobufStream(T& message)
        : message(message)
    {
        buffer = nullptr;
        size = 0;
    }

    ~DelimitedProtobufStream()
    {
        if (buffer) {
            delete buffer;
        }
    }

    operator bool() const { return valid; }

    template <class U>
    friend std::istream& operator>>(std::istream& is, cute::proto::DelimitedProtobufStream<U>& stream);

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, cute::proto::DelimitedProtobufStream<U>& stream);

private:
    uint8_t* buffer;
    uint64_t size;
    T& message;
    bool valid;
};

template <class T>
std::istream& operator>>(std::istream& is, cute::proto::DelimitedProtobufStream<T>& stream)
{
    uint64_t size;
    is.read((char*)&size, sizeof(size));

    if (size > stream.size) {
        if (stream.buffer) {
            delete stream.buffer;
            stream.buffer = nullptr;
        }

        stream.buffer = new uint8_t[size];
    }

    is.read((char*)stream.buffer, size);
    stream.valid = stream.message.ParseFromArray(stream.buffer, size);

    return is;
}

template <class T>
std::ostream& operator<<(std::ostream& os, cute::proto::DelimitedProtobufStream<T>& stream)
{
    uint64_t size = stream.message.ByteSizeLong();
    os.write((char*)&size, sizeof(size));
    stream.message.SerializeToOstream(&os);
    return os;
}

}


#endif