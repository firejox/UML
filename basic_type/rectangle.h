#ifndef __UML_BASIC_TYPE_RECTANGLE_TYPE_H__
#define __UML_BASIC_TYPE_RECTANGLE_TYPE_H__


#include "point.h"

typedef struct _rectangle {
    point_t pos;
    double width;
    double height;
} rectangle_t;

extern inline rectangle_t *rectangle_create
                            (double width, double height);

extern inline int          is_rectangle_inside 
                            (rectangle_t *rect, point_t *pt);

extern inline int          is_rectangle_covered
                            (rectangle_t *target, rectangle_t *src);

extern inline void         rectangle_destory
                            (rectangle_t *rect);

#endif
