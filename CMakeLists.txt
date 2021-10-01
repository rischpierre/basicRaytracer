cmake_minimum_required(VERSION 3.1)

project(raytracerExperiment C)

set(CMAKE_C_STANDARD 11)

include_directories(raytracerExperiment)

message(STATUS "Flags: ${FLAGS}")
string(REPLACE ";" " -I" FLAGS "${FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GTK3_FLAGS} ${FLAGS})


file(GLOB SOURCES
        "src/*.h"
        "src/*.c"
        )

file(GLOB ALL_SOURCES
        "src/tests/*.c"
        "src/*.c"
        "src/*.h"
        )
list(FILTER ALL_SOURCES EXCLUDE REGEX "src/main.c")

add_executable(raytracerExperiment ${SOURCES})
add_executable(raytracerExperimentTests ${ALL_SOURCES})


# add math library
target_link_libraries(raytracerExperiment m)

# testing lib
# todo use git submodules to install criterion  dynamically
find_library(CRITERION_LIBS NAMES libcriterion*)
target_link_libraries(raytracerExperimentTests m)
target_link_libraries(raytracerExperimentTests ${CRITERION_LIBS})