#include <iostream>

#include <QApplication>
#include <QStyleFactory>

#include <google/protobuf/stubs/common.h>

#include <log/log.hh>
#include <log/ostream_logsink.hh>
#include <net/net.hh>

#include "app.hh"

using namespace logging;

namespace {

struct LaunchArgs {
    std::filesystem::path config_path;
};

void usage()
{
    std::cout << R"~~(usage: cute <options>

optional arguments:
    -c, --config    Path to configuration JSON file. Defaults to "config.json".
    -h, --help      Displays this message.
)~~" << std::endl;
}

std::pair<LaunchArgs, bool> parseArgs(int argc, char* argv[], LaunchArgs args = {})
{
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0) {
            if (i < argc - 1) {
                args.config_path = argv[++i];
                continue;
            }
        }

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            usage();
            return {{}, true};
        }

        // Unknown switch
        std::cout << "unrecognized argument: " << argv[i] << std::endl;
        usage();
        return {{}, true};
    }

    return {args, false};
}

}

int main(int argc, char* argv[])
{
    auto exit = [](int rc) {
        google::protobuf::ShutdownProtobufLibrary();
        net::cleanup();
        return rc;
    };

    logging::OstreamLogSink coutSink(std::cout);
    logging::Log::get().addSink(&coutSink);

    auto [args, error] = parseArgs(argc, argv, { .config_path = "config.json" });
    if (error) {
        return exit(EXIT_FAILURE);
    }

    if (!std::filesystem::exists(args.config_path)) {
        logging::err("main") << "Could not find configuration file " << args.config_path << logging::endl;
        return exit(EXIT_FAILURE);
    }

    if (!net::init()) {
        return exit(EXIT_FAILURE);
    }

    QApplication qapp(argc, argv);
    qapp.setStyle(QStyleFactory::create("Fusion"));
    cute::App app(args.config_path);
    app.show();

    return exit(qapp.exec());
}
