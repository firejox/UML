#ifndef __RESOURCE_generalization_line_plugin_H__
#define __RESOURCE_generalization_line_plugin_H__

#include <gio/gio.h>

extern GResource *generalization_line_plugin_get_resource (void);

extern void generalization_line_plugin_register_resource (void);
extern void generalization_line_plugin_unregister_resource (void);

#endif
