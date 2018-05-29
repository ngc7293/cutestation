#include "communication/serial.hh"

Serial::Serial()
    : error_(false)
{
}

Serial& operator>>(Serial& serial, uint8_t& val)
{
    serial.read_byte(&val, 1);
    return serial;
}