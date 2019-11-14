#include "model/series.hh"

Series::Series()
{
}

Series::~Series()
{
}

void Series::add(float data)
{
    data_.push_back(data);
    data_.erase(data_.begin());
    emit dataChanged();
}

void Series::clear()
{
    data_.clear();
}