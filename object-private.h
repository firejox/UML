#ifndef __UML_OBJECT_PRIVATE_H__
#define __UML_OBJECT_PRIVATE_H__

#include "object-protected.h"
#include "component-protected.h"

struct object_private {
    point_t pos;
    object_class *_class;
};


#endif
