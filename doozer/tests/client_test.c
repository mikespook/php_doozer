#include <stdlib.h>
#include "../client.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("<HOST> and <PORT> needed.\n");
        return EXIT_FAILURE;
    }

    int doozer;
    char * host = argv[1];
    unsigned port = atoi(argv[2]);
    if ((doozer = doozer_connect(host, port, NULL, NULL)) == DOOZER_ERR) {
        printf("Error Number: %d\n", doozer_last_errno());
        return EXIT_FAILURE;
    }

    Doozer__Request req = DOOZER__REQUEST__INIT;
    req.tag = 0;
    req.verb = DOOZER__REQUEST__VERB__NOP;
    req.path = "/";
    
    int len = _doozer_send(doozer, &req);
    printf("Send length: %d\n", len);        

    Doozer__Response *resp;
    _doozer_recv(doozer, resp);

    doozer_close(doozer);
    printf("%s:%d\n", host, port);
    
    return EXIT_SUCCESS;
}
