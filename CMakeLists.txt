cmake_minimum_required(VERSION 3.1)

project(raytracerExperiment C)

set(CMAKE_C_STANDARD 11)

include_directories(raytracerExperiment)

set(FLAGS "-I${GTK3_INCLUDE_DIRS}")
message(STATUS "Flags: ${FLAGS}")
string(REPLACE ";" " -I" FLAGS "${FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GTK3_FLAGS} ${FLAGS})

add_executable(raytracerExperiment
        src/main.c src/vector.c src/vector.h src/geometries.c src/geometries.h src/tests/test_vector.c src/tests/test_vector.c src/tests/test_vector.h src/raytracer.c src/raytracer.h src/tests/test_raytracer.c src/tests/test_raytracer.h src/utils.c src/utils.h)