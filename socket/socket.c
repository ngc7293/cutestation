#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/home/ngc7293/cute.sock"


void thread(int* cl)
{
    int rc;
    char buf[128] = { 0 };
    int fd = *cl;
    while ((rc = read(fd, buf, sizeof(buf))) > 0) {
        printf("read %u bytes: %.*s\n", rc, rc, buf);
    }
    close(fd);
}

void server()
{
    int fd, rc, cl;
    struct sockaddr_un addr;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (unlink(SOCKET_PATH) == -1) {
        perror("unlink error");
        exit(-1);
    }

    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind error");
        exit(-1);
    }

    if (listen(fd, 1) == -1) {
        perror("listen error");
        exit(-1);
    }

    while (1) {
        if ((cl = accept(fd, NULL, NULL)) == -1) {
            perror("accept error");
            continue;
        }
        
        pthread_create(malloc(sizeof(pthread_t)), NULL, (void* (*)(void*)) &thread, &cl);
    }
}

void client()
{
    int fd, rc;
    struct sockaddr_un addr;
    char buf[128] = { 0 };

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect error");
        exit(-1);
    }

    while ((rc = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        if (write(fd, buf, rc) != rc) {
            if (rc == 0) {
                perror("write error");
                exit(-1);
            }
        }
    }
}

int main(int argc, const char* argv[])
{
    if (strcmp(argv[1], "server") == 0)
        server();
    else if (strcmp(argv[1], "client") == 0)
        client();
}