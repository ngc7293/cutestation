#!/usr/bin/env python3

import argparse
import json
import math
import socket
import time
import psutil
import threading


def send_numeric(sock, name, value):
    send(sock, json.dumps({
        'type': 'numeric',
        'name': name,
        'value': value
    }))

def send_keyvalue(sock, name, data):
    data['name'] = name
    data['type'] = 'keyvalue'
    send(sock, json.dumps(data))

def send(sock, content):
    content = "Content-Length: {}\r\n\r\n{}".format(
        len(content.encode('utf-8')), content).encode('utf-8')
    sock.send(content)


def sin(sock):
    n = 0
    while True:
        value = 200 * math.sin(n / 60)
        send_numeric(sock, "sin", value)
        time.sleep(0.005)
        n += 1

def cpu(sock):
    while True:
        send_numeric(sock, "cpu.percent", psutil.cpu_percent(interval=None))
        send_numeric(sock, "memory.size", psutil.virtual_memory().used / 1000000)
        time.sleep(0.1)

def mem(sock):
    for proc in psutil.process_iter():
        if proc.name() in ["cute", "./cute"]:
            process = proc
            break

    while True:
        send_numeric(sock, "memory.raw", process.memory_info().rss / 1000000)
        send_numeric(sock, "memory.percent", process.memory_percent())
        time.sleep(0.1)

def color(sock):
    colors = ['black', 'red', 'purple', 2]
    i = 0
    while True:
        send_keyvalue(sock, "favorite.color", {"david": colors[i]})
        time.sleep(0.5)
        i  = (i + 1) % len(colors)

def main(args):
    sock = socket.socket(family=socket.AF_UNIX, type=socket.SOCK_STREAM)
    sock.connect("/tmp/cute")
    {
        'cpu': cpu,
        'mem': mem,
        'sin': sin,
        'color': color
    }[args.source](sock)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', choices=['cpu','mem','sin', 'color'], required=True)
    main(parser.parse_args())
