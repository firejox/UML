#ifndef __UML_MEOW_CANVAS_H__
#define __UML_MEOW_CANVAS_H__

#include <gtk/gtk.h>
#include <cairo/cairo.h>

typedef struct _canvas canvas_t;

struct _canvas {
    cairo_t         *cr;
};


#endif
