QT       += core gui widgets charts network
 
TARGET = cute 
TEMPLATE = app 
 
DEFINES += QT_DEPRECATED_WARNINGS 
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x051001 
 
SOURCES += \ 
        src/main.cc \ 
        src/ui/app.cc \
        src/data/data.cc \
        src/connector/unixconnector.cc \
        src/connector/unixconnectormanager.cc

HEADERS += \ 
        inc/ui/app.hh \
        inc/data/data.hh \
        inc/connector/unixconnector.hh \
        inc/connector/unixconnectormanager.hh
 
FORMS += \ 
        ui/app.ui 
 
INCLUDEPATH += \ 
        inc/ 
 
OBJECTS_DIR = obj 
MOC_DIR = obj

QMAKE_CXXFLAGS += -std=c++17