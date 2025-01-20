#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>

int socket_connect(char *host, in_port_t port) {
    struct hostent *hp;
    struct sockaddr_in addr;
    int on = 1, sock;

    if ((hp = gethostbyname(host)) == NULL) {
        herror("gethostbyname");
        exit(1);
    }
    memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

    if (sock == -1) {
        perror("setsockopt");
        exit(1);
    }

    if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
        perror("connect");
        exit(1);
    }
    return sock;
}

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int fd;
    char buffer[BUFFER_SIZE];

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(1);
    }

    fd = socket_connect(argv[1], atoi(argv[2]));

    char request[BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]);

    write(fd, request, strlen(request));
    memset(buffer, 0, BUFFER_SIZE);

    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytesRead] = '\0';
        fprintf(stderr, "%s", buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }

    if (bytesRead < 0) {
        perror("read");
        exit(1);
    }

    close(fd);

    return 0;
}
