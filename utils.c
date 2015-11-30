#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "utils.h"

#define EPS 1e-7

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

int double_equal(double dest, double src) {
    return islessequal(fabs(dest-src), EPS);
}


void xerror_log (const char *fmt, ...) {
    va_list ap;

    va_start (ap, fmt);

    vfprintf (stderr, fmt, ap);

    va_end (ap);

}
