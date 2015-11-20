#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

#define XMEM_CHECK(mem)                         \
    do {                                        \
        if (mem == NULL) {                      \
            perror ("There is no free memory"); \
            assert(mem != NULL);                \
        }                                       \
    } while (0) 

void *xmalloc (size_t size) {
    void *mem = malloc (size);
    XMEM_CHECK(mem);
    return mem; 
}

void *xcalloc (size_t nmemb, size_t size) {
    void *mem = calloc (nmemb, size);
    XMEM_CHECK(mem);
    return mem;
}

void *xrealloc (void *ptr, size_t size) {
    void *mem = xrealloc (ptr, size);
    XMEM_CHECK(mem);
    return mem;
}

void xfree (void *ptr) {
    free (ptr);
}
