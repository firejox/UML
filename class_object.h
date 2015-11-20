#ifndef __UML_CLASS_OBJECT_H__
#define __UML_CLASS_OBJECT_H__

#include "basic_object.h"

typedef struct _class_object class_object_t;
typedef struct _class_object_class class_object_class;
typedef struct _class_object_private class_object_private;

struct _class_object {
    basic_object_t parent;
    class_object_private *priv;
};

struct _class_object_class {
    basic_object_class p_class;
};

extern class_object_t *class_object_create  (point_t *pos);



#endif
