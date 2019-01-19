#ifndef RPC_SERVER_HH
#define RPC_SERVER_HH

#include <map>
#include <string>

#include "lib/json.hh"

class RPCServer {
private:
    std::map<std::string, void (*)(void*, nlohmann::json)> methods_;

public:
    RPCServer();
    virtual ~RPCServer();

    void add(std::string method, void (*callback)(void* self, nlohmann::json params));
    void remove(std::string method);

    void call(std::string method, nlohmann::json params);
};

#endif