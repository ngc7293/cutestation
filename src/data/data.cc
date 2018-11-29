#include "data/data.hh"

Data::Data(uint64_t timestamp)
    : timestamp_(timestamp)
{
    value_ = 0;
}

Data::~Data()
{
}