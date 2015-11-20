#ifndef __UML_BASIC_OBJECT_H__
#define __UML_BASIC_OBJECT_H__

#include "object.h"
#include "port_object.h"


typedef struct _basic_object basic_object_t;
typedef struct _basic_object_class basic_object_class;
typedef struct _basic_object_private basic_object_private;


struct _basic_object {
    object_t parent;
    basic_object_private *priv;
};


struct _basic_object_class {
    object_class p_class; 

    port_object_t *(*get_port_object) (basic_object_t *obj, point_t *pos);
    rectangle_t   *(*get_region)      (basic_object_t *obj);

};


void basic_object_set_name (basic_object_t *obj, const char *name);

const char *basic_object_get_name (basic_object_t *obj);


port_object_t *basic_object_get_port_object 
                            (basic_object_t *obj, point_t *pos);

#endif
