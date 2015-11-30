#ifndef __RESOURCE_class_plugin_H__
#define __RESOURCE_class_plugin_H__

#include <gio/gio.h>

extern GResource *class_plugin_get_resource (void);

extern void class_plugin_register_resource (void);
extern void class_plugin_unregister_resource (void);

#endif
