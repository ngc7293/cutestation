#include "data/source.h"

#include <string>

#include "log.h"
#include "data/tree.h"
#include "data/node_finder.h"

namespace cute::data {

struct Source::Priv {
    std::string name = "";
};

Source::Source()
    : _d(*(new Priv))
{
}

Source::~Source() {
    delete &_d;
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
    Log::debug(_d.name, "Reached receiveHandshake!");

    for (const std::string& command : handshake->commands()) {
        NodeFinder finder(command);
        NodeSP node = finder.visit(Tree::root());

        if (node && node->command()) {
            node->command()->registerDataSource(this);
        } else {
            Log::err("Source", "no command registered!");
        }
    }
}

} // namespaces