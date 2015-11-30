#ifndef __UML_BASIC_TYPE_POINT_TYPE_H__
#define __UML_BASIC_TYPE_POINT_TYPE_H__


typedef struct _point {
    double x;
    double y;
} point_t;

extern point_t *point_create  (double x, double y);

extern int is_same_point (point_t *dest, point_t *src);

extern void     point_destroy (point_t *pt);

#endif
