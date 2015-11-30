#ifndef __UML_BASIC_OBJECT_PRIVATE_H__
#define __UML_BASIC_OBJECT_PRIVATE_H__

#include "basic_object-protected.h"
#include "object-protected.h"


struct _basic_object_private {
    SLIST(port_object)      *ports;
    xstring_t               *name;
    basic_object_class      *_class;
    rectangle_t             range;
};

#endif
