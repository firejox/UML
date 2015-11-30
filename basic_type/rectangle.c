#include <math.h>
#include "../utils.h"
#include "rectangle.h"

rectangle_t *rectangle_create (double width, double height) {
    rectangle_t *tmp = xmalloc(sizeof(rectangle_t));
    tmp->center.x = tmp->center.y = 0;
    tmp->width = width;
    tmp->height = height;
}

int is_rectangle_inside (rectangle_t *rect, point_t *pt) {
    double half_w = rect->width / 2.0;
    double half_h = rect->height / 2.0;

    return (islessequal     (rect->center.x - half_w, pt->x)        &&
            isgreaterequal  (rect->center.x + half_w, pt->x)        &&
            islessequal     (rect->center.y - half_h, pt->y)        &&
            isgreaterequal  (rect->center.y + half_h, pt->y));
}

int is_rectangle_covered (rectangle_t *dest, rectangle_t *src) {
    double d_half_w = dest->width / 2.0;
    double d_half_h = dest->height / 2.0;

    double s_half_w = src->width / 2.0;
    double s_half_h = src->height / 2.0;


    return (islessequal     (src->center.x - s_half_w,
                            dest->center.x - d_half_w)          &&
            islessequal     (src->center.y - s_half_h,
                            dest->center.y - d_half_h)          &&
            isgreaterequal  (src->center.x + s_half_w,
                            dest->center.x + d_half_w)          &&
            isgreaterequal  (src->center.y + s_half_h,
                            dest->center.y + d_half_h));
}

void rectangle_paint (rectangle_t *rect, canvas_t *ca) {
    double x = rect->center.x - (rect->width / 2);
    double y = rect->center.y - (rect->height / 2); 

    cairo_rectangle (ca->cr, x, y, rect->width, rect->height);

    cairo_stroke_preserve (ca->cr);
}

void rectangle_destroy (rectangle_t *rect) {
    xfree(rect);
}
