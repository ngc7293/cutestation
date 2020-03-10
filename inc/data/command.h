#ifndef DATA_COMMAND_H_
#define DATA_COMMAND_H_

#include "source.h"
#include "proto/packet.h"

namespace cute::data {

class Command {
private:
    std::vector<Source*> sources_;
    std::string name_;

public:
    Command(std::string name);
    ~Command();

    void registerDataSource(Source* source);

    template<typename T>
    void setValue(T value);
};

typedef std::shared_ptr<Command> CommandSP;

} // namespaces

#endif