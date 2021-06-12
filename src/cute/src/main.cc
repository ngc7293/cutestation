#include <iostream>

#include <QApplication>

#include <log/log.hh>
#include <log/ostream_logsink.hh>

#include "app.hh"

using namespace logging;

int main(int argc, char* argv[])
{
    /* App */
    logging::OstreamLogSink coutSink(std::cout);
    logging::Log::get().addSink(&coutSink);

    QApplication qapp(argc, argv);
    cute::App app;
    app.show();

    return qapp.exec();
}
