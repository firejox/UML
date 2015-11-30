#ifndef __UML_MEOW_GENERALIZATION_LINE_H__
#define __UML_MEOW_GENERALIZATION_LINE_H__

#include "../../line.h"

typedef struct _generalization_line generalization_line_t;
typedef struct _generalization_line_class generalization_line_class;
typedef struct _generalization_line_private generalization_line_private;

struct _generalization_line {
    line_t parent;
    generalization_line_private *priv;
};

struct _generalization_line_class {
    line_class p_class;
};

extern generalization_line_t *generalization_line_create 
                                    (port_object_t *st, port_object_t *ed);

#endif
