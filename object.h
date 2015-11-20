#ifndef __UML_OBJECT_H__
#define __UML_OBJECT_H__

#include "component.h"

typedef struct _object object_t;
typedef struct _object_class object_class;
typedef struct _object_private object_private;


struct _object {
    component_t parent;
    object_private *priv;
};

struct _object_class {
    component_class p_class;

    void (*update)  (object_t *obj);
};


extern void object_update (object_t *obj);
extern void object_set_pos (object_t *obj, point_t *pos);
extern void object_get_pos (object_t *obj, point_t *pos);

#endif
