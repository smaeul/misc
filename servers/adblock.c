#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define HOST "::"
#define PORT "65535"
#define RESPONSE "HTTP/1.1 204 No Content\nCache-Control: max-age=315360000\nConnection: close\nExpires: Thu, 31 Dec 2037 23:55:55 GMT\n\n"

void die(char *msg)
{
    perror(msg);
    exit(1);
}

void *handle(void *fdptr)
{
    int fd = (int)fdptr;

    send(fd, RESPONSE, sizeof(RESPONSE) - 1, MSG_NOSIGNAL);

    close(fd);
    return NULL;
}

int main(void)
{
    int reuse = 1, sock;
    pthread_t thread;
    pthread_attr_t attr;
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM
    }, *res;

    if (getaddrinfo(HOST, PORT, &hints, &res) != 0)
        die("getaddrinfo");
    if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
        die("socket");
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
        die("setsockopt");
    if (bind(sock, res->ai_addr, res->ai_addrlen) < 0)
        die("bind");
    if (listen(sock, SOMAXCONN) < 0)
        die("listen");
    freeaddrinfo(res);
 
    if (pthread_attr_init(&attr) != 0)
        die("pthread_attr_init");
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        die("pthread_attr_setdetachstate");

    for (;;) {
        int fd = accept(sock, 0, 0);

        if (fd < 0) {
            perror("accept");
            continue;
        }
        if (pthread_create(&thread, &attr, handle, (void *)fd) != 0)
            close(fd);
    }

    pthread_attr_destroy(&attr);
    close(sock);

    return 0;
}
