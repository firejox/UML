#ifndef __UML_OBJECT_H__
#define __UML_OBJECT_H__

#include "component.h"

typedef struct _object object_t;
typedef struct _object_class object_class;
typedef struct _object_private object_private;

typedef enum _object_type object_type;

enum _object_type {
    BASIC_OBJECT_TYPE,
    COMPOSITE_OBJECT_TYPE,
    PORT_OBJECT_TYPE,
    LINE_DECORATE_TYPE
};

struct _object {
    component_t parent;
    object_private *priv;
};

struct _object_class {
    component_class p_class;

    void               (*update)     (object_t *obj);
    const rectangle_t *(*get_region) (object_t *obj);
};


extern void object_update (object_t *obj);

extern void object_set_pos (object_t *obj, point_t *pos);
extern const point_t *object_get_pos (object_t *obj);

extern const rectangle_t *object_get_region (object_t *obj);

extern object_type object_get_type (object_t *obj);

#endif
