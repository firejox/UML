#ifndef __UML_PORT_OBJECT_H__
#define __UML_PORT_OBJECT_H__

typedef struct _port_object port_object_t;
typedef struct _port_object_private port_object_private;

#include "basic_object.h"
#include "line.h"


struct _port_object {
    object_t  parent;
    port_object_private *priv;
};


port_object_t *port_object_create (basic_object_t *obj, point_t *pos);

basic_object_t *port_object_get_basic_object (port_object_t *port);

void port_object_link_line (port_object_t *port, line_t *con);

void port_object_unlink_line (port_object_t *port, line_t *con);

void port_object_get_absolute_pos (port_object_t *port, point_t *pos);

#endif
