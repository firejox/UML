#ifndef __UML_BASIC_OBJECT_PROTECTED_H__
#define __UML_BASIC_OBJECT_PROTECTED_H__

#include "basic_object.h"

void basic_object_init_class (basic_object_t *obj, basic_object_class *_class);

void basic_object_add_port (basic_object_t *obj, port_object_t *port);

single_list_t *basic_object_get_ports (basic_object_t *obj);

#endif
