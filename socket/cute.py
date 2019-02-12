#!/usr/bin/env python3

import argparse
import json
import math
import socket
import time
import psutil
import threading


def send(sock, source, name, value):
    content = json.dumps({
        'object': source,
        'name': name,
        'value': value
    })
    content = "Content-Length: {}\r\n\r\n{}".format(
        len(content.encode('utf-8')), content).encode('utf-8')
    sock.send(content)


def sin(sock):
    n = 0
    while True:
        value = 200 * math.sin(n / 60)
        send(sock, "python", "sin", value)
        time.sleep(0.005)
        n += 1

def cpu(sock):
    while True:
        send(sock, "system", "cpu.percent", psutil.cpu_percent(interval=None))
        send(sock, "system", "memory.size", psutil.virtual_memory().used / 1000000)
        time.sleep(0.1)

def mem(sock):
    for proc in psutil.process_iter():
        if proc.name() in ["cute", "./cute"]:
            process = proc
            break

    while True:
        send(sock, "cute", "memory.raw", process.memory_info().rss / 1000000)
        send(sock, "cute", "memory.percent", process.memory_percent())
        time.sleep(0.1)


def main(args):
    sock = socket.socket(family=socket.AF_UNIX, type=socket.SOCK_STREAM)
    sock.connect("/tmp/cute")
    {
        'cpu': cpu,
        'mem': mem,
        'sin': sin
    }[args.source](sock)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', choices=['cpu','mem','sin'], required=True)
    main(parser.parse_args())
