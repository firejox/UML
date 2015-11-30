#ifndef __UML_BASIC_OBJECT_PROTECTED_H__
#define __UML_BASIC_OBJECT_PROTECTED_H__

#include "basic_object.h"

#include "single_list-template.h"

GENERAL_SLIST_MODULE_DEF(port_object)

extern void basic_object_init_class (basic_object_t *obj, basic_object_class *_class);

extern void basic_object_add_port (basic_object_t *obj, port_object_t *port);

extern SLIST(port_object) *basic_object_get_ports (basic_object_t *obj);

#endif
