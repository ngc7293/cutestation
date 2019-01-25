#include "rpc/rpcserver.hh"

RPCServer::RPCServer()
{
}

RPCServer::~RPCServer()
{
}

void RPCServer::add(std::string method, void (*callback)(void* self, nlohmann::json params, nlohmann::json& result, nlohmann::json& error))
{
    methods_.emplace(method, callback);
}

void RPCServer::remove(std::string method)
{
    methods_.erase(method);
}

void RPCServer::call(std::string method, nlohmann::json params)
{
    void (*callback)(void* self, nlohmann::json params) = methods_.find(method)->second;
    callback(this, params);
}