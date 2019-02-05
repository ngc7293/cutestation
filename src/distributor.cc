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

void Distributor::onMessage(Message* message)
{
    for (Widget* widget : widgets_) {
        widget->accept(*message);
    }
    delete message;
}
