#include "plugin_manager.h"
#include "utils.h"
#include <glob.h>
#include <dlfcn.h>

#include <errno.h>
#include <string.h>



static void menu_connect_cb (GtkWidget *widget, gpointer user_data) {
    GtkMenuItem *item = GTK_MENU_ITEM (widget);

    tool_plugin_t *tp = user_data;

    const char *name = gtk_menu_item_get_label (item);


    xfunc_error_log("menu item label : %s\n", name);

    g_signal_connect (item, "activate",
            G_CALLBACK(tp->get_menuitem_handle(name)), tp);

}

static void plugin_get_widgets (plugin_widgets_t *pw) {
    tool_plugin_t *tp = pw->plugin;

    pw->builder = gtk_builder_new_from_resource (tp->resource_path);
    pw->btn = GTK_RADIO_TOOL_BUTTON(
            gtk_builder_get_object (pw->builder, tp->button_name));
    if (tp->menu_name) {
        pw->menu = gtk_builder_get_object (pw->builder, tp->menu_name);

        gtk_container_foreach(pw->menu, menu_connect_cb, tp);
    }
    else 
        pw->menu = NULL;
}

static plugin_widgets_t *plugin_widgets_create (tool_plugin_t *tp, void *handle) {
    plugin_widgets_t *pw = xmalloc (sizeof (plugin_widgets_t));

    pw->plugin = tp;
    xfunc_error_log("plugin_addr : %p\n", pw->plugin);

    plugin_get_widgets (pw);

    pw->handle = handle;

    return pw;
}

static void plugin_widgets_destroy (plugin_widgets_t *pw) {
    dlclose(pw->handle);
    xfree (pw);
}


static plugin_widgets_unit_t *load_plugin_by_path (const char *path) {
    plugin_widgets_t *pw = NULL;

    void *handle;
    tool_plugin_init_func init_func;
    const char *error_msg = NULL;
    
    handle = dlopen (path, RTLD_LAZY);
    if (!handle) {
        xfunc_error_log("%s\n", dlerror());
        return NULL;
    }

    dlerror(); /*clear any existing error */
    
    init_func = (tool_plugin_init_func)dlsym (handle, "tool_plugin_init");

    error_msg = dlerror (); 
    if (error_msg != NULL) {
        xfunc_error_log("tool_plugin_init is not exists : %s\n", error_msg);
        dlclose (handle);
        return NULL;
    }

    pw = plugin_widgets_create (init_func(), handle);


    return plugin_widgets_unit_create(pw);
}



static plugin_widgets_list_t *find_plugins (void) {
    glob_t plugins_path;
    int res, i;

    plugin_widgets_unit_t *pw_u;
    plugin_widgets_list_t *pw_l = plugin_widget_list_create();

    plugins_path.gl_offs = 0;
    
    res = glob(PLUGIN_DIR "*.so", GLOB_DOOFFS , NULL, &plugins_path);

    if (res) 
        xfunc_error_log ("find plugin error : %s\n", strerror (errno));
    else {

        for (i = 0; i < plugins_path.gl_pathc; i++) {
            pw_u = load_plugin_by_path (plugins_path.gl_pathv[i]);

            if (pw_u) 
                single_list_prepend(pw_l, pw_u);
        }
    }

    globfree (&plugins_path);
    
    return pw_l;
}

void load_uml_plugins (application_t *app) {
    app->plugins = find_plugins ();
}



GENERAL_SLIST_MODULE_IMPL(plugin_widgets, plugin_widgets_destroy)
