#include "class_plugin.h"
#include <gtk/gtk.h>

static class_data_t *data = NULL;


static void plugin_load(general_object_pool_t *pool) {
    data->pool = pool;
}

static void mouse_press(double x, double y) {
    class_object_t *obj = NULL;
    point_t pt = {.x = x, .y = y};

    general_object_t *g_obj = NULL;
    general_object_unit_t *nd = NULL;

    obj = class_object_create (&pt);

    g_obj = GO_CREATE(basic_object)(obj);

    nd = general_object_unit_create(g_obj);

    double_list_prepend (nd, data->pool);

}

static void mouse_drag (double x, double y) {
    
}


static void mouse_release (double x, double y) {
    

}

static void empty_handle (GtkMenuItem *item, gpointer data) {}

static handle_t get_menuitem_handle (const char *label_name) {
    return (handle_t)empty_handle;
}

static component_t *get_tmp_component(void) {
    return NULL;
}

static void plugin_unload(void) {
    
}


#define SELECT_PLUGIN_RES_PATH "/tool_plugin/class_plugin/"

static tool_plugin_t class_plugin = {
    .resource_path = SELECT_PLUGIN_RES_PATH "class_plugin.ui",
    .style_path = SELECT_PLUGIN_RES_PATH "class_plugin.css",
    .button_name = "class_btn",
    .menu_name = NULL,

    .plugin_load = plugin_load,

    .mouse_press   = mouse_press,
    .mouse_drag    = mouse_drag,
    .mouse_release = mouse_release,

    .get_tmp_component = get_tmp_component,

    .plugin_unload = plugin_unload
};



tool_plugin_t *tool_plugin_init(void) {
    if (!data) {
        class_plugin_register_resource();

        data = xcalloc (1, sizeof (class_data_t));
    }

    return &class_plugin;
}
