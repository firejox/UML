#ifndef __UML_LINE_H__
#define __UML_LINE_H__

typedef struct _line          line_t;
typedef struct _line_class    line_class;
typedef struct _line_private  line_private;

#include "component.h"

#include "line_decorate.h"
#include "port_object.h"
 

struct _line {
    component_t parent;
    line_private *priv;
};


struct _line_class {
    line_path_t *(* const path_create) (point_t *st, point_t *ed);

    void (* const start_decorate_update) 
                    (line_decorate_t *dec, line_path_t *path);
    void (* const end_decorate_update) 
                    (line_decorate_t *dec, line_path_t *path);
};



extern void line_update             (line_t *con);

extern void line_set_start_port   (line_t *con, port_object_t *port);
extern void line_set_end_port     (line_t *con, port_object_t *port);


extern const port_object_t *line_get_start_port (line_t *con);
extern const port_object_t *line_get_end_port   (line_t *con);


#endif
