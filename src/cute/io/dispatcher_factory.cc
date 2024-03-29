#include <util/json.hh>

#include "dispatcher_factory.hh"
#include "dispatcher.hh"
#include "socket_dispatcher.hh"

namespace cute::io {

template<>
std::shared_ptr<SocketDispatcher> DispatcherFactory::build(const json& config)
{
    std::shared_ptr<SocketDispatcher> dispatcher;

    std::string type, host;
    int port;

    type = config.at("type");

    if (type == "tcp") {
        if (!util::json::validate("SocketDispatcher", config,
            util::json::required(host, "host"),
            util::json::required(port, "port")
        )) {
            return dispatcher;
        }

        dispatcher = std::make_shared<SocketDispatcher>();
        dispatcher->set_socket_address(host, static_cast<std::uint16_t>(port));
    }

    if (type == "unix") {
#if (not defined _MSC_VER)
        if (!util::json::validate("SocketDispatcher", config,
            util::json::required(host, "path")
        )) {
            return dispatcher;
        }

        dispatcher = std::make_shared<SocketDispatcher>();
        dispatcher->set_socket_path(host);
#else
        logging::warn("DispatcherFactory") << "Unix sockets are not supported on Windows" << logging::endl;
        return dispatcher;
#endif
    }

    return dispatcher;
}

template<>
std::shared_ptr<Dispatcher> DispatcherFactory::build(const json& config)
{
    std::string type;

    if (!util::json::validate("Dispatcher", config,
        util::json::required(type, "type")
    )) {
        return std::shared_ptr<Dispatcher>();
    }

    if (type == "tcp" or type == "unix") {
        return build<SocketDispatcher>(config);
    }

    logging::warn("DispatcherFactory") << "Unknown dispatcher type '" << type << "'" << logging::endl;
    return std::shared_ptr<Dispatcher>();
}

template<>
std::vector<std::shared_ptr<Dispatcher>> DispatcherFactory::buildAll(const json& config)
{
    std::vector<std::shared_ptr<Dispatcher>> dispatchers;

    if (!config.is_array()) {
        return dispatchers;
    }

    for (const json& el : config) {
        if (std::shared_ptr<Dispatcher> dispatcher = build<Dispatcher>(el)) {
            dispatchers.push_back(dispatcher);
        }
    }

    return dispatchers;
}

}