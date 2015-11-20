#ifndef __UML_PORT_OBJECT_H__
#define __UML_PORT_OBJECT_H__

#include "basic_object.h"
#include "line.h"

typedef struct _port_object port_object_t;
typedef struct _port_object_class port_object_class;
typedef struct _port_object_private port_object_private;

struct _port_object {
    object_t  parent;
    port_object_private *priv;
};

struct _port_object_class {
    object_class  p_class;
};


port_object_t *port_object_create (basic_object *obj, point_t *pos);

rectangle_t *port_object_get_basic_object_region (port_object_t *port);

void port_object_link_line (port_object_t *port, line_t *con);

void port_object_unlink_line (port_object_t *port, line_t *con);


#endif
