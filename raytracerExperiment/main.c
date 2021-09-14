#include <gtk/gtk.h>
#include "geometries.h"
#include "raytracer.h"

// todo make a preprocessor for the unittests ?? or use a lib for it
#include "tests/test_vector.h"
#include "tests/test_raytracer.h"

#define BYTES_PER_PIXEL 3



void run_all_tests(){
    printf("Running unittests\n");

    test_cross_product_is_valid();
    test_dot_product_is_valid();

    test_ray_inside_triangle();
    test_ray_outside_triangle();

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

    int white = 255;
    int grey = 128;
    int black = 20;

    int resolutionY = 100;
    int resolutionX = 100;

    //  geometries
    Scene scene = defineScene();

    int sizeArray = resolutionY * resolutionX * BYTES_PER_PIXEL;
    guchar rgbBuffer[sizeArray];
    memset( rgbBuffer, 0, sizeArray*sizeof(guchar) );

//     set all pixels to grey for testing
//    for(size_t i = 0; i <= sizeof(rgbBuffer); i++) {
//        rgbBuffer[i] = white;
//    }


    float filmSizeX = 6;
    float filmSizeY = 6;
    float pixelIncrementX = filmSizeX / (float)resolutionY;
    float pixelIncrementY = filmSizeY / (float)resolutionX;

    // defining a triangle that is in the sight of the ray
    Face f1;

    f1.normal.x = -1;
    f1.normal.y = 0;
    f1.normal.z = 0;

    f1.v0.x = 2;
    f1.v0.y = 2;
    f1.v0.z = 0;

    f1.v1.x = 2;
    f1.v1.y = -1;
    f1.v1.z = -1;

    f1.v2.x = 2;
    f1.v2.y = -1;
    f1.v2.z = 1;


    // this is first a test with planar projection
    Ray ray;
    ray.direction.x = 1;
    ray.direction.y = 0;
    ray.direction.z = 0;

    int buffer[sizeArray];

    int i = 0;
    for(int x = 0; x <= resolutionY; x++) {
        for(int y = 0; y <= resolutionX; y++) {

            ray.origin.x = (float)x + pixelIncrementX - filmSizeX/2;
            ray.origin.y = (float)y + pixelIncrementY - filmSizeY/2;

            bool intersected = isRayIntersectsTriangle( ray, f1);
            if (intersected) {
                buffer[i] = 255;
                buffer[i+1] = 255;
                buffer[i+2] = 255;

            } else{
                buffer[i] = 128;
                buffer[i+1] = 128;
                buffer[i+2] = 128;
            }

           i+=3;
        }
    }

    // todo bug with the representation of the buffer
    for(size_t j = 0; j <= sizeof(rgbBuffer); j++) {
        rgbBuffer[j] = buffer[j];
    }

    // VIEW
    // todo put the view in another file  -> bug with passing the guchar array to the function
    gtk_init(&argc, &argv);

    GdkPixbuf *pb = gdk_pixbuf_new_from_data(
            rgbBuffer,
            GDK_COLORSPACE_RGB,     // colorspace (must be RGB)
            0,                      // has_alpha (0 for no alpha)
            8,                      // bits-per-sample (must be 8)
            resolutionX, resolutionY,             // cols, rows
            resolutionX * BYTES_PER_PIXEL, // rowstride
            NULL, NULL              // destroy_fn, destroy_fn_data
    );
    GtkWidget *image = gtk_image_new_from_pixbuf(pb);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Image");
    gtk_window_set_default_size(GTK_WINDOW(window), resolutionX + 20, resolutionY + 20);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(window), image);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}