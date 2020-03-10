#include "data/command_factory.h"

#include "log.h"
#include "util.h"

#include "data/node_finder.h"
#include "data/series_factory.h"

namespace cute::data {

CommandSP CommandFactory::build(const json& config)
{
    CommandSP command;

    if (!has_string(config, "command")) {
        Log::err("CommandFactory", "missing or invalid configuration 'command'");
        return command;
    }

    NodeFinder creator(config["command"].get<std::string>(), true);
    NodeSP node = creator.visit(Tree::root());

    if (node->command()) {
        return node->command();
    }

    command = std::make_shared<Command>(config["command"].get<std::string>());
    node->setCommand(command);
    return node->command();
}

} // namespaces