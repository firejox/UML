#ifndef __TOOL_PLUGIN_H__
#define __TOOL_PLUGIN_H__

#include "general_object_pool.h"

typedef void (*handle_t)(void *, void *);

typedef struct _tool_plugin {
    const char  *resource_path;
    const char  *style_path;
    const char  *button_name;
    const char  *menu_name;

    void         (*plugin_load)         (general_object_pool_t *pool);

    void         (*mouse_press)         (double x, double y);
    void         (*mouse_release)       (double x, double y);
    void         (*mouse_drag)          (double x, double y);

    handle_t     (*get_menuitem_handle) (const char *label_name);

    void         (*plugin_unload)       (void);

    component_t *(*get_tmp_component)   (void);

} tool_plugin_t;

typedef tool_plugin_t *(*tool_plugin_init_func)(void);

tool_plugin_t *tool_plugin_init (void);



#endif
