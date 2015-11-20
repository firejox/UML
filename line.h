#ifndef __UML_LINE_H__
#define __UML_LINE_H__


#include "component.h"

#include "line_decorate.h"
#include "port_object.h"

typedef struct _line          line_t;
typedef struct _line_class    line_class;
typedef struct _line_private  line_private; 

struct _line {
    component_t parent;
    line_private *priv;
} line_t;


struct _line_class {
    component_class p_class;
    void (*update) (line_t *con);
};


extern line_t *line_ref             (line_t *con);

extern void line_update             (line_t *con);

extern void line_set_start_object   (line_t *con, port_object_t *port);
extern void line_set_end_object     (line_t *con, port_object_t *port);


extern const port_object_t *line_get_start_object (line_t *con);
extern const port_object_t *line_get_end_object   (line_t *con);


#endif
