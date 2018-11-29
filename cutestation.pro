QT       += core gui widgets charts  
 
TARGET = cute 
TEMPLATE = app 
 
DEFINES += QT_DEPRECATED_WARNINGS 
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x051001 
 
SOURCES += \ 
        src/main.cc \ 
        src/ui/app.cc \
        src/data/data.cc \
        src/source/source.cc

HEADERS += \ 
        inc/ui/app.hh \
        inc/data/data.hh \
        inc/source/source.hh
 
FORMS += \ 
        ui/app.ui 
 
INCLUDEPATH += \ 
        inc/ 
 
OBJECTS_DIR = obj 
MOC_DIR = obj

QMAKE_CXXFLAGS += -std=c++17