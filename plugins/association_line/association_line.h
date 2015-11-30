#ifndef __UML_MEOW_ASSOCIATION_LINE_H__
#define __UML_MEOW_ASSOCIATION_LINE_H__

#include "../../line.h"

typedef struct _association_line association_line_t;
typedef struct _association_line_class association_line_class;
typedef struct _association_line_private association_line_private;

struct _association_line {
    line_t parent;
    association_line_private *priv;
};

struct _association_line_class {
    line_class p_class;
};

association_line_t *association_line_create 
                        (port_object_t *st, port_object_t *ed);

#endif
