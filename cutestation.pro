QT       += core gui widgets charts 

TARGET = cute
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x051001

SOURCES += \
        src/main.cc \
        src/ui/app.cc \
        src/ui/widgets/sensorwidget.cc \
        src/ui/widgets/accelerationwidget.cc \
        src/communication/packet.cc \
        src/communication/serial.cc \
        src/communication/serialcom.cc \
        src/communication/serialstub.cc \
        src/messages/message.cc \
        src/messages/altimetermessage.cc \
        src/messages/ejectionsettingsmessage.cc \
        src/messages/rocketstatemessage.cc \
        src/messages/parachutestatemessage.cc \
        src/messages/accelerationmessage.cc \
        src/messages/gyromessage.cc \
        src/messages/gpsmetamessage.cc \
        src/messages/gpsdatamessage.cc \
        src/workers/serialworker.cc


HEADERS += \
        inc/ui/app.hh \
        inc/ui/widgets/sensorwidget.hh \
        inc/ui/widgets/accelerationwidget.hh \
        inc/communication/packet.hh \
        inc/communication/serial.hh \
        inc/communication/serialcom.hh \
        inc/communication/serialstub.hh \
        inc/messages/message.hh \
        inc/messages/message_defs.h \
        inc/messages/altimetermessage.hh \
        inc/messages/ejectionsettingsmessage.hh \
        inc/messages/rocketstatemessage.hh \
        inc/messages/parachutestatemessage.hh \
        inc/messages/accelerationmessage.hh \
        inc/messages/gyromessage.hh \
        inc/messages/gpsmetamessage.hh \
        inc/messages/gpsdatamessage.hh \
        inc/workers/serialworker.hh

FORMS += \
        ui/app.ui

INCLUDEPATH += \
        inc/

OBJECTS_DIR = obj
MOC_DIR = obj