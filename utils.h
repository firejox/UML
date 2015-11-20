#ifndef __UML_MEOW_UTILS_H__
#define __UML_MEOW_UTILS_H__

#include <stddef.h>

extern void *xmalloc  (size_t size);
extern void *xcalloc  (size_t nmemb, size_t size);
extern void *xrealloc (void *ptr, size_t size);

extern void  xfree    (void *ptr);


#endif
