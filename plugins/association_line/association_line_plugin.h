#ifndef __UML_MEOW_ASSOCIATION_LINE_PLUGIN_H__
#define __UML_MEOW_ASSOCIATION_LINE_PLUGIN_H__

#include "../../tool_plugin.h"
#include "../../utils.h"
#include "association_line-private.h"
#include "resource.h"

typedef struct _association_line_data association_line_data_t;

struct _association_line_data {
    general_object_pool_t *pool;

    association_line_t *tmp;

    point_t st_pos;
    point_t ed_pos;

    port_object_t *st_port;
    port_object_t *ed_port;

    basic_object_t *st_obj;
    basic_object_t *ed_obj;

};


#endif
