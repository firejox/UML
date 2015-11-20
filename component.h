#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "basic_types.h"
#include "canvas.h"

typedef enum {
    LINE_TYPE,
    OBJECT_TYPE,
    REGION_TYPE
} component_type;

typedef struct _component         component_t;
typedef struct _component_class   component_class;
typedef struct _component_private component_private;

struct _component {
    component_private *priv;
} ;



struct _component_class {
    void (*paint)      (component_t *co, canvas_t *ca);
    int  (*is_inside)  (component_t *co, point_t  *pt);
    int  (*is_covered) (component_t *co, rectangle_t *re);
    void (*selected)   (component_t *co);
    void (*unselected) (component_t *co);
    void (*destory)    (component_t *co);
};


extern void           component_paint        (component_t *co, canvas_t *ca);

extern int            is_component_inside    (component_t *co, point_t *pt);

extern int            is_component_covered   (component_t *co, rectangle_t *re);

extern component_type component_get_type     (component_t *co);

extern void           component_selected     (component_t *co);

extern void           component_unselected   (component_t *co);

extern int            component_get_selected (component_t *co);

extern void           component_destory      (component_t *co);

#endif
