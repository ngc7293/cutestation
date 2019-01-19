#include "rpc/rpcserver.hh"

RPCServer::RPCServer()
{
}

RPCServer::~RPCServer()
{
}

void RPCServer::add(std::string method, (void)(*callback)(void* self, nlohmann::json params))
{
    methods_.insert_or_assign(method, callback);
}

void RPCServer::remove(std::string method)
{
    methods_.erase(method);
}

void RPCServer::call(std::string method, nlohmann::json params)
{
    (void)(*callback)(void* self, nlohmann::json params) = methods_.find(method);
    callback(params);
}