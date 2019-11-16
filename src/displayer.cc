#include "displayer.h"

Displayer::Displayer() {}

Displayer::~Displayer() {}

void Displayer::receiveMessage(PacketSP msg) { displayMessage(msg); }

void Displayer::displayMessage(PacketSP msg) {
  std::chrono::milliseconds ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch());
  std::cout << msg->timestamp() << " " << ms.count() << " diff "
            << ms.count() - msg->timestamp() << std::endl;
}

void Displayer::close() { deleteLater(); }