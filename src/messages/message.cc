#include "messages/message.hh"

#include "messages/accelerationmessage.hh"
#include "messages/altimetermessage.hh"
#include "messages/ejectionsettingsmessage.hh"
#include "messages/gpsdatamessage.hh"
#include "messages/gpsmetamessage.hh"
#include "messages/gyromessage.hh"
#include "messages/message_defs.h"
#include "messages/parachutestatemessage.hh"
#include "messages/rocketstatemessage.hh"

Message* Message::fromPacket(Packet& packet)
{
    switch (packet.id()) {
    case MSG_ID_EJECTION_SETTINGS:
        return new EjectionSettingsMessage(packet);
    case MSG_ID_ALTIMETER_DATA:
        return new AltimeterMessage(packet);
    case MSG_ID_ACCELERATION:
        return new AccelerationMessage(packet);
    case MSG_ID_GYRO:
        return new GyroMessage(packet);
    case MSG_ID_ROCKET_STATE:
        return new RocketStateMessage(packet);
    case MSG_ID_PARACHUTE_STATE:
        return new ParachuteStateMessage(packet);
    case MSG_ID_GPS_METADATA:
        return new GPSMetaMessage(packet);
    case MSG_ID_GPS_DATA:
        return new GPSDataMessage(packet);
    }
    return nullptr;
}

Message::Message(Packet packet)
    : data_(packet)
{
}

Message::~Message()
{
}

std::ostream& operator<<(std::ostream& stream, Message& message)
{
    return stream << message.toString();
}

std::ostream& operator<<(std::ostream& stream, Message* message)
{

    return stream << *message;
}