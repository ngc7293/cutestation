#!/usr/bin/env python3

import json
import socket


def send(sock, count, value):
    content = json.dumps({
        'jsonrpc': '2.0',
        'id': count,
        'method': 'echo',
        'params': {
            'value': value
        }
    })
    content = "Content Length: {}\r\n\r\n{}".format(len(content.encode('utf-8')), content).encode('utf-8')
    sock.send(content)
    print(sock.recv(256))


def main():
    sock = socket.socket(family=socket.AF_UNIX, type=socket.SOCK_STREAM)
    sock.connect("/tmp/cute")
    count = 1

    while (True):
        value = input(">")
        if value == "quit":
            break
        send(sock, count, value)
        count += 1


if __name__ == "__main__":
    main()