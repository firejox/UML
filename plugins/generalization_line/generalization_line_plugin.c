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

    data->st_obj = NULL;

    for_each_node_in_double_list (p, data->pool) {
       if (p->type != GO_TYPE(composite_object)) {
           co = GO_GET_COMPONENT(p->data);

           if (is_component_inside (co, &pt))
               break;
       }
    }

    if (p) {
        move_to_top (p);

        data->st_obj = (basic_object_t *)co;

        data->st_port = basic_object_get_port_object (data->st_obj, &pt);

        port_object_get_absolute_pos(data->st_port, &data->st_pos);

    }
}

static void mouse_drag (double x, double y) {
    line_path_t *path;

    if (data->st_port) {
        data->ed_pos.x = x;
        data->ed_pos.y = y;

        set_start_decorate (data->tmp, &data->st_pos, &data->ed_pos);
        path = path_create (&data->st_pos, &data->ed_pos);

        line_set_line_path (data->tmp, path);
    }
}


static void mouse_release (double x, double y) {
    general_object_unit_t *p;
    point_t pt = {.x = x, .y = y};
    generalization_line_t *con;


    if (data->st_obj) {
        data->ed.x = x;
        data->ed.y = y;

        for_each_node_in_double_list (p, data->pool) {
            if (p->type != GO_TYPE(composite_object)) {
                co = GO_GET_COMPONENT(p->data);

                if (is_component_inside (co, &pt))
                    break;
            }
        }

        if (p) {
            move_to_top (p);

            data->ed_obj = (basic_object_t *)co; 

            if (data->ed_obj == data->st_obj) {

                data->ed_port = basic_object_get_port_object 
                                            (data->st_obj, &pt);

                con = generalization_line_create (data->st_port, data->ed_port);

                port_object_link_line (data->st_port, con);

                port_object_link_line (data->ed_port, con);

            }



        }

        data->st_obj = NULL;
    }   
}

static void empty_handle (GtkMenuItem *item, gpointer data) {}

static handle_t get_menuitem_handle (const char *label_name) {
    return (handle_t)empty_handle;
}

static component_t *get_tmp_component(void) {
    if (!data->st_port)
        return NULL;
    return data->tmp;
}

static void plugin_unload(void) {
    data->st_port = NULL;
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
        data->tmp = generalization_line_create(NULL, NULL);
    }

    return &generalization_line_plugin;
}


