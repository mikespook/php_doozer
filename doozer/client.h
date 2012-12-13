#ifndef _CLIENT_H
#define _CLIENT_H

#include "client.c"

extern int doozer_connect(const char *, unsigned, TIMEOUT, TIMEOUT);
extern int doozer_last_errno();
extern void doozer_close(int);
extern int doozer_current_revision(int, int64_t *);
extern int doozer_set(int, char *, uint8_t *, size_t, int64_t *);
extern int doozer_get(int, char *, int64_t, uint8_t **, size_t *);
extern int doozer_delete(int, char *, int64_t);
extern int doozer_dir(int, char *, int64_t, int32_t, char **);
extern int doozer_stat(int, char *, int64_t *, int32_t *);
extern int doozer_access(int, char *);
extern int doozer_wait(int, char *, int64_t *, 
        char **, char **, size_t *, char *);
/*
extern void doozer_walk();
extern void doozer_hosts();
extern void doozer_wait();
*/
#endif /* _CLIENT_H */
