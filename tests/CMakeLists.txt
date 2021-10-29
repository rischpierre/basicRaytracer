# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
file(GLOB TESTS_SOURCES "*.cpp" )

add_executable(Google_Tests_run ${TESTS_SOURCES})

# add warnings
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

file(GLOB ALL_SOURCES
        "../src/*.c"
        "../src/*.h"
        )
list(FILTER ALL_SOURCES EXCLUDE REGEX "src/main.c")

target_link_libraries(Google_Tests_run ${ALL_SOURCES})

target_link_libraries(Google_Tests_run gtest gtest_main)
