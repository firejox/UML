#ifndef __UML_MEOW_UTILS_H__
#define __UML_MEOW_UTILS_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define STR(x)  SPLICE_STR(x)
#define SPLICE_STR(x) #x



extern void *xmalloc  (size_t size);
extern void *xcalloc  (size_t nmemb, size_t size);
extern void *xrealloc (void *ptr, size_t size);

extern void  xfree    (void *ptr);

extern int double_equal (double dest, double src);

extern void xerror_log (const char *fmt, ...);

#define NDEBUG
#ifdef NDEBUG
#define xfunc_error_log(...) ((void) (0))
#else

#define xfunc_error_log(...) \
    xerror_log ("File : " __FILE__ " "\
               "Line : " STR(__LINE__) " "\
               __VA_ARGS__)

#endif


#endif
