#include "select.h"
#include <math.h>
#include <string.h>
#include <gtk/gtk.h>
#include <assert.h>

static select_data_t *data = NULL;
static GtkDialog  *ch_name  = NULL;
static GtkEntry   *entry    = NULL;

static const rectangle_t empty_rect = {0};

static void load_ch_name_dialog(void);

static void plugin_load(general_object_pool_t *pool) {
    data->pool = pool;
    data->select_count = 0;
}

static void merge_back_to_pool (general_object_pool_t *selected_pool) {
    general_object_pool_t *pool = data->pool;

    if (pool->tail == NULL) {
        pool->tail = selected_pool->tail;
    } else {
        selected_pool->tail->next = pool->head;
        pool->head->prev          = selected_pool->tail;
    }

    pool->head = selected_pool->head;

    selected_pool->head = selected_pool->tail = NULL;

}

static void move_to_selected_pool (general_object_unit_t *p) {
    general_object_unit_t *tmp;

    if (data->pool->head == p)
        data->pool->head = p->next;
    if (data->pool->tail == p)
        data->pool->tail = p->prev;

    if (p->next)
        p->next->prev = p->prev;
    if (p->prev)
        p->prev->next = p->next;

    p->next = p->prev = NULL;

    double_list_append (p, data->selected_pool);
}

static void mouse_press(double x, double y) {
    general_object_unit_t *p;
    component_t *co;

    data->st_pos.x = data->ed_pos.x = x;
    data->st_pos.y = data->ed_pos.y = y;

    for_each_node_in_double_list (p, data->pool) {
        co = GO_GET_COMPONENT(p->data);
        if (component_get_selected(co)) {
            component_unselected (co);
        }
    }
    
    for_each_node_in_double_list (p, data->pool) {
        co = GO_GET_COMPONENT(p->data);
        if (is_component_inside (co, &data->st_pos))
            break;
    }

    if (p) {
        xfunc_error_log("select component\n");
        component_selected (co);

        data->select_count = 1;
        
        xfunc_error_log("before move to selected_pool!\n");
        
        move_to_selected_pool (p);


        merge_back_to_pool (data->selected_pool);
    } else {
        xfunc_error_log("press empty area\n");
        data->select_count = 0;

        region_set_range (data->range, &empty_rect);

    }

}

static void mouse_drag (double x, double y) {
    object_t *obj;
    rectangle_t rect;

    data->ed_pos.x = x;
    data->ed_pos.y = y;

    if (data->select_count) {
        data->st_pos = data->ed_pos;

        xfunc_error_log("drag component\n");
        obj = (object_t*)GO_UNIT_GET_COMPONENT(data->pool->head);

        object_set_pos (obj, &data->ed_pos);
        object_update (obj);
    } else {
        xfunc_error_log("create rectangle\n");
        rect.center.x = (data->st_pos.x + data->ed_pos.x) / 2.0;
        rect.center.y = (data->st_pos.y + data->ed_pos.y) / 2.0;
        
        rect.width  = fabs (data->st_pos.x - data->ed_pos.x);
        rect.height = fabs (data->st_pos.y - data->ed_pos.y);

        region_set_range (data->range, &rect);
    }
}


static void mouse_release (double x, double y) {
    rectangle_t *rect = NULL;
    general_object_unit_t *p, *q = NULL;
    component_t *co;

    data->st_pos.x = data->ed_pos.x = x;
    data->st_pos.y = data->ed_pos.y = y;

    if (!data->select_count) {
        xfunc_error_log("empty rectangle\n");

        rect = region_get_range (data->range);
    
        for_each_node_in_double_list(p, data->pool) {
            if (q) {
                co = GO_GET_COMPONENT(q->data);

                if (is_component_covered (co, rect)) {
                    component_selected (co);
                    move_to_selected_pool (q);

                    data->select_count ++;
                }

            }
            q = p;
        }
        
        if (q) {
            co = GO_GET_COMPONENT(q->data);

            if (is_component_covered (co, rect)) {
                component_selected (co);
                move_to_selected_pool (q);

                data->select_count ++;
            }

        }
        if (data->select_count)
            merge_back_to_pool (data->selected_pool);
    
    }

}


static void select_group (GtkMenuItem *item, gpointer user_data) {
    general_object_unit_t *p, *q = NULL;
    general_object_t *obj;
    component_t *co;
    composite_object_t *com;

    if (data->select_count > 1) {
        for_each_node_in_double_list (p, data->pool) {
            if (!data->select_count)
                break;

            if (q) {
               move_to_selected_pool (q); 
            }

            data->select_count--;

            q = p;
        }

        move_to_selected_pool (q);

        xfunc_error_log ("selected pool %p", data->selected_pool->head);

        com = composite_object_group (data->selected_pool);

        obj = GO_CREATE(composite_object)(com);

        q = general_object_unit_create(obj);

        double_list_prepend(q, data->pool);

        component_selected (com);

        data->selected_pool = general_object_pool_create();
    }

    data->select_count = 1;

}

static void select_ungroup (GtkMenuItem *item, gpointer user_data) {
    composite_object_t *obj;
    general_object_t *g_obj;
    general_object_unit_t *g_unit;
    general_object_pool_t *tmp;

    int i;
    general_object_unit_t *p;
    

    if (data->select_count == 1) {
        g_unit = data->pool->head;
        g_obj = g_unit->data;
        
        i = 0;
        for_each_node_in_double_list(p, data->pool)
            i++;

        xfunc_error_log("pool size :%d\n", i);

        if (g_obj->type == GO_TYPE(composite_object)) {
            data->pool->head = g_unit->next;
            if (!data->pool->head)
                data->pool->tail = NULL;
            g_unit->data = NULL;
            g_unit->next = NULL;

            obj = (composite_object_t*)GO_GET_COMPONENT(g_obj);

            tmp = composite_object_ungroup (obj);
            
            i = 0;
            for_each_node_in_double_list(p, tmp) 
                i++;
            data->select_count = i;

            xfunc_error_log("compoite size :%d\n", i);

            merge_back_to_pool (tmp);

            i = 0;
            for_each_node_in_double_list(p, data->pool)
                i++;

            xfunc_error_log("pool size :%d\n", i);

            general_object_pool_destroy(tmp);
            general_object_unit_destroy(g_unit);
            
        }

    }

}


static void select_change_object_name (GtkMenuItem *item, gpointer user_data) {
    int res;
    component_t *co;
    const char *name;
    GtkWindow *parent = gtk_widget_get_toplevel(item);

    xfunc_error_log("change object name\n");

    if (data->select_count == 1 &&
            GO_UNIT_GET_TYPE(data->pool->head) != GO_TYPE(composite_object)) {
        co = GO_UNIT_GET_COMPONENT(data->pool->head);
        load_ch_name_dialog();
        gtk_window_set_transient_for (ch_name, parent);

        name = basic_object_get_name(co);
        gtk_entry_set_text (entry, name);


        res = gtk_dialog_run (GTK_DIALOG (ch_name));
        switch (res) {
            case GTK_RESPONSE_OK:
                basic_object_set_name (co, gtk_entry_get_text (entry));
                gtk_widget_destroy(ch_name);
                object_update(co);
                break;
            default:
                gtk_widget_destroy(ch_name);
                break;
        }


    }
}


static handle_t get_menuitem_handle (const char *label_name) {
    if (!strcmp (label_name, "group"))
        return (handle_t)select_group;
    else if (!strcmp (label_name, "ungroup"))
        return (handle_t)select_ungroup;
    else
        return (handle_t)select_change_object_name;
}

static component_t *get_tmp_component(void) {
    if (is_same_point (&data->st_pos, &data->ed_pos))
        return NULL;
    return (component_t*)data->range;
}

static void plugin_unload(void) {
    
    data->selected_pool->head = NULL;
    data->selected_pool->tail = NULL;
    data->select_count = 0;
}


#define SELECT_PLUGIN_RES_PATH "/tool_plugin/select_plugin/"

static tool_plugin_t select_plugin = {
    .resource_path = SELECT_PLUGIN_RES_PATH"select_plugin.ui",
    .style_path = SELECT_PLUGIN_RES_PATH"select_plugin.css",
    .button_name = "select_btn",
    .menu_name = "select_menu",

    .plugin_load = plugin_load,

    .mouse_press   = mouse_press,
    .mouse_drag    = mouse_drag,
    .mouse_release = mouse_release,

    .get_tmp_component = get_tmp_component,
    
    .get_menuitem_handle = get_menuitem_handle,

    .plugin_unload = plugin_unload
};

static void load_ch_name_dialog(void) {
    GtkBuilder *builder = NULL;

    builder = gtk_builder_new_from_resource (
            SELECT_PLUGIN_RES_PATH "change_object_name.ui");

    ch_name = GTK_DIALOG (gtk_builder_get_object (builder, 
                "change_object_name_dialog"));

    entry = GTK_ENTRY (gtk_builder_get_object (builder,
                "basic_object_name"));

    gtk_builder_connect_signals (builder, NULL);

    ch_name = g_object_ref (ch_name);

    g_object_unref (G_OBJECT (builder));
}

tool_plugin_t *tool_plugin_init(void) {
    if (!data) {
        select_plugin_register_resource();

        data = xcalloc (1, sizeof (select_data_t));
        data->selected_pool = general_object_pool_create();
        data->range = region_create();

    }

    return &select_plugin;
}
