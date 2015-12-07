#include "generalization_line_plugin.h"
#include <gtk/gtk.h>
#include <math.h>

static generalization_line_data_t *data = NULL;

static void plugin_load(general_object_pool_t *pool) {
    data->pool = pool;
}


static void move_to_top (general_object_unit_t *p) {
    general_object_pool_t *pool = data->pool;

    if (pool->head == p)
        pool->head = p->next;
    if (pool->tail == p)
        pool->tail = p->prev;

    if (p->next)
        p->next->prev = p->prev;
    if (p->prev)
        p->prev->next = p->next;

    p->next = p->prev = NULL;

    double_list_prepend (p, pool);

}

static void mouse_press(double x, double y) {
    point_t pt = {.x = x, .y = y};
    general_object_unit_t *p;
    component_t *co;
    port_object_t *port;

    for_each_node_in_double_list (p, data->pool) {
       if (p->data->type != GO_TYPE(composite_object)) {
           co = GO_GET_COMPONENT(p->data);

           if (is_component_inside (co, &pt))
               break;
       }
    }

    if (p) {
        move_to_top (p);

        port = basic_object_get_port_object ((basic_object_t*)co, &pt);

        line_factory_register_start_port (data->fact, port);

        line_factory_setup_end_pos (data->fact, &pt);
        
        data->st_flag = 1;
    }
}

static void mouse_drag (double x, double y) {
    line_path_t *path;
    point_t pt = {.x = x, .y = y};
    
    line_factory_setup_end_pos (data->fact, &pt);
}


static void mouse_release (double x, double y) {
    general_object_unit_t *p;
    point_t pt = {.x = x, .y = y};
    component_t *co;
    port_object_t *port;

    if (data->st_flag) {

        for_each_node_in_double_list (p, data->pool) {
            if (p->data->type != GO_TYPE(composite_object)) {
                co = GO_GET_COMPONENT(p->data);

                if (is_component_inside (co, &pt))
                    break;
            }
        }

        if (p) {
            move_to_top (p);

            port = basic_object_get_port_object ((basic_object_t*)co, &pt);

            line_factory_register_end_port (data->fact, port);

            line_factory_produce_one (data->fact);
        }

        line_factory_unregister_all (data->fact);

        data->st_flag = 0;
    }   
}

static void empty_handle (GtkMenuItem *item, gpointer data) {}

static handle_t get_menuitem_handle (const char *label_name) {
    return (handle_t)empty_handle;
}

static component_t *get_tmp_component(void) {
    return line_factory_get_sample (data->fact);
}

static void plugin_unload(void) {
    data->st_flag = 0;
    line_factory_unregister_all (data->fact);
}

#define SELECT_PLUGIN_RES_PATH "/tool_plugin/generalization_line_plugin/"

static tool_plugin_t generalization_line_plugin = {
    .resource_path = SELECT_PLUGIN_RES_PATH "generalization_line_plugin.ui",
    .style_path = SELECT_PLUGIN_RES_PATH "generalization_line_plugin.css",
    .button_name = "generalization_line_btn",
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
        generalization_line_plugin_register_resource();

        data = xcalloc (1, sizeof (generalization_line_data_t));

        data->fact = generalization_line_factory_create();
    }

    return &generalization_line_plugin;
}


