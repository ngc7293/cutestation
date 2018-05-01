#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

#include <ctime>
#include <csignal>

#include <termios.h>

#include "communication/packet.hh"
#include "communication/serialcom.hh"
#include "communication/serialstub.hh"

#include "messages/message_defs.h"
#include "messages/message.hh"

void print(Packet& packet)
{
    Message* message = Message::fromPacket(packet);
    if (message && (message->id() == MSG_ID_GYRO || message->id() == MSG_ID_ACCELERATION)) {
        std::cout << message << std::endl;
    }
    delete message;
}

std::ofstream* file = nullptr;

int main(int argc, const char* argv[])
{
    std::string port = "/dev/ttyUSB0";
    bool dump = false;

    signal(SIGINT, [](int sig){ 
        if (file) {
            file->close();
            delete file;
        }
        exit(0); 
    });

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == "--port" || argv[i] == "-p") {
            port = argv[++i];
        }
        else if (argv[i] == "--dump" || "-d") {
            dump = true;
        }
    }

    SerialCom serial("/dev/ttyUSB0", B115200);
    //SerialStub serial;
    
    std::vector<Packet> packets;

    if (dump) {
        time_t now = time(NULL);
        struct tm* date = localtime(&now);
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << 1900 + date->tm_year << "-";
        ss << std::setw(2) << std::setfill('0') << date->tm_mon << "-";
        ss << std::setw(2) << std::setfill('0') << date->tm_mday << " ";
        ss << std::setw(2) << std::setfill('0') << date->tm_hour << ":";
        ss << std::setw(2) << std::setfill('0') << date->tm_min << ":";
        ss << std::setw(2) << std::setfill('0') << date->tm_sec << ".dump";
        file = new std::ofstream(ss.str(), std::ios::binary | std::ios::app);
    }


    while (true) {
        uint8_t b;
        serial >> b;

        if (b == 250) {
            packets.push_back(Packet());
        }

        if (file) {
            file->write((char*)&b, 1);
        }

        for (size_t i = 0; i < packets.size(); ++i) {
            packets[i] << b;
            switch (packets[i].validate()) {
            case Packet::CORRUPTED:
                packets.erase(packets.begin() + i);
                i--;
                break;
            case Packet::OK:
                print(packets[i]);
                packets.erase(packets.begin() + i);
                break;
            }
        }
    }
}
