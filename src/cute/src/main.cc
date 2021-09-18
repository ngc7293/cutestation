#include <iostream>

#include <QApplication>
#include <QStyleFactory>

#include <google/protobuf/stubs/common.h>

#include <log/log.hh>
#include <log/ostream_logsink.hh>
#include <net/net.hh>

#include "app.hh"

using namespace logging;

int main(int argc, char* argv[])
{
    logging::OstreamLogSink coutSink(std::cout);
    logging::Log::get().addSink(&coutSink);

    if (!net::init()) {
        return -1;
    }

    QApplication qapp(argc, argv);
    qapp.setStyle(QStyleFactory::create("Fusion"));
    cute::App app;
    app.show();

    int rc = qapp.exec();

    google::protobuf::ShutdownProtobufLibrary();
    net::cleanup();
    return rc;
}
