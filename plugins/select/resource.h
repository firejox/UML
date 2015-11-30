#ifndef __RESOURCE_select_plugin_H__
#define __RESOURCE_select_plugin_H__

#include <gio/gio.h>

extern GResource *select_plugin_get_resource (void);

extern void select_plugin_register_resource (void);
extern void select_plugin_unregister_resource (void);

#endif
