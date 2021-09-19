cmake_minimum_required(VERSION 3.1)

project(raytracerExperiment C)

set(CMAKE_C_STANDARD 11)

include_directories(raytracerExperiment)

set(FLAGS "-I${GTK3_INCLUDE_DIRS}")
message(STATUS "Flags: ${FLAGS}")
string(REPLACE ";" " -I" FLAGS "${FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GTK3_FLAGS} ${FLAGS})


file(GLOB SOURCES
        "src/*.h"
        "src/*.c"
        )

file(GLOB TEST_SOURCES
        "src/tests/*.c"
        )


add_executable(raytracerExperiment ${SOURCES})
add_executable(raytracerExperimentTests ${TEST_SOURCES})


# todo
enable_testing()
add_test(Tests raytracerExperimentTests)