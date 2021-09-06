cmake_minimum_required(VERSION 3.1)

project(raytracerExperiment C)

set(CMAKE_C_STANDARD 11)

include_directories(raytracerExperiment)

# Find dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

link_directories(${GTK3_LIBRARY_DIRS})
add_compile_options(${GTK3_CFLAGS_OTHER})
set(LIBRARIES ${LIBRARIES} ${GTK3_LIBRARIES})

set(FLAGS "-I${GTK3_INCLUDE_DIRS}")
message(STATUS "Flags: ${FLAGS}")
string(REPLACE ";" " -I" FLAGS "${FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GTK3_FLAGS} ${FLAGS})

add_executable(raytracerExperiment
        raytracerExperiment/main.c)

add_definitions (${GTK3_CFLAGS_OTHER})
target_link_libraries (raytracerExperiment ${GTK3_LIBRARIES})