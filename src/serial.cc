#include "serial.hh"

#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define PACKET_SIZE sizeof(radio_packet_t)
#define CRC_INDEX (PACKET_SIZE - 1)

Serial::Serial(QString device, Serializer* serializer)
{
    serializer_ = serializer;
    quit_ = false;
    connected_ = false;

    device_ = open(device.toStdString().c_str(), O_RDWR);
    if (device_ >= 0 && config()) {
        connected_ = true;
    } else {
        std::cerr << "[Serial] Could not open device " << device.toStdString() << std::endl;
    }
}

Serial::~Serial()
{
    close(device_);
}

void Serial::work()
{
    std::ofstream ofs;
    uint8_t bytes[PACKET_SIZE] = { 0 };

    time_t now = time(NULL);
    std::stringstream ss;
    ss << "dump+" << now << ".anirniq";
    ofs.open(ss.str(), std::ifstream::out | std::ifstream::binary);

    while (!quit_ && connected_) {
        int n = 0;

        while (n != 1 && !quit_) {
            n = read(device_, &bytes[PACKET_SIZE - 1], 1);
        }

        if (radio_compute_crc((radio_packet_t*)bytes) == bytes[CRC_INDEX]) {
            radio_packet_t packet;
            now = time(NULL);
            memcpy(&packet, bytes, PACKET_SIZE);
            serializer_->serialize(packet);
            ofs.write((char*)&time, sizeof(now));
            ofs.write((char*)&packet, sizeof(packet));
        }

        // Shift buffer left
        for (unsigned int i = 1; i < PACKET_SIZE; i++) {
            bytes[i - 1] = bytes[i];
        }
    }
}

bool Serial::config()
{
    // Configure serial
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(device_, &tty) != 0) {
        std::cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
        return false;
    }

    // Set speed
    cfsetospeed(&tty, B460800);
    cfsetispeed(&tty, B460800);

    // Various SerialCom port config
    tty.c_cflag &= ~PARENB; // Make 8n1
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS; // no flow control
    tty.c_lflag = 0; // no signaling chars, no echo, no canonical processing
    tty.c_oflag = 0; // no remapping, no delays
    tty.c_cc[VMIN] = 0; // read doesn't block
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

    tty.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    tty.c_oflag &= ~OPOST; // make raw

    // Set attributes
    tcflush(device_, TCIFLUSH);
    if (tcsetattr(device_, TCSANOW, &tty) != 0) {
        std::cerr << "Error " << errno << " from tcsetattr" << std::endl;
        return false;
    }

    return true;
}

void Serial::send(radio_packet_t packet)
{
    if (!connected_) {
        return;
    }

    int n = write(device_, &packet, sizeof(packet));

    if (n != sizeof(packet)) {
        std::cerr << "[Serial] Error writing packet, expected to send " << sizeof(packet) << " but sent " << n << "!" << std::endl;
    }
}