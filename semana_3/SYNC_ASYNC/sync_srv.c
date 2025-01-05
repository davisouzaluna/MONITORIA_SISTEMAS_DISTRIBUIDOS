#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 80

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[MAX];
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);

    len = sizeof(cli);
    connfd = accept(sockfd, (struct sockaddr*)&cli, &len);

    while (1) {
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        write(connfd, buff, sizeof(buff));
        if (strncmp(buff, "exit", 4) == 0)
            break;
    }
    close(sockfd);
    return 0;
}
