#include <QApplication>

#include "app.h"
#include "proto/packet.h"

int main(int argc, char* argv[])
{
    /* Setup QT types */
    qRegisterMetaType<cute::proto::DataSP>("cute.proto.DataSP");
    qRegisterMetaType<cute::proto::HandshakeSP>("cute.proto.HandshakeSP");

    /* App */
    QApplication qapp(argc, argv);
    App app;
    app.show();
    return qapp.exec();
}