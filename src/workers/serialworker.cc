#include "workers/serialworker.hh"

#include <iostream>

#include <termios.h>

#include "communication/serialcom.hh"
#include "communication/serialstub.hh"

SerialWorker::SerialWorker()
    : serial_(new SerialCom("/dev/ttyUSB0", B115200))
    , internal_(nullptr)
{
    quit_ = false;
}

SerialWorker::SerialWorker(Serial* serial)
    : serial_(serial)
{
    quit_ = false;
}

SerialWorker::~SerialWorker()
{
    if (internal_) {
        stop();
    }
}

void SerialWorker::start()
{
    internal_ = new std::thread(&SerialWorker::run, this);
}

void SerialWorker::run()
{
    std::cout << "Starting SerialWorker thread" << std::endl;
    std::vector<Packet> packets;

    while (!quit_) {
        uint8_t b;
        *serial_ >> b;
        if (b == 250) {
            packets.push_back(Packet());
        }

        for (size_t i = 0; i < packets.size(); ++i) {
            packets[i] << b;
            switch (packets[i].validate()) {
            case Packet::CORRUPTED:
                packets.erase(packets.begin() + i);
                i--;
                break;
            case Packet::OK:
                emit messageReady(Message::fromPacket(packets[i]));
                packets.erase(packets.begin() + i);
                break;
            }
        }
    }
    std::cout << "Stopping SerialWorker thread" << std::endl;
}

void SerialWorker::stop()
{
    quit_ = true;
    internal_->join();
    delete internal_;
    internal_ = nullptr;
}