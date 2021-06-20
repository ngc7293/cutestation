#include <iostream>

#include <gtest/gtest.h>

#include <log/log.hh>
#include <log/ostream_logsink.hh>
#include <net/net.hh>

int main(int argc, const char* argv[])
{
    int rc;

    logging::OstreamLogSink cout(std::cout);
    logging::Log::get().addSink(&cout);

    if (!net::init()) {
        return -1;
    }

    testing::InitGoogleTest(&argc, (char**)argv);
    rc = RUN_ALL_TESTS();

    net::cleanup();
    return rc;
}