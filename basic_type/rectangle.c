#include <math.h>
#include "../utils.h"
#include "rectangle.h"

inline rectangle_t *rectangle_create (double width, double height) {
    rectangle_t *tmp = xmalloc(sizeof(rectangle_t));
    tmp->pos.x = tmp->pos.y = 0;
    tmp->width = width;
    tmp->height = height;
}

inline int is_rectangle_inside (rectangle_t *rect, point_t *pt) {
    return (islessequal     (rect->pos.x, pt->x)                 &&
            isgreaterequal  (rect->pos.x + rect->width, pt->x)   &&
            islessequal     (rect->pos.y, pt->y)                 &&
            isgreaterequal  (rect->pos.y + rect->height, pt->y));
}

inline int is_ellipse_covered (rectangle_t *target, rectangle_t *src) {
    return (islessequal     (src->pos.x,
                             target->pos.x)                     &&
            islessequal     (src->pos.y,
                             target->pos.y)                     &&
            isgreaterequal  (src->pos.x + src->width,
                             target->pos.x + target->width)     &&
            isgreaterequal  (src->pos.y + src->height,
                             target->pos.y + target->height));
}

inline void rectangle_destory (rectangle_t *rect) {
    xfree(rect);
}
