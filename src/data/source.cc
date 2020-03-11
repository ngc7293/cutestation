#include "data/source.h"

#include <string>

#include "log.h"
#include "data/tree.h"
#include "data/node_finder.h"

namespace cute::data {

struct Source::Priv {
    std::string name = "";
    std::vector<std::string> commands;
};

Source::Source()
    : _d(*(new Priv))
{
}

Source::~Source()
{
    delete &_d;
}

void Source::close()
{
    Log::info(_d.name, "Disconnected.");
    for (const std::string& command : _d.commands) {
        NodeFinder finder(command);
        NodeSP node = finder.visit(Tree::root());

        if (node && node->command()) {
            node->command()->unregisterDataSource(shared_from_this());
        }
    }

}

void Source::receiveData(proto::DataSP data)
{
    for (const proto::Measurement& measurement : data->measurements()) {
        NodeFinder finder(measurement.source());
        NodeSP node = finder.visit(Tree::root());

        if (node) {
            node->series()->accept(measurement);
        }
    }
}

void Source::receiveHandshake(proto::HandshakeSP handshake)
{
    _d.name = handshake->name();
    Log::info(_d.name, "Received handshake.");

    for (const std::string& command : handshake->commands()) {
        NodeFinder finder(command);
        NodeSP node = finder.visit(Tree::root());

        if (node && node->command()) {
            _d.commands.push_back(command);
            node->command()->registerDataSource(shared_from_this());
        }
    }
}

} // namespaces