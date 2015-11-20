#ifndef __UML_MEOW_IMAGE_H__
#define __UML_MEOW_IMAGE_H__

#include <cairo/cairo.h>

typedef struct _image image_t;

struct _image {
    cairo_surface_t *src;
    int ref_count;
};

extern image_t *image_create_from_file (const char *str, int width, int height);
extern image_t *image_ref   (image_t *im);
extern void     image_unref (image_t *im);


#endif
