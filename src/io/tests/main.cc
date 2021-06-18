#include <gtest/gtest.h>

#include <google/protobuf/stubs/common.h>

#include <log/log.hh>
#include <log/ostream_logsink.hh>

int main(int argc, const char* argv[])
{
    logging::OstreamLogSink cerr(std::cerr);
    logging::Log::get().addSink(&cerr);

    testing::InitGoogleTest(&argc, (char**)argv);
    int rc = RUN_ALL_TESTS();

    google::protobuf::ShutdownProtobufLibrary();
    return rc;
}