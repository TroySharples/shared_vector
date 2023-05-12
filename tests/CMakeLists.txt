include(GoogleTest)

add_executable(shared_vector_test shared_vector_test.cpp)
target_link_libraries(shared_vector_test PRIVATE shared-vector gtest pthread)

add_test(shared_vector_test shared_vector_test)