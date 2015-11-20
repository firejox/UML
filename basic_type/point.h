#ifndef __UML_BASIC_TYPE_POINT_TYPE_H__
#define __UML_BASIC_TYPE_POINT_TYPE_H__


typedef struct _point {
    double x;
    double y;
} point_t;

extern inline point_t *point_create  (double x, double y);

extern inline void     point_destory (point_t *pt);

#endif
