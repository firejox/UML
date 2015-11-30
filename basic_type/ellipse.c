#include <math.h>
#include "../utils.h"
#include "ellipse.h"


ellipse_t *ellipse_create (double radius, double rate) {
    ellipse_t *tmp = xmalloc (sizeof(ellipse_t));
    tmp->center.x = tmp->center.y = 0;
    tmp->radius = radius;
    tmp->rate = rate;
    return tmp;
} 


int is_ellipse_inside (ellipse_t *e, point_t *pt) {
    double rx = e->radius;
    double ry = e->radius * e->rate;
    double dist = hypot((e->center.x - pt->x) / rx,
                        (e->center.y - pt->y) / ry);

    return islessequal (dist, 1.0);
}

int is_ellipse_covered (ellipse_t *e, rectangle_t *src) {
    double rx = e->radius;
    double ry = e->radius * e->rate;
    double half_w = src->width / 2.0;
    double half_h = src->height / 2.0;

    return (islessequal     (src->center.x - half_w, e->center.x - rx)  &&
            islessequal     (src->center.y - half_h, e->center.y - ry)  &&
            isgreaterequal  (src->center.x + half_w, e->center.x + rx)  &&
            isgreaterequal  (src->center.y + half_h, e->center.y + ry));
}

void ellipse_paint (ellipse_t *e, canvas_t *ca) {
    cairo_translate (ca->cr, e->center.x, e->center.y);

    cairo_scale (ca->cr, 1, e->rate);

    cairo_arc (ca->cr, 0.0, 0.0, e->radius, 0, 2*M_PI);

    cairo_stroke_preserve (ca->cr);
}

void ellipse_destroy (ellipse_t *e) {
    xfree (e);
}
