cmake_minimum_required(VERSION 3.18)

project (shared_vector VERSION 1.0 LANGUAGES CXX)

add_subdirectory(tests)
add_subdirectory(src)

add_compile_options(-Wall, -Wextra, -Wpedantic, -Werror)