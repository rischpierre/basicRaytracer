#include <gtk/gtk.h>
#include "test_vector.h"
#include "geometries.h"

#define ROWS 300
#define COLS 600
#define BYTES_PER_PIXEL 3



void run_all_tests(){
    printf("Running unittests\n");
    test_cross_product_is_valid();
    test_dot_product_is_valid();
    printf("End unittests\n");
}

// todo first start make a 2d projection of the created face, need to

Scene defineScene(){

    // lets design a flat scene  along x, y

    Face f1;

    f1.v0.x = 10;
    f1.v0.y = 0;
    f1.v0.z = 0;

    f1.v1.x = 10;
    f1.v1.y = 1;
    f1.v1.z = 0;

    f1.v2.x = 10;
    f1.v2.y = 0;
    f1.v2.z = 1;

    Camera camera;

    camera.focalPoint.x = 0;
    camera.focalPoint.y = 0;
    camera.focalPoint.z = 0;

    camera.direction.x = 10;
    camera.direction.y = 1;
    camera.direction.z = 0;

    Scene scene;
    scene.camera = camera;
    scene.face = f1;

    return scene;
}


int main(int argc, char *argv[]) {

    // run tests if -t is in the args
    for (int i=0; i < argc; i++) {

        if(strcmp(argv[i], "-t") == 0) {
            run_all_tests();
            return 0;
        }
    }

    //  geometries
    Scene scene = defineScene();

    guchar rgbBuffer[ROWS * COLS * BYTES_PER_PIXEL] = {0};

    // set all pixels to grey
//    for(size_t i = 0; i <= sizeof(rgbBuffer); i++) {
//        rgbBuffer[i] = 128;
//    }

    double filmSizeX = 6;
    double filmSizeY = 3;
    double pixelIncrementX = ROWS / filmSizeX;
    double pixelIncrementY = COLS / filmSizeY;

    Ray ray;

    for(int x = 0; x <= ROWS; x++) {
        for(int y = 0; x <= COLS; x++) {
            ray.v.x = 1;
            ray.v.y = 0;
            ray.v.z = 0;
            ray.p.x = x + pixelIncrementX;
            ray.p.y = y + pixelIncrementY;

            bool intersected = intersectRayTriangle( ray, triangle);

            if intersected{
                // todo need to have a double array
            }
        }
        }



    // VIEW
    // todo put the view in another file  -> bug with passing the guchar array to the function
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