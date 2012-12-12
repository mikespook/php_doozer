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
/*
extern void doozer_dir();
extern void doozer_stat();
extern void doozer_access();
extern void doozer_walk();
extern void doozer_hosts();
extern void doozer_wait();
*/
#endif /* _CLIENT_H */
