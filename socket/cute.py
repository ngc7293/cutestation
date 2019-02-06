#!/usr/bin/env python3

import json
import math
import socket
import time

def send(sock, count, value):
    content = json.dumps({
        'object': 'Python',
        'name': 'altitude',
        'value': value
    })
    content = "Content-Length: {}\r\n\r\n{}".format(len(content.encode('utf-8')), content).encode('utf-8')
    sock.send(content)


def main():
    sock = socket.socket(family=socket.AF_UNIX, type=socket.SOCK_STREAM)
    sock.connect("/tmp/cute")
    count = 1

    while (True): 
        try:
            value = 200 * math.sin(count / 60)
        except EOFError:
            print("exit")
            value = "exit"
        if value == "exit":
            sock.close()
            return

        send(sock, count, value)
        count += 1
        time.sleep(0.005)


if __name__ == "__main__":
    main()