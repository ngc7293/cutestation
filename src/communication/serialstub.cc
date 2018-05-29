#include "communication/serialstub.hh"

#include <iostream>

#include <unistd.h>

SerialStub::SerialStub()
{
    file_.open("data/");
}

SerialStub::~SerialStub()
{
    file_.close();
}

int SerialStub::read_byte(uint8_t* dest, int retry)
{
    if (file_.eof()) {
        exit(1);
    }
    *dest = file_.get();
    usleep(10000);
    return 1;
}