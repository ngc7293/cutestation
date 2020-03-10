#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''Testing script for CuteStation'''

from argparse import ArgumentParser
from math import sin
from socket import socket, AF_UNIX, SOCK_STREAM
from time import sleep, time

from proto.packet_pb2 import Packet, Measurement, Handshake


def create_measurement(source, value):
    '''Returns a proto Measurement with given source, value'''
    measurement = Measurement()
    measurement.source = source
    measurement.timestamp = int(round(time() * 1000))
    measurement.float = value
    return measurement


def main(args):
    '''Main'''
    sock = socket(family=AF_UNIX, type=SOCK_STREAM)
    sock.connect("/tmp/cute")

    packet = Packet()
    packet.handshake.name = "python_testing"
    packet.handshake.commands.append("anirniq.remote_control.engine.sequence.start")
    sock.send(packet.SerializeToString())
    sleep(0.001)

    n = 0
    while True:
        packet = Packet()
        packet.data.measurements.append(
            create_measurement(args.source, 2 * sin(n / 1.42857))
        )
        sock.send(packet.SerializeToString())
        n += 0.1
        sleep(0.001)


if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('-s', '--source', required=True)
    main(parser.parse_args())
