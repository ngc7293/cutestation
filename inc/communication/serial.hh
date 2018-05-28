#ifndef SERIAL_H
#define SERIAL_H

#include <string>

#include <cstdint>

class Serial {
public:
    virtual int read_byte(uint8_t* dest, int retry = 0) = 0;

    friend Serial& operator>>(Serial& serial, uint8_t& val);
};

#endif // SERIAL_H