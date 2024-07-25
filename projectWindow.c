#include <gtk/gtk.h>

// Callback function to handle window destruction
void on_destroy(GtkWidget *widget, gpointer data) {
    gtk_window_close(GTK_WINDOW(widget));
}

int main(int argc, char *argv[]) {
    // Initialize GTK application
    GtkApplication *app = gtk_application_new("com.example.novus", G_APPLICATION_DEFAULT_FLAGS);

    // Create a new window
    GtkWidget *window = gtk_application_window_new(app);

    // Connect the destroy signal to the callback function
    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

    // Set the default window size
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);

    // Set the window to be maximized by default
    gtk_window_maximize(GTK_WINDOW(window));

    // Create a CSS provider and load CSS
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider, "* { background-color: #8C8A8A; }", -1, NULL);

    // Create a style context and add the CSS provider to it
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Show the window
    gtk_widget_show_all(window);

    // Start the main loop
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Clean up
    g_object_unref(css_provider);
    g_object_unref(app);

    return status;
}
