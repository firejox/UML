#include "utils.h"
#include "application.h"

#include "canvas-protected.h"
#include "plugin_manager.h"



void application_init (application_t *app, int *argc, char ***argv) {
    gtk_init (argc, argv);
    
    app->scr = gdk_screen_get_default();

    load_uml_plugins (app);

}



static void menu_connect_canvas (GtkWidget *widget, gpointer user_data) {
    GtkMenuItem    *item = GTK_MENU_ITEM (widget);
    GtkDrawingArea *d_area = GTK_DRAWING_AREA (user_data);

    g_signal_connect_swapped (item, "activate",
            (GCallback)gtk_widget_queue_resize, d_area); 

}

static void gui_structure_link_plugins 
                (GtkBuilder *build, plugin_widgets_list_t *plugins) {
    GtkToolbar         *uml_toolbar;
    GtkRadioToolButton *origin_btn;
    GSList             *o_group;
    GtkMenuItem        *edit_item;
    GtkDrawingArea     *d_area;
    
    plugin_widgets_unit_t *p;
    
 /*************************** load tool bar **************************/

    uml_toolbar = gtk_builder_get_object (build, "UML_toolbar");

/******************** origin_btn load and initial ********************/
    origin_btn = gtk_builder_get_object (build, "origin_btn");
    g_signal_connect (origin_btn, "toggled",
            G_CALLBACK(plugin_change), NULL);

    o_group = gtk_radio_tool_button_get_group (origin_btn);

    xfunc_error_log("o_group: %p\n", o_group);

/************************ menu item initial *************************/

    edit_item = gtk_builder_get_object (build, "edit_menu");

/*********************** drawing area initial *********************/

    d_area = gtk_builder_get_object (build, "UML_canvas");

    drawing_area_initial (d_area);

/*******************  put plugin into main widget **************/
    
    for_each_node_in_single_list (p, plugins) {


        gtk_radio_tool_button_set_group (p->data->btn, o_group);
        
        o_group = gtk_radio_tool_button_get_group(p->data->btn);


        g_signal_connect (GTK_TOGGLE_TOOL_BUTTON(p->data->btn), "toggled",
               G_CALLBACK(plugin_change), p->data->plugin);

        gtk_toolbar_insert (uml_toolbar, p->data->btn, -1);

        if (p->data->menu) { 
            gtk_menu_item_set_submenu (edit_item, GTK_WIDGET(p->data->menu));

            gtk_container_foreach(p->data->menu, menu_connect_canvas, d_area);
        }

        gtk_builder_connect_signals (p->data->builder, NULL);

        g_object_unref (p->data->builder);

    }
               
}

static void load_gui_structure (application_t *app) {
    GtkBuilder         *main_build;



    xfunc_error_log("load gui struct\n");
/*********************** load main widget builder *********************/
    main_build = gtk_builder_new_from_resource ("/main_window.ui");

    app->app = GTK_APPLICATION_WINDOW(
                    gtk_builder_get_object(main_build, "main_window"));

    g_signal_connect (app->app, "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
/******************** link plugins ***************************/
    gui_structure_link_plugins (main_build, app->plugins);

/******************* connect main_wdget signal **************/
    gtk_builder_connect_signals(main_build, NULL);

/********************* destroy main builder ****************/

    g_object_unref (main_build);
}

static void load_css (application_t *app) {
    GtkCssProvider *prov;
    plugin_widgets_unit_t *p = NULL;

    prov = gtk_css_provider_new ();
    gtk_css_provider_load_from_resource (prov, "main_window.css");

    gtk_style_context_add_provider_for_screen (app->scr, 
            GTK_STYLE_PROVIDER(prov), GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref (prov);

    for_each_node_in_single_list (p, app->plugins) {
        prov = gtk_css_provider_new ();

        gtk_css_provider_load_from_resource (prov,
                p->data->plugin->style_path);

        gtk_style_context_add_provider_for_screen (app->scr, 
                GTK_STYLE_PROVIDER(prov), GTK_STYLE_PROVIDER_PRIORITY_USER);

        g_object_unref (prov);
    
    }
    
}

void load_resource (application_t *app) {
    load_gui_structure (app);
    load_css (app);
}

void application_run (application_t *app) {
    gtk_widget_show (app->app);
    gtk_main ();  
}
