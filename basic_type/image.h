#ifndef __UML_MEOW_IMAGE_H__
#define __UML_MEOW_IMAGE_H__

#include "../canvas.h"

typedef struct _image image_t;

struct _image {
    cairo_surface_t *src;
};

extern image_t *image_create_from_file (const char *fn,
                                                 int width, int height);

extern image_t *image_create_from_resource (const char *res,
                                                 int width, int height);

extern image_t *image_ref   (image_t *im);
extern void     image_unref (image_t *im);

extern int      image_get_width  (image_t *im);
extern int      image_get_height (image_t *im);

extern void     image_paint (image_t *im, canvas_t *ca);

#endif
