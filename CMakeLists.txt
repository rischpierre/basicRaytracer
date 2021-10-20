cmake_minimum_required(VERSION 3.1)

project(raytracerExperiment C)

set(CMAKE_C_STANDARD 11)

include_directories(raytracerExperiment)

string(REPLACE ";" " -I" FLAGS "${FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GTK3_FLAGS} ${FLAGS})


file(GLOB SOURCES "src/*.h" "src/*.c")

add_subdirectory(tests)

add_executable(raytracerExperiment ${SOURCES})


# add math library
target_link_libraries(raytracerExperiment m)
