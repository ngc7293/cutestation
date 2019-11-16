#include <QApplication>

#include "app.h"
#include "proto/packet.h"

int main(int argc, char *argv[]) {
  /* Setup QT types */
  qRegisterMetaType<PacketSP>("PacketSP");

  /* App */
  QApplication qapp(argc, argv);
  App app;
  app.show();
  return qapp.exec();
}