#include "serializer.hh"

#include <iostream>

#include "distributor.hh"

#include "data/keyvaluedata.hh"
#include "data/numericaldata.hh"

#include "shared/interfaces/enums.h"
#include "shared/interfaces/id.h"

Serializer::Serializer()
{
}

Serializer::~Serializer() {}

QString charge_to_string(unsigned int status)
{
    switch (status) {
    case NO_CHARGE:
        return "None";
    case DROGUE_SENSE:
        return "Drogue";
    case MAIN_SENSE:
        return "Main";
    case BOTH_SENSE:
        return "Drogue+Main";
    }

    return "error";
}

QString rocket_to_string(unsigned int status)
{
    switch (status) {
    case INITIALISATION:
        return "Initialisation";
    case STANDBY_ON_PAD:
        return "Standby";
    case LAUNCH:
        return "Launch";
    case POWERED_ASCENT:
        return "Powered Ascent";
    case ENGINE_BURNOUT:
        return "Engine Burnout";
    case COASTING_ASCENT:
        return "Coasting Ascent";
    case APOGEE_REACHED:
        return "Apogee";
    case DROGUE_DEPLOYMENT:
        return "Drogue Deployment";
    case DROGUE_DESCENT:
        return "Drogue Descent";
    case MAIN_DEPLOYMENT:
        return "Main Deployment";
    case MAIN_DESCENT:
        return "Main Descent";
    case LANDING:
        return "Landing";
    case RECOVERY:
        return "Recovery";
    case PICKEDUP:
        return "Picked";
    }

    return "error";
}

void Serializer::serialize(radio_packet_t packet)
{
    QString name = "anirniq.";
    QString type = "";
    QString key = "";
    QString value = "";
    double number = 0;

    switch (packet.node) {
    case 1:
        name += "mission";
        break;
    case 3:
        name += "acquisition";
        break;
    case 4:
        name += "motherboard";
        break;
    default:
        // Unhandled packets
        return;
    }
    name += ".";

    if (name == "anirniq.mission.") {
        switch (packet.message_id) {
        case CAN_MISSION_ROCKET_STATUS_INDEX:
            type = "keyvalue";
            name += "status";
            key = "rocket";
            value = rocket_to_string(packet.payload.UINT);
            //                std::cout << "[rocket] " << rocket_to_string(packet.payload.UINT).toStdString() << std::endl;
            break;

        case CAN_MISSION_CHARGE_STATUS_INDEX:
            type = "keyvalue";
            name += "status";
            key = "charges";
            value = charge_to_string(packet.payload.UINT);
            //                std::cout << "[charge] " << charge_to_string(packet.payload.UINT).toStdString() << std::endl;
            break;
        }
    } else if (name == "anirniq.acquisition.") {
        switch (packet.message_id) {
        case CAN_ACQUISITION_AIR_PRESSURE_INDEX:
            type = "numeric";
            name += "air.pressure";
            number = packet.payload.FLOAT;
            break;

        case CAN_ACQUISITION_AIR_TEMPERATURE_INDEX:
            type = "numeric";
            name += "air.temperature";
            number = packet.payload.FLOAT;
            break;

        case CAN_ACQUISITION_ALTITUDE_INDEX:
            type = "numeric";
            name += "altitude";
            number = packet.payload.FLOAT;
            std::cout << "[altitude] " << number << std::endl;
            break;

        case CAN_ACQUISITION_VERTICAL_VELOCITY_INDEX:
            type = "numeric";
            name += "vvelocity";
            number = packet.payload.FLOAT;
            break;

        case CAN_ACQUISITION_GPS_LAT_INDEX:
            type = "numeric";
            name += "gps.lat";
            number = packet.payload.FLOAT;
            //                std::cout << "[gps lat] " << packet.payload.FLOAT << std::endl;
            break;

        case CAN_ACQUISITION_GPS_LON_INDEX:
            type = "numeric";
            name += "gps.lon";
            number = packet.payload.FLOAT;
            //                std::cout << "[gps lon] " << packet.payload.FLOAT << std::endl;
            break;

        default:
            break;
        }
    } else if (name == "anirniq.motherboard.") {
        switch (packet.message_id) {
        case CAN_MOTHERBOARD_3V3_AMPERAGE:
            type = "numeric";
            name += "3v3.amperage";
            number = packet.payload.FLOAT;
            break;

        case CAN_MOTHERBOARD_3V3_VOLTAGE:
            type = "numeric";
            name += "3v3.voltage";
            number = packet.payload.FLOAT;
            break;

        case CAN_MOTHERBOARD_5V_AMPERAGE:
            type = "numeric";
            name += "5v.amperage";
            number = packet.payload.FLOAT;
            break;

        case CAN_MOTHERBOARD_5V_VOLTAGE:
            type = "numeric";
            name += "5v.voltage";
            number = packet.payload.FLOAT;
            break;

        case CAN_MOTHERBOARD_VBATT_AMPERAGE:
            type = "numeric";
            name += "battery.amperage";
            number = packet.payload.FLOAT;
            break;

        case CAN_MOTHERBOARD_VBATT_VOLTAGE:
            type = "numeric";
            name += "battery.voltage";
            number = packet.payload.FLOAT;
            break;
        }
    }

    Data* data = nullptr;
    if (type == "numeric") {
        data = new NumericalData(name, number);
        std::cout << name.toStdString() << "=" << number << std::endl;
    } else if (type == "keyvalue") {
        data = new KeyValueData(name);
        ((KeyValueData*)data)->add(key, value);
        std::cout << name.toStdString() << ":" << key.toStdString() << "=" << value.toStdString() << std::endl;
    }
    if (data != nullptr) {
        Distributor::get().onData(data);
        delete data;
    }
}
