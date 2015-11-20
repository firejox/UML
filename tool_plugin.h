#ifndef __TOOL_PLUGIN_H__
#define __TOOL_PLUGIN_H__

#include "drawobj.h"

typedef struct _tool_plugin {
    void (*mouse_event_handle)();
    draw_obj_type (*get_draw_obj_type)(void);
} tool_plugin_t;

void tool_plugin_init (tool_plugin_t **plugin);




#endif
