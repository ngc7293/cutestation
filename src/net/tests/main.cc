#include <iostream>

#include <gtest/gtest.h>

#include <log/log.hh>
#include <log/ostream_logsink.hh>

int main(int argc, const char* argv[])
{
    logging::OstreamLogSink cerr(std::cerr);
    logging::Log::get().addSink(&cerr);
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}