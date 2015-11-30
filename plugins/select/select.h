#ifndef __UML_MEOW_SELECT_PLUGIN_H__
#define __UML_MEOW_SELECT_PLUGIN_H__


#include "../../tool_plugin.h"
#include "../../region.h"
#include "../../utils.h"
#include "resource.h"

typedef struct _select_data select_data_t;

struct _select_data {
    general_object_pool_t *pool;
    general_object_pool_t *selected_pool;

    region_t *range;
    point_t ed_pos;
    point_t st_pos;
    int select_count; 
};

#endif
