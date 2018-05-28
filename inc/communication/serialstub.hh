#ifndef SERIALSTUB_H
#define SERIALSTUB_H

#include <fstream>

#include "communication/serial.hh"

class SerialStub : public Serial {
private:
    std::ifstream file_;

public:
    SerialStub();
    ~SerialStub();

    virtual int read_byte(uint8_t * dest, int retry = 0);
};

#endif // SERIALSTUB_H