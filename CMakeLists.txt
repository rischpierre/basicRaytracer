cmake_minimum_required(VERSION 3.1)

project(basicRaytracer C)

set(CMAKE_C_STANDARD 11)

include_directories(basicRaytracer)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

file(GLOB SOURCES "src/*.h" "src/*.c" "examples/*.h")

add_subdirectory(tests)

add_executable(basicRaytracer ${SOURCES})

target_link_libraries(basicRaytracer pthread m)
