#ifndef _CLIENT_H
#define _CLIENT_H

#include "client.c"

/**
 * Connect to a doozer server
 * @params: host, port, receive timeout, send timeout
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_connect(const char *, unsigned, TIMEOUT, TIMEOUT);

/**
 * Get last error number
 * @params: void
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_last_errno();

/**
 * Close doozer socket file handler
 * @params: socket fd
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern void doozer_close(int);

/**
 * Get current revision
 * @params: socket fd, revision{in|out}
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_rev(int, int64_t *);

/**
 * Set a value for a path
 * @params: socket fd, path, value, value length, revision{in|out}
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_set(int, char *, uint8_t *, size_t, int64_t *);

/**
 * Get a value from a path
 * @params: socket fd, revision, value{out}, value length{out}
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_get(int, char *, int64_t, uint8_t **, size_t *);

/** 
 * Delete a path
 * @params: socket fd, path, revision
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_delete(int, char *, int64_t);

/**
 * Get a subpath
 * @params: socket fd, path, revision, offset, subpath{out}
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_dir(int, char *, int64_t, int32_t, char **);

/**
 * Get a stat for a path
 * @params: socket fd, path, revision{in|out}, length{out}
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_stat(int, char *, int64_t *, int32_t *);

/**
 * Access doozer server
 * @params: socket fd, token
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_access(int, char *);

/**
 * Wait for a path to change
 * @params: socket fd, path, revision{in|out}, response path{out},
 *     value{out}, value length{out}, flag{out}
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_wait(int, char *, int64_t *, 
        char **, uint8_t **, size_t *, int32_t *);

/**
 * An empty request for an empty response
 * @params: socket fd
 * @return: DOOZER_ERR | DOOZER_SUCCESS
 */
extern int doozer_nop(int);

#endif /* _CLIENT_H */
