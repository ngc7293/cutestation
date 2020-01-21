#!/usr/bin/env python3

from math import sin
from socket import socket, AF_UNIX, SOCK_STREAM
from time import sleep, time

from proto.packet_pb2 import Packet

def main(args):
    sock = socket(family=AF_UNIX, type=SOCK_STREAM)
    sock.connect("/tmp/cute")

    n = 0
    while True:
        msg = Packet()
        msg.source = "anirniq.mission.charge"
        msg.timestamp = int(round(time() * 1000))
        msg.value = sin(n / 1.42857)
        sock.send(msg.SerializeToString())
        n += 1
        sleep(0.1)

if __name__ == "__main__":
    main(None)
