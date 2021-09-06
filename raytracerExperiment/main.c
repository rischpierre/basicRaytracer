#include <gtk/gtk.h>

#define ROWS 300
#define COLS 600
#define BYTES_PER_PIXEL 3


int main(int argc, char **argv) {

    guchar rgbBuffer[ROWS * COLS * BYTES_PER_PIXEL] = {0};

    // set all pixels to grey
    for(size_t i = 0; i <= sizeof(rgbBuffer); i++) {
        rgbBuffer[i] = 128;
    }

    gtk_init(&argc, &argv);

    GdkPixbuf *pb = gdk_pixbuf_new_from_data(
            rgbBuffer,
            GDK_COLORSPACE_RGB,     // colorspace (must be RGB)
            0,                      // has_alpha (0 for no alpha)
            8,                      // bits-per-sample (must be 8)
            COLS, ROWS,             // cols, rows
            COLS * BYTES_PER_PIXEL, // rowstride
            NULL, NULL              // destroy_fn, destroy_fn_data
    );
    GtkWidget *image = gtk_image_new_from_pixbuf(pb);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Image");
    gtk_window_set_default_size(GTK_WINDOW(window), COLS+20, ROWS+20);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(window), image);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}