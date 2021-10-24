#include "geometries.h"
#include "raytracer.h"
#include "ioLib.h"

Scene defineExampleScene() {

    Camera camera = {
            .focalPoint={0, 0, 0},
            .direction={1, 0, 0},
    };

    // light on the right side
    DirLight light = {.direction={0, 1, 0}};

    Scene scene;
    scene.camera = camera;
    scene.light = light;

    return scene;
}

int main(int argc, char *argv[]) {
    Scene scene = defineExampleScene();
    parseObjFile(&scene, "../examples/twoTriangle.obj");

    render(&scene);

    return 0;
}