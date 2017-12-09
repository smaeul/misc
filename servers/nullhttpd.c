/*
 * Copyright © 2015-2017 Samuel Holland <samuel@sholland.org>
 * SPDX-License-Identifier: 0BSD
 * vim: ft=c:noexpandtab:sts=8:sw=8:ts=8:tw=80
 */

#include <arpa/inet.h>
#include <limits.h>
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
#define RESPONSE                                                               \
	"HTTP/1.1 204 No Content\n"                                            \
	"Cache-Control: max-age=315360000\n"                                   \
	"Connection: close\n"                                                  \
	"Expires: Thu, 31 Dec 2037 23:55:55 GMT\n\n"

void
die(char *msg)
{
	perror(msg);
	exit(1);
}

void *
handle(void *fdptr)
{
	char buf[PAGESIZE];
	int fd = (int)(intptr_t)fdptr;

	/* HTTP requires waiting for the request. Throw it away. */
	recv(fd, buf, PAGESIZE, 0);
	send(fd, RESPONSE, sizeof(RESPONSE) - 1, MSG_NOSIGNAL);

	close(fd);
	return NULL;
}

int
main(void)
{
	int one = 1;
	int sock;
	pthread_t thread;
	pthread_attr_t attr;
	struct addrinfo hints
	    = { .ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM };
	struct addrinfo *res;

	if (getaddrinfo(HOST, PORT, &hints, &res) != 0)
		die("getaddrinfo");
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock < 0)
		die("socket");
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0)
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
		void *data = (void *)(intptr_t)fd;

		if (fd < 0) {
			perror("accept");
			continue;
		}
		if (pthread_create(&thread, &attr, handle, data) != 0)
			close(fd);
	}

	pthread_attr_destroy(&attr);
	close(sock);

	return 0;
}
