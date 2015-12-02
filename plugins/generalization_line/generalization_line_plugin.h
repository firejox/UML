#ifndef __UML_MEOW_GENERALIZATION_LINE_PLUGIN_H__
#define __UML_MEOW_GENERALIZATION_LINE_PLUGIN_H__

#include "../../tool_plugin.h"
#include "../../utils.h"
#include "generalization_line-private.h"
#include "resource.h"

typedef struct _generalization_line_data generalization_line_data_t;

struct _generalization_line_data {
    general_object_pool_t *pool;

    generalization_line_t *tmp;

    point_t st_pos;
    point_t ed_pos;

    port_object_t *st_port;
    port_object_t *ed_port;

    basic_object_t *st_obj;
    basic_object_t *ed_obj;
    
};


#endif
