#ifndef __RESOURCE_association_line_plugin_H__
#define __RESOURCE_association_line_plugin_H__

#include <gio/gio.h>

extern GResource *association_line_plugin_get_resource (void);

extern void association_line_plugin_register_resource (void);
extern void association_line_plugin_unregister_resource (void);

#endif
