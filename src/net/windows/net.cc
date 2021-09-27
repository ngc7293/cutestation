#ifdef _MSC_VER

#include "net/net.hh"

#include <WinSock2.h>

#include "log/log.hh"

namespace net {

bool init()
{
    static bool initiated = false;

    if (!initiated){
        WSADATA wsadata;

        if (WSAStartup(MAKEWORD(2, 2), &wsadata) == 0) {
            int major, minor, high_major, high_minor;

            initiated = true;
            minor = (wsadata.wVersion >> 8) & 0xff;
            major = (wsadata.wVersion & 0xff);
            high_minor = (wsadata.wHighVersion >> 8) & 0xff;
            high_major = (wsadata.wHighVersion & 0xff);

            logging::debug("net::init") << "Init'd WinSock2" 
                << logging::tag{"version", std::to_string(major) + "." + std::to_string(minor)} 
                << logging::tag{"high_version",  std::to_string(high_major) + "." + std::to_string(high_minor)}
                << logging::endl; 
        } else {
            char buf[128];
            int error = WSAGetLastError();

            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buf, sizeof(buf), NULL);
            logging::err("net::init") << "Failed to init WinSock2: " << buf << "'" << logging::tag{"errno", error} << logging::endl;
        }
    }

    return initiated;
}

void cleanup()
{
    WSACleanup();
}

} // namespaces

#endif