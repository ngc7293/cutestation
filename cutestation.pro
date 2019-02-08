QT       += core gui widgets charts network

TARGET = cute
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x051001

SOURCES += \
        src/main.cc \
        src/ui/app.cc \
        src/widgets/widget.cc \
        src/widgets/chartwidget.cc \
        src/widgets/config/widget_config.cc \
        src/widgets/config/chartwidget_config.cc \
        src/messages/message.cc \
        src/distributor.cc \
        src/connection/connection.cc \
        src/connection/connectionmanager.cc \
        src/connection/unixconnection.cc \
        src/connection/unixconnectionmanager.cc

HEADERS += \
        inc/ui/app.hh \
        inc/widgets/widget.hh \
        inc/widgets/chartwidget.hh \
        inc/widgets/config/widget_config.hh \
        inc/widgets/config/chartwidget_config.hh \
        inc/messages/message.hh \
        inc/distributor.hh \
        inc/connection/connection.hh \
        inc/connection/connectionmanager.hh \
        inc/connection/unixconnection.hh \
        inc/connection/unixconnectionmanager.hh

FORMS += \
        ui/app.ui

INCLUDEPATH += \
        inc/

OBJECTS_DIR = obj
MOC_DIR = obj

QMAKE_CXXFLAGS += -std=c++17