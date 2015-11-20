#ifndef __UML_PORT_OBJECT_PRIVATE_H__
#define __UML_PORT_OBJECT_PRIVATE_H__


#include "port_object.h"
#include "object-protected.h"

struct _port_object_private {
    basic_object_t *src_obj;
    single_list_t  *cons;
};


#endif
