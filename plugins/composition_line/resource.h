#ifndef __RESOURCE_composition_line_plugin_H__
#define __RESOURCE_composition_line_plugin_H__

#include <gio/gio.h>

extern GResource *composition_line_plugin_get_resource (void);

extern void composition_line_plugin_register_resource (void);
extern void composition_line_plugin_unregister_resource (void);

#endif
