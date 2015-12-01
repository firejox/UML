#ifndef __RESOURCE_use_case_plugin_H__
#define __RESOURCE_use_case_plugin_H__

#include <gio/gio.h>

extern GResource *use_case_plugin_get_resource (void);

extern void use_case_plugin_register_resource (void);
extern void use_case_plugin_unregister_resource (void);

#endif
