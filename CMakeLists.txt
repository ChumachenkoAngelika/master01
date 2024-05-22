cmake_minimum_required(VERSION 3.27)
project(Project17 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project17 main.c
        libs/algorithms/array.c
        libs/data_struct/bitset/bitset.c
        libs/data_struct/matrix/matrix.h
        libs/data_struct/matrix/matrix.c
        libs/data_struct/ordered_array/ordered_array.c
        libs/data_struct/string/string_.c
        libs/data_struct/unordered_array/unordered_array.c
        libs/data_struct/vector/vector.c
        libs/data_struct/vector_void/vectorVoid.h
        libs/data_struct/vector_void/vectorVoid.c
        libs/data_struct/string/tusk/test.c
        libs/data_struct/string/tusk/test_processing_string.c
        libs/data_struct/string/tusk/test_processing_string.h
        libs/data_struct/string/processing_string.h
        libs/data_struct/string/processing_string.c
        libs/algorithms/lab19.c
        libs/algorithms/lab20.c
)
