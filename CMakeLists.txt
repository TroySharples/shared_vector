cmake_minimum_required(VERSION 3.18)

set(PROJECT_NAME "shared_vector")
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    include(CTest)
    add_subdirectory(tests)
endif()
