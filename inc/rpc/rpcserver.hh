#ifndef RPC_SERVER_HH
#define RPC_SERVER_HH

#include <map>
#include <string>

#include "lib/rapidjson/document.h"

class RPCServer {
public:
    typedef void (*procedure_t)(void* self, rapidjson::Document& params, rapidjson::Document& result, rapidjson::Document& error);

private:
    std::map<std::string, procedure_t> methods_;

public:
    RPCServer();
    virtual ~RPCServer();

    /* Add/Remove procedures */
    void add(std::string method, procedure_t);
    void remove(std::string method);

    /* Operate */
    void receive(std::string payload);
    void call(std::string method, rapidjson::Document& params);
};

#endif