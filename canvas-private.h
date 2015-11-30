#ifndef __UML_MEOW_CANVAS_PRIVATE_H__
#define __UML_MEOW_CANVAS_PRIVATE_H__

#include "canvas.h"
#include "canvas-protected.h"
#include "general_object_pool.h"

typedef struct _canvas_private canvas_private;

struct _canvas_private {
    canvas_t                ca;
    cairo_surface_t         *surface;
    general_object_pool_t   *pool; 
    rectangle_t             range;
};

#endif
