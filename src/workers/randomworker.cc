#include "workers/randomworker.hh"

#include <iostream>
#include <unistd.h>

RandomWorker::RandomWorker()
    : internal_(nullptr)
{
}

RandomWorker::~RandomWorker()
{
}

void RandomWorker::start()
{
}

void RandomWorker::run()
{
    std::cout << "Starting RandomWorker thread" << std::endl;

    while (!quit_) {
        rapidjson::Document* payload = new rapidjson::Document();
        rapidjson::Value name(rapidjson::kStringType);
        rapidjson::Value value(rapidjson::kNumberType);
        name.SetString("altitude");
        value.SetInt(rand() % 200);
        payload->SetObject();
        payload->AddMember("name", name, payload->GetAllocator());
        payload->AddMember("value", value, payload->GetAllocator());

        Message* msg = new Message(payload);
        emit messageReady(msg);
        usleep(10*1000);
    }
    std::cout << "Stopping RandomWorker thread" << std::endl;
}

void RandomWorker::stop()
{
    quit_ = true;
    internal_->join();
    delete internal_;
    internal_ = nullptr;
}