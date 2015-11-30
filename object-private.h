#ifndef __UML_OBJECT_PRIVATE_H__
#define __UML_OBJECT_PRIVATE_H__

#include "object-protected.h"
#include "component-protected.h"

struct _object_private {
    unsigned int    type:2;
    point_t         pos;
    object_class    *_class;
};


#endif
