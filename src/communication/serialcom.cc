#include "communication/serialcom.hh"

#include <iostream>

#include <cstring>
#include <cerrno>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

SerialCom::SerialCom(std::string port, unsigned int baudrate)
    : port_(port)
    , baudrate_(baudrate)
{
    device_ = open(port_.c_str(), O_RDWR | O_NONBLOCK | O_NDELAY);
    if (device_ < 0) {
        std::cerr << "Error " << errno << " opening " << port_ << ": " << strerror(errno) << std::endl;
    }
}

SerialCom::~SerialCom()
{
    close(device_);
}

void SerialCom::config()
{
    // Configure serial
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(device_, &tty) != 0) {
        std::cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
    }

    // Set speed
    cfsetospeed(&tty, baudrate_);
    cfsetispeed(&tty, baudrate_);

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
    }
}

int SerialCom::read_byte(uint8_t * dest, int retry)
{
    int n = 0;
    int tries = retry;
    uint8_t buf[1];
    while (n != 1 && tries >= 0) {
        n = read(device_, buf, 1);
    }
    if (tries == 0) {
        return 0;
    }
    *dest = buf[0];
    return 1;
}