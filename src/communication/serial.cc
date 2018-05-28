#include "communication/serial.hh"

Serial& operator>>(Serial& serial, uint8_t& val)
{
    serial.read_byte(&val, 1);
    return serial;
}