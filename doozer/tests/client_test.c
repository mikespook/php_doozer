#include <stdlib.h>
#include "../client.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("<HOST> and <PORT> needed.\n");
        return EXIT_FAILURE;
    }
    printf("Connecting...\n");
    int doozer;
    char * host = argv[1];
    unsigned port = atoi(argv[2]);
    if ((doozer = doozer_connect(host, port, NULL, NULL)) == DOOZER_ERR) {
        printf("Error Number: %d\n", doozer_last_errno());
        return EXIT_FAILURE;
    }
    int64_t rev = 0;
    
    {
        printf("Revision\n");
        int err = doozer_current_revision(doozer, &rev);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d\n", doozer_last_errno()); 
            return EXIT_FAILURE;
        }
    }

    {
        printf("Set\n");
        char * str = "foobar";
        int err = doozer_set(doozer, "/test", str, strlen(str), &rev);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d:%lld\n", err, rev);
    }

    {
        printf("Get\n");
        size_t len;
        uint8_t *data;
        int err = doozer_get(doozer, "/test", rev, &data, &len);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d:%d:%s\n", err, len, data);
    }
    
    {
        printf("Delete\n");
        size_t len;
        int err = doozer_delete(doozer, "/test", rev);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d\n", err);
    }

    doozer_close(doozer);
    return EXIT_SUCCESS;
}
