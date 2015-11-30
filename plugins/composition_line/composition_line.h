#ifndef __UML_MEOW_COMPOSITION_LINE_H__
#define __UML_MEOW_COMPOSITION_LINE_H__

#include "../../line.h"

typedef struct _composition_line composition_line_t;
typedef struct _composition_line_class composition_line_class;
typedef struct _composition_line_private composition_line_private;


struct _composition_line {
    line_t parent;
    composition_line_private *priv;
};

struct _composition_line_class {
    line_class p_class;
};


extern composition_line_t *composition_line_create 
                        (port_object_t *st, port_object_t *ed);

#endif
