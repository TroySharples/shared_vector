add_library(shared-vector INTERFACE)
target_include_directories(shared-vector INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(shared-vector INTERFACE cxx_std_20)