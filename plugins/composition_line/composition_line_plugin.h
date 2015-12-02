#ifndef __UML_MEOW_COMPOSITION_LINE_PLUGIN_H__
#define __UML_MEOW_COMPOSITION_LINE_PLUGIN_H__

#include "../../tool_plugin.h"
#include "../../utils.h"
#include "composition_line-private.h"
#include "resource.h"

typedef struct _composition_line_data composition_line_data_t;

struct _composition_line_data {
    general_object_pool_t *pool;

    composition_line_t *tmp;

    point_t st_pos;
    point_t ed_pos;

    port_object_t *st_port;
    port_object_t *ed_port;

    basic_object_t *st_obj;
    basic_object_t *ed_obj;
    
};


#endif
