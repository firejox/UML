#ifndef __UML_BASIC_TYPE_RECTANGLE_TYPE_H__
#define __UML_BASIC_TYPE_RECTANGLE_TYPE_H__


#include "point.h"
#include "../canvas.h"

typedef struct _rectangle {
    point_t center;
    double width;
    double height;
} rectangle_t;

extern rectangle_t *rectangle_create
                            (double width, double height);

extern int          is_rectangle_inside 
                            (rectangle_t *rect, point_t *pt);

extern int          is_rectangle_covered
                            (rectangle_t *dest, rectangle_t *src);

extern void         rectangle_paint
                            (rectangle_t *rect, canvas_t *ca);

extern void         rectangle_destroy
                            (rectangle_t *rect);

#endif
