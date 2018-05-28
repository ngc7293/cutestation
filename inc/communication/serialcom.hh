#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <string>

#include <cstdint>

#include "communication/serial.hh"

class SerialCom : public Serial {
private:
    std::string port_;
    unsigned int baudrate_;

    int device_;

public:
    SerialCom(std::string port, unsigned int baudrate);
    virtual ~SerialCom();

    virtual int read_byte(uint8_t* dest, int retry = 0);

    // Getters
    std::string port() const { return port_; }
    int baudrate() const { return baudrate_; }

private:
    void config();
};

#endif // SERIALCOM_H