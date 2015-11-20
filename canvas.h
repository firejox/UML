#ifndef __CANVAS_H
#define __CANVAS_H

#include <gtk/gtk.h>
#include <cairo/cairo.h>

typedef struct _canvas {
    GtkStyleContext *gs_ctx;
    cairo_t         *cr;
} canvas_t;

#endif
