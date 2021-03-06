#ifndef __UML_BASIC_TYPE_ELLIPSE_TYPE_H__
#define __UML_BASIC_TYPE_ELLIPSE_TYPE_H__

#include "point.h"
#include "rectangle.h"
#include "../canvas.h"

typedef struct _ellipse {
    point_t center;
    double radius; 
    double rate; /* y/x */
} ellipse_t;

extern ellipse_t *ellipse_create     (double radius, double rate);

extern int        is_ellipse_inside  (ellipse_t *e, point_t *pt);

extern int        is_ellipse_covered (ellipse_t *e, rectangle_t *src);

extern void       ellipse_paint      (ellipse_t *e, canvas_t *ca); 

extern void       ellipse_destroy    (ellipse_t *e);

#endif
