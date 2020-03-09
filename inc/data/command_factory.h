#ifndef COMMAND_FACTORY_H_
#define COMMAND_FACTORY_H_

#include "nlohmann/json.hpp"

#include "command.h"
#include "tree.h"

using json = nlohmann::json;

namespace cute::data {

class CommandFactory {
public:
    static CommandSP build(Tree& tree, const json& config);
};

} // namespaces

#endif 