#include "communication/serialstub.hh"

#include <unistd.h>

SerialStub::SerialStub()
{
    file.open("dump");
}

SerialStub::~SerialStub()
{
    file.close();
}

SerialStub& operator>>(SerialStub& serial, uint8_t& val)
{
    if (serial.file.eof()) {
        exit(1);
    }
    usleep(10000);
    val = serial.file.get();
}