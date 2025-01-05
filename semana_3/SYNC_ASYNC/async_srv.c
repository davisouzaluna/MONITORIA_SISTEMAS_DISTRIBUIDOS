#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define PORT 8080
#define MAX 80
#define MAX_EVENTS 10

int main() {
    int sockfd, connfd, epfd, nfds;
    struct sockaddr_in servaddr, cli;
    struct epoll_event ev, events[MAX_EVENTS];
    char buff[MAX];
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);

    epfd = epoll_create1(0);
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

    while (1) {
        nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == sockfd) {
                len = sizeof(cli);
                connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
                ev.events = EPOLLIN;
                ev.data.fd = connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            } else {
                bzero(buff, MAX);
                read(events[i].data.fd, buff, sizeof(buff));
                write(events[i].data.fd, buff, sizeof(buff));
                if (strncmp(buff, "exit", 4) == 0)
                    close(events[i].data.fd);
            }
        }
    }
    close(sockfd);
    return 0;
}
