#ifndef __UML_MEOW_PLUGIN_MANAGER_H__
#define __UML_MEOW_PLUGIN_MANAGER_H__

#include "single_list-template.h"

typedef struct _plugin_widgets plugin_widgets_t;

GENERAL_SLIST_MODULE_DEF(plugin_widgets)

typedef SLIST(plugin_widgets) plugin_widgets_list_t;
typedef SLIST_NODE(plugin_widgets) plugin_widgets_unit_t;

#include "application.h"
#include "tool_plugin.h"

struct _plugin_widgets {
    GtkRadioToolButton *btn;
    GtkMenu            *menu;
    GtkBuilder         *builder;
    tool_plugin_t      *plugin;
};



#define plugin_widget_list_create() SLIST_CREATE(plugin_widgets)()
#define plugin_widgets_unit_create(pw) SLIST_NODE_CREATE(plugin_widgets)(pw)

#define plugin_widget_list_destroy(pwl) SLIST_DESTROY(plugin_widgets)(pwl)
#define plugin_widgets_unit_destroy(pwu) SLIST_NODE_DESTROY(plugin_widgets)(pwu)


extern void load_uml_plugins (application_t *app);


#endif
