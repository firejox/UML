#ifndef __UML_MEOW_APPLICATION_H__
#define __UML_MEOW_APPLICATION_H__

#include <gtk/gtk.h>

typedef struct _application application_t;

#include "plugin_manager.h"

struct _application {
    GtkApplicationWindow    *app;
    GdkScreen               *scr;
    plugin_widgets_list_t   *plugins;
};

extern void application_init (application_t *, int *argc, char ***argv);

extern void load_resource (application_t *app);

extern void application_run (application_t *app);

#endif
