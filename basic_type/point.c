#include "../utils.h"
#include "point.h"


point_t *point_create (double x, double y) {
    point_t *tmp = xmalloc(sizeof(point_t));
    tmp->x = x;
    tmp->y = y;
    return tmp;
}

int is_same_point (const point_t *dest, const point_t *src) { 
    return (double_equal(dest->x, src->x) && double_equal(dest->y, src->y));
}

void point_destroy (point_t *pt) {
    xfree (pt);
}
