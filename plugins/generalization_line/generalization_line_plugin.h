#ifndef __UML_MEOW_GENERALIZATION_LINE_PLUGIN_H__
#define __UML_MEOW_GENERALIZATION_LINE_PLUGIN_H__

#include "../../tool_plugin.h"
#include "../../utils.h"
#include "generalization_line_factory.h"
#include "resource.h"

typedef struct _generalization_line_data generalization_line_data_t;

struct _generalization_line_data {
    general_object_pool_t   *pool;

    line_factory_t          *fact;

    unsigned int            st_flag:1;
};


#endif
