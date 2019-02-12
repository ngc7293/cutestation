#include "distributor.hh"

Distributor::Distributor()
{
}

Distributor& Distributor::get()
{
    static Distributor* instance_;
    if (!instance_) {
        instance_ = new Distributor();
    }
    return *instance_;
}

Distributor::~Distributor()
{
}

void Distributor::onData(Data* data)
{
    for (Widget* widget : widgets_) {
        widget->accept(*data);
    }
    delete data;
}
