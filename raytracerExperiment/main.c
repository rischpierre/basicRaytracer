#include <gtk/gtk.h>

#define ROWS 600
#define COLS 600
#define BYTES_PER_PIXEL 3

void bw_to_rgb(guchar *rgb, guchar *bw, size_t sz) {
    for (size_t i = 0; i < sz; i++)
        for (size_t j = 0; j < BYTES_PER_PIXEL; j++)
            rgb[i * BYTES_PER_PIXEL + j] = bw[i];
}

int main(int argc, char **argv) {

    // grayscale data array
    guchar bw[ROWS * COLS] = { 0 }; // start all black

    // draw a design
    for (int color = 0, i = 20; i < ROWS; i += 20) {
        color = (color == 0) ? 255 : 0;
        for (int r = i; r < ROWS - i; r++)
            for (int c = i; c < COLS - i; c++)
                bw[r * COLS + c] = color;
    }

    // convert to rgb (by tripling the values)
    guchar rgb[sizeof bw * BYTES_PER_PIXEL];
    bw_to_rgb(rgb, bw, ROWS * COLS);

    gtk_init(&argc, &argv);

    GdkPixbuf *pb = gdk_pixbuf_new_from_data(
            rgb,
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