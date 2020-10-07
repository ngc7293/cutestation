#include "proto/packet.h"

namespace cute::proto {

void makeData(proto::Data& data, std::initializer_list<_measurement_initializer> list)
{
    data.clear_measurements();

    for (const _measurement_initializer& init: list) {
        proto::Measurement& measurement = *(data.add_measurements());

        measurement.set_source(init.s);
        measurement.set_timestamp(init.t);

        if (init.v.type() == typeid(bool)) {
            measurement.set_bool_(std::any_cast<bool>(init.v));
        } else if (init.v.type() == typeid(int)) {
            measurement.set_int_(std::any_cast<int>(init.v));
        } else if (init.v.type() == typeid(double)) {
            measurement.set_float_(std::any_cast<double>(init.v));
        } else if (init.v.type() == typeid(std::string)) {
            measurement.set_string(std::any_cast<std::string>(init.v));
        } else {
            assert(false);
        }
    }
}

void makeHandshake(proto::Handshake& handshake, const std::string& name, std::initializer_list<_command_initializer> list)
{
    handshake.set_name(name);
    handshake.clear_commands();

    for (const _command_initializer& init: list) {
        proto::Handshake::Command& command = *(handshake.add_commands());

        command.set_name(init.n);

        if (init.t == typeid(bool)) {
            command.set_type(proto::Handshake_Command_Type_BOOL);
        } else if (init.t == typeid(int)) {
            command.set_type(proto::Handshake_Command_Type_INT);
        } else if (init.t == typeid(double)) {
            command.set_type(proto::Handshake_Command_Type_FLOAT);
        } else if (init.t == typeid(std::string)) {
            command.set_type(proto::Handshake_Command_Type_STRING);
        } else {
            assert(false);
        }
    }
}

}