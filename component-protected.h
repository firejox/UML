#ifndef __UML_COMPONENT_PROTECTED_H__

#include "component.h"

extern void component_init_class (component_t *co,
                     component_type type, component_class *_class);

extern void component_mark_dirty (component_t *co);

#endif
