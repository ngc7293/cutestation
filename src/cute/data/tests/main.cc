#include <gtest/gtest.h>

#include <log/log.hh>
#include <log/ostream_logsink.hh>

int main(int argc, const char* argv[])
{
    logging::OstreamLogSink cout(std::cout);
    logging::Log::get().addSink(&cout);

    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}