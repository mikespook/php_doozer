
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#include "msg.pb-c.h"

#define DOOZER_ERR -1
#define BUF_SIZE 1024
#define TIMEVAL struct timeval
#define TIMEOUT const TIMEVAL *

void _debug_print(uint8_t *buf, ssize_t size) {
    int i;
    for (i = 0; i < size; i ++) {
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

int doozer_connect(const char *hostname, unsigned port,
        TIMEOUT rcvtimeo, TIMEOUT sndtimeo) {
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
    addr.sin_family = AF_INET;
    memcpy((char *)&addr.sin_addr.s_addr, 
            (char *)host->h_addr, host->h_length);
    addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&addr, 
                sizeof(struct sockaddr_in)) == DOOZER_ERR) {
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

int doozer_current_revision(int sockfd, int64_t *rev) {
    Doozer__Request req = DOOZER__REQUEST__INIT;
    req.has_verb = 1; req.verb = DOOZER__REQUEST__VERB__REV;
    Doozer__Response *resp;
    int err;
    if ((err = _doozer_invoke(sockfd, &req, &resp)) != 0) {
        errno = err;
        return DOOZER_ERR;
    }
    memcpy(rev, &resp->rev, 8);
    return 0;
}

int doozer_set(int sockfd, char *path, uint8_t *vdata, size_t vlen, int64_t *rev) {
    Doozer__Request req = DOOZER__REQUEST__INIT;
    req.has_verb = 1; req.verb = DOOZER__REQUEST__VERB__SET;
    req.path = path;
    ProtobufCBinaryData value;
    value.len = vlen;
    value.data = vdata;
    req.has_value = 1; req.value = value;
    req.has_rev = ((*rev != 0) || (rev != NULL)); req.rev = *rev;
    Doozer__Response *resp;
    int err;
    if ((err = _doozer_invoke(sockfd, &req, &resp)) != 0) {
        errno = err;
        return DOOZER_ERR;
    }
    memcpy(rev, &resp->rev, 8);
    return 0;   
}

int doozer_get(int sockfd, char *path, int64_t rev, uint8_t **vdata, size_t *vlen) {
    Doozer__Request req = DOOZER__REQUEST__INIT;
    req.has_verb = 1; req.verb = DOOZER__REQUEST__VERB__GET;
    req.path = path;
    req.has_rev = (rev != 0); req.rev = rev;
    Doozer__Response *resp;
    int err;
    if ((err = _doozer_invoke(sockfd, &req, &resp)) != 0) {
        errno = err;
        return DOOZER_ERR;
    }

    if (resp->has_value) {
        *vlen = resp->value.len;
        *vdata = resp->value.data;
    } else {
        return DOOZER_ERR;
    }
    return 0;
}

int doozer_delete(int sockfd, char *path, int64_t rev) {
    Doozer__Request req = DOOZER__REQUEST__INIT;
    req.has_verb = 1; req.verb = DOOZER__REQUEST__VERB__DEL;
    req.path = path;
    req.has_rev = (rev != 0); req.rev = rev;
    Doozer__Response *resp;
    int err;
    if ((err = _doozer_invoke(sockfd, &req, &resp)) != 0) {
        errno = err;
        return DOOZER_ERR;
    }
    return 0;
}

int _doozer_invoke(int sockfd, Doozer__Request *req, Doozer__Response **resp) {
    req->has_tag = 1; req->tag = 0;
    if (_doozer_send(sockfd, req) == DOOZER_ERR) {
        return DOOZER_ERR;
    }
    if (_doozer_recv(sockfd, resp) ==  DOOZER_ERR) {
        return DOOZER_ERR;
    }
    if ((*resp)->has_err_code) {
        return (*resp)->err_code;
    }
    return 0;
}

int _doozer_send(int sockfd, const Doozer__Request *req) {
    int sended, l, nl;
    l = doozer__request__get_packed_size(req);
    nl = ntohl(l);
    if ((sended = send(sockfd, &nl, 4, 0)) == DOOZER_ERR) {
        return DOOZER_ERR;
    }
    uint8_t buf[l];
    doozer__request__pack(req, buf); 
    if ((sended = send(sockfd, buf, l, 0)) == DOOZER_ERR) {
        return DOOZER_ERR;
    }
    return sended;
}

int _doozer_recv(int sockfd, Doozer__Response **resp) {
    int l, nl;
    l = recv(sockfd, &nl, 4, 0);
    if (l != 4) {
        return DOOZER_ERR;
    }
    nl = htonl(nl);
    void *buf = malloc(nl);
    l = recv(sockfd, buf, nl, 0);
    if (l != nl) {
        return DOOZER_ERR;
    }
    *resp = doozer__response__unpack(NULL, l, buf);
    free(buf);
    return l;
}
