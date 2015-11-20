

#ifndef __UML_COMPONENT_PRIVATE_H__
#define __UML_COMPONENT_PRIVATE_H__

#include "component-protected.h"

struct component_private {
    unsigned int     is_selected:1;
    unsigned int     is_dirty:1;
    unsigned int     type:2;
    component_class *_class;
};

#endif
