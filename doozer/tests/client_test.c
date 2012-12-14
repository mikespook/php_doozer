#include <stdlib.h>
#include "../client.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("<HOST> and <PORT> needed.\n");
        return EXIT_FAILURE;
    }
    // {{{ init
    printf("Connecting...\n");
    int doozer;
    char * host = argv[1];
    unsigned port = atoi(argv[2]);
    if ((doozer = doozer_connect(host, port, NULL, NULL)) == DOOZER_ERR) {
        printf("Error Number: %d\n", doozer_last_errno());
        return EXIT_FAILURE;
    }
    // }}}

    int64_t rev = 0;
    
    { // {{{ rev
        printf("Revision\n");
        int err = doozer_rev(doozer, &rev);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d\n", doozer_last_errno()); 
            return EXIT_FAILURE;
        }
    } // }}}

    { // {{{ set
        printf("Set\n");
        char * str = "foobar";
        int err = doozer_set(doozer, "/test", str, strlen(str), &rev);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d:%lld\n", err, rev);
    } // }}}

    { // {{{ get
        printf("Get\n");
        size_t len;
        uint8_t *data;
        int err = doozer_get(doozer, "/test", rev, &data, &len);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d:%d:%s\n", err, len, data);
    } // }}}
    
    { // {{{ delete
        printf("Delete\n");
        size_t len;
        int err = doozer_delete(doozer, "/test", rev);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d\n", err);
    } // }}}

    { // {{{ dir
        printf("Dir\n");
        char *path;
        int err = doozer_dir(doozer, "/", rev, 0, &path);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d:%s\n", err, path);    
    } // }}}

    { // {{{ stat 
        printf("Stat\n");
        int32_t len;
        int err = doozer_stat(doozer, "/ctl/cal/0", &rev, &len);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d:%lld:%d\n", err, rev, len);    
    } // }}}
    
    { // {{{ access
        printf("Access\n");
        int err = doozer_access(doozer, "/");
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d\n", err);    
 
    } // }}}

    { // {{{ nop
        printf("Nop\n");
        int err = doozer_nop(doozer);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d\n", err);       
    } // }}}

    { // {{{ wait
        printf("Wait\n");
        int err = doozer_rev(doozer, &rev);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d\n", doozer_last_errno()); 
            return EXIT_FAILURE;
        }       
        size_t bodylen;
        int32_t flags;
        char *path;
        uint8_t *body;
        err = doozer_wait(doozer, "/test", &rev, &path, &body, &bodylen, &flags);
        if (err == DOOZER_ERR) {
            printf("Error Number: %d; Revision: %lld\n", doozer_last_errno(), rev); 
            return EXIT_FAILURE;
        }
        printf("%d:%s:%s:%d:%d:%lld\n", err, path, body, bodylen, flags, rev);       
    } // }}}

    doozer_close(doozer);
    return EXIT_SUCCESS;
}
