#include <gtk/gtk.h>
#include <stdio.h>

#define MAINWINDOW_XML_PATH "gui_form.glade"
#define MAINWINDOW_CSS_PATH "gui_form.css"


void on_window_destory () {
    gtk_main_quit ();
}

void tool_state_change(GtkToggleToolButton *ttb, gpointer user_data) {
    printf ("button %s: ", gtk_tool_button_get_label (ttb));
    if (gtk_toggle_tool_button_get_active(ttb)) {
        puts ("active");
    } else
        puts("inactive");
}

int main (int argc, char *argv[]) {
    GdkScreen       *screen;
    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkCssProvider  *css_prov;
    GtkStyleContext *gsc;

    gtk_init (&argc, &argv);
    screen = gdk_screen_get_default();

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, MAINWINDOW_XML_PATH, NULL);

    css_prov = gtk_css_provider_get_default();
    gtk_css_provider_load_from_path (css_prov, MAINWINDOW_CSS_PATH, NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
    

    gtk_style_context_add_provider_for_screen (screen, css_prov,
            GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_reset_style (window);

    gtk_builder_connect_signals (builder, NULL);

    g_object_unref (G_OBJECT (builder));

    gtk_widget_show (window);
    gtk_main();

    return 0;
}
