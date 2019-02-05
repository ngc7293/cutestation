QT += core gui widgets charts 3dcore 3drender 3dinput 3dextras

TARGET = cute
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x051001

SOURCES += \
    src/main.cc \
    src/ui/app.cc \
    src/ui/widgets/widget.cc \
    src/ui/widgets/chartwidget.cc \
    src/messages/message.cc \
    src/workers/randomworker.cc

HEADERS += \
    inc/ui/app.hh \
    inc/ui/widgets/widget.hh \
    inc/ui/widgets/chartwidget.hh \
    inc/messages/message.hh \
    inc/workers/randomworker.hh  

FORMS += ui/app.ui

INCLUDEPATH += inc/

OBJECTS_DIR = obj/
MOC_DIR = obj/