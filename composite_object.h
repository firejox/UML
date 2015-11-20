#ifndef __UML_COMPOSITE_OBJECT_H__
#define __UML_COMPOSITE_OBJECT_H__

#include "object.h"

typedef struct _composite_object composite_object_t;
typedef struct _composite_object_class composite_object_class;
typedef struct _composite_object_private composite_object_private;


struct _composite_object {
    object_t parent;
    composite_object_private *priv;
};

struct _composite_object_class {
    object_class p_class;
};



#endif
