#include <math.h>
#include "../utils.h"
#include "ellipse.h"


inline ellipse_t *ellipse_create (double radius, double rate) {
    ellipse_t *tmp = xmalloc (sizeof(ellipse_t));
    tmp->center.x = tmp->center.y = 0;
    tmp->radius = radius;
    tmp->rate = rate;
    return tmp;
} 


inline int is_ellipse_inside (ellipse_t *e, point_t *pt) {
    double rx = e->radius;
    double ry = e->radius * e->rate;
    double dist = hypot((e->center.x - pt->x) / rx,
                        (e->center.y - pt->y) / ry);

    return islessequal (dist, 1.0);
}

inline int is_ellipse_covered (ellipse_t *e, rectangle_t *src) {
    double rx = e->radius;
    double ry = e->radius * e->rate;

    return (islessequal     (src->pos.x, e->center.x - rx)                  &&
            islessequal     (src->pos.y, e->center.y - ry)                  &&
            isgreaterequal  (src->pos.x + src->width, e->center.x + rx)     &&
            isgreaterequal  (src->pos.y + src->height, e->center.y + ry));
}

inline void ellipse_destory (ellipse_t *e) {
    xfree (e);
}
