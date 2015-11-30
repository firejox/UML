#ifndef __UML_USE_CASE_OBJECT_H__
#define __UML_USE_CASE_OBJECT_H__

#include "../../basic_object.h"

typedef struct _use_case_object use_case_object_t;
typedef struct _use_case_object_class  use_case_object_class;
typedef struct _use_case_object_private use_case_object_private;

struct _use_case_object {
    basic_object_t  parent;
    use_case_object_private *priv;
};

struct _use_case_object_class {
    basic_object_class p_class;
};


extern use_case_object_t *use_case_object_create  (point_t *pos);



#endif
