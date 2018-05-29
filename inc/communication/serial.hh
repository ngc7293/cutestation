#ifndef SERIAL_H
#define SERIAL_H

#include <string>

#include <cstdint>

class Serial {
protected:
    bool error_;

public:
    Serial();

    virtual int read_byte(uint8_t* dest, int retry = 0) = 0;

    friend Serial& operator>>(Serial& serial, uint8_t& val);

    bool error() const { return error_; };
};

#endif // SERIAL_H