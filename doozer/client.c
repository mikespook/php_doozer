
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <errno.h>

#include "msg.pb-c.h"

#define DOOZER_ERR -1
#define BUF_SIZE 1024
#define TIMEVAL struct timeval
#define TIMEOUT const TIMEVAL *


int doozer_connect(const char *hostname, unsigned port, TIMEOUT rcvtimeo, TIMEOUT sndtimeo) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return DOOZER_ERR;
    }
    // receiving timeout
    if (rcvtimeo != NULL && setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
                (char *)rcvtimeo, sizeof(TIMEVAL)) == DOOZER_ERR) {
        return DOOZER_ERR;
    }
    // sending timeout
    if (sndtimeo != NULL && setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO,
                (char *)sndtimeo, sizeof(TIMEVAL)) == DOOZER_ERR) {
        return DOOZER_ERR;
    }
    // connect to...
    struct sockaddr_in addr;
    struct hostent *host;
    if ((host = gethostbyname(hostname)) == NULL) {
        return DOOZER_ERR;
    }
    bzero((char *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    bcopy((char *)host->h_addr, (char *)&addr.sin_addr.s_addr, host->h_length);
    addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == DOOZER_ERR) {
        return DOOZER_ERR;
    }
    return sockfd;
}

int doozer_last_errno() {
    return errno;
}

void doozer_close(int sockfd) {
    close(sockfd);
}

int _doozer_send(int sockfd, Doozer__Request *req) {
    int sended, len;
    void *buf;
    len = doozer__request__get_packed_size(req);
    buf = malloc(len);
    doozer__request__pack(req, buf);
    if ((sended = send(sockfd, buf, len, 0)) == DOOZER_ERR) {
        return DOOZER_ERR;
    }
    return sended;
}

int _doozer_recv(int sockfd, Doozer__Response *resp) {
    int len;
    void *buf;
    // TODO: an epoll here
    len = recv(sockfd, buf, BUF_SIZE, 0)
    resp = doozer__response__unpack(NULL, len, buf);
    return len;
}