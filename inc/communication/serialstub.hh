#ifndef SERIALSTUB_H
#define SERIALSTUB_H

#include <fstream>

#include "communication/serial.hh"

class SerialStub : public Serial {
private:
    std::ifstream file;

public:
    SerialStub();
    ~SerialStub();

    // Operator overloads
    friend SerialStub& operator>>(SerialStub& serial, uint8_t& val);
};

#endif // SERIALSTUB_H