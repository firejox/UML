#ifndef __UML_BASIC_TYPE_XSTRING_TYPE_H__
#define __UML_BASIC_TYPE_XSTRING_TYPE_H__

typedef struct _xstring xstring_t;

extern inline xstring_t *xstring_create (void);

extern inline xstring_t *xstring_ref (xstring_t *str);

extern inline void xstring_set_string (xstring_t *str, const char *s);

extern inline const char *xstring_get_string (xstring_t *str);

extern inline size_t xstring_get_len (xstring_t *str);

extern inline void xstring_unref (xstring_t *str);

#endif
