#include "../utils.h"
#include "point.h"

inline point_t *point_create (double x, double y) {
    point_t *tmp = xmalloc(sizeof(point_t));
    tmp->x = x;
    tmp->y = y;
    return tmp;
}
inline void point_destory (point_t *pt) {
    xfree (pt);
}
