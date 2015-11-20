#include <stdio.h>
#include <string.h>
#include "../utils.h"
#include "xstring.h"

#define XSTR_MAX_SIZE (SIZE_MAX >> 1)
#define XSTR_MIN_SIZE 32

struct _xstring {
    char *str;
    size_t len;
    size_t lim;
    int ref_count;
};

inline xstring_t *xstring_create(void) {
    xstring_t *str = xmalloc(sizeof(xstring_t));
    str->str = xmalloc(MIN_SIZE);
    str->str[0] = '\0';
    str->len = 0;
    str->lim = MIN_SIZE;
    str->ref_count = 0;

    return str;
}


inline xstring_t *xstring_ref (xstring_t *str) {
    str->ref_count++;
    return str;
}


inline void xstring_set_string (xstring_t *str, const char *s) {
    size_t len = strlen (s);
    
    if (str->lim <= len) {
        while (str->lim <= len && len <= MAX_SIZE) 
            str->lim <<= 1;
        str->str = xrealloc (str->str, str->lim);
    }

    str->len = snprintf (str->str, str->lim, "%s", s); 
}

inline const char *xstring_get_string (xstring_t *str) {
    return str->str;
}

inline size_t xstring_get_len (xstring_t *str) {
    return str->len;
}

inline void xstring_unref (xstring_t *str) {
    if (!str->ref_count) {
        xfree (str->str);
        xfree (str);
    }

    str->ref_count --;
}
