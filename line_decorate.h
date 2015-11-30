#ifndef __UML_LINE_DECORATE_H__
#define __UML_LINE_DECORATE_H__

#include "object.h"

typedef struct _line_decorate line_decorate_t;
typedef struct _line_decorate_private line_decorate_private;

struct _line_decorate {
    object_t parent;
    line_decorate_private *priv;
};


extern line_decorate_t *line_decorate_create (image_t *im);

extern int line_decorate_get_width  (line_decorate_t *dec);
extern int line_decorate_get_height (line_decorate_t *dec);

extern void line_decorate_set_angle (line_decorate_t *dec, double angle);

#endif
