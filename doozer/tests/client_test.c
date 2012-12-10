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

    doozer_close(doozer);
    printf("%s:%d\n", host, port);
    return EXIT_SUCCESS;
}
