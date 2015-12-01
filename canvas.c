#include "utils.h"
#include "canvas-private.h"
#include "tool_plugin.h"
#include <math.h>

static canvas_private *cur_canvas = NULL;
static tool_plugin_t *cur_plugin = NULL;

void plugin_change (GtkToggleToolButton *btn, gpointer user_data) {
    int res = gtk_toggle_tool_button_get_active (btn);

    tool_plugin_t *data_plugin = (tool_plugin_t*)user_data;

    if (res) {
        xfunc_error_log ("load next plugin.\n");
        cur_plugin = data_plugin;
        xfunc_error_log ("current plugin addr : %p\n", cur_plugin);
        if (cur_plugin) {
            if (cur_canvas)
                cur_plugin->plugin_load(cur_canvas->pool);
        }
    } else {
        xfunc_error_log ("unload current plugin. \n");
        if (cur_plugin) {
            cur_plugin->plugin_unload();
        }
        cur_plugin = NULL;
    }

}


static void clear_surface (canvas_t *ca) {

    cairo_set_source_rgb (ca->cr, 1.0, 1.0, 1.0);
    
    cairo_paint (ca->cr);

    cairo_set_operator (ca->cr, CAIRO_OPERATOR_OVER);
}

static void draw_all_object (canvas_private *ca, component_t *co) {
    general_object_unit_t *p;


    for_each_node_in_double_list_reverse (p, ca->pool) {
        component_paint (GO_UNIT_GET_COMPONENT(p), ca);
    }

    component_paint (co, ca);
}

static void canvas_draw (GtkWidget *widget, canvas_private *ca, component_t *co) {
    draw_all_object (ca, co);
    gtk_widget_queue_draw (widget);
}

static gboolean draw_configure (GtkWidget *widget,
                    GdkEventConfigure *event, gpointer user_data) {
    canvas_private *ca = (canvas_private*)user_data;
    cairo_surface_t *surface = ca->surface;
    GdkWindow *window;

    int w, h;

    xfunc_error_log ("draw configure!\n");

    if (surface) {
        cairo_destroy (ca->ca.cr);
        cairo_surface_destroy (surface);
    }

    window = gtk_widget_get_window (widget);

    w = gtk_widget_get_allocated_width (widget);
    h = gtk_widget_get_allocated_height (widget);


    surface = gdk_window_create_similar_surface 
                        (window, CAIRO_CONTENT_COLOR_ALPHA, w, h);

    ca->surface = surface;
    ca->ca.cr = cairo_create (surface);

    clear_surface (ca);

    if (cur_plugin) {
        draw_all_object (ca, cur_plugin->get_tmp_component());    
    } else 
        draw_all_object (ca, NULL);

    cairo_destroy(ca->ca.cr);

    ca->ca.cr = NULL;

    return TRUE;
}


static gboolean draw_widget (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    canvas_private *ca = user_data;

    cairo_set_source_surface (cr, ca->surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}

static gboolean mouse_press (GtkWidget *widget,
                     GdkEventButton *ev, gpointer user_data) {
    canvas_private *ca = user_data;

    
    if (!ca->surface)
        return FALSE;

    if (ev->button == GDK_BUTTON_PRIMARY) {
        if (cur_plugin) {
            ca->ca.cr = cairo_create (ca->surface);

            clear_surface (ca);

            cur_plugin->mouse_press (ev->x, ev->y);

            canvas_draw (widget, ca, cur_plugin->get_tmp_component());

            cairo_destroy (ca->ca.cr);
            
            ca->ca.cr = NULL;
        }
    
    }

    return TRUE;
}

static gboolean mouse_drag (GtkWidget *widget,
        GdkEventMotion *ev, gpointer user_data) {
    canvas_private *ca = user_data;

    if (!ca->surface)
        return FALSE;

    if (ev->state & GDK_BUTTON1_MASK) {
        if (cur_plugin) {
            xfunc_error_log("mouse drag !\n");

            ca->ca.cr = cairo_create (ca->surface);

            clear_surface (ca);

            cur_plugin->mouse_drag (ev->x, ev->y);

            canvas_draw (widget, ca, cur_plugin->get_tmp_component());

            cairo_destroy (ca->ca.cr);
            
            ca->ca.cr = NULL;
        }
    
    }

    return TRUE;
}

static gboolean mouse_release (GtkWidget *widget,
        GdkEventButton *ev, gpointer user_data) {
    canvas_private *ca = user_data;

    if (!ca->surface)
        return FALSE;

    if (ev->button == GDK_BUTTON_PRIMARY) {
        if (cur_plugin) {
            ca->ca.cr = cairo_create (ca->surface);
            
            clear_surface (ca);

            cur_plugin->mouse_release (ev->x, ev->y);

            canvas_draw (widget, ca, cur_plugin->get_tmp_component());
            
            cairo_destroy (ca->ca.cr);
            
            ca->ca.cr = NULL;
        }
    
    }

    return TRUE;

}


static void canvas_private_destroy (canvas_private *ca) {
    if (ca->ca.cr)
        cairo_destroy (ca->ca.cr);
    if (ca->surface)
        cairo_surface_destroy (ca->surface);

    general_object_pool_destroy (ca->pool);

    xfree (ca);
}

static void draw_area_clean (GtkWidget *widget, gpointer user_data) {

    xfunc_error_log("drawing area destory !\n");

    canvas_private_destroy (user_data);

    cur_plugin = NULL;
    cur_canvas = NULL;

}

static canvas_private *canvas_private_create (GtkDrawingArea *d_area) {
    canvas_private *ca = xcalloc (1, sizeof (canvas_private));

    ca->pool = general_object_pool_create();

    g_signal_connect (d_area, "draw", G_CALLBACK(draw_widget), ca);

    g_signal_connect (d_area, "configure-event",
            G_CALLBACK(draw_configure), ca);

    g_signal_connect (d_area, "destroy",
            G_CALLBACK(draw_area_clean), ca);

    g_signal_connect (d_area, "motion-notify-event", 
            G_CALLBACK(mouse_drag), ca);

    g_signal_connect (d_area, "button-press-event", 
            G_CALLBACK(mouse_press), ca);

    g_signal_connect (d_area, "button-release-event",
            G_CALLBACK(mouse_release), ca);
    
    return ca;
}


void drawing_area_initial (GtkDrawingArea *area) {
    canvas_private *ca = canvas_private_create (area);

    gtk_widget_add_events (area, GDK_BUTTON_PRESS_MASK
                               | GDK_POINTER_MOTION_MASK
                               | GDK_BUTTON_RELEASE_MASK);

    cur_canvas = ca;
}
