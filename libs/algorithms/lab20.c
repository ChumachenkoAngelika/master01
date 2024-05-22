//
// Created by admin on 07.05.2024.
//
#include <stdio.h>
#include "array.h"
#include "../data_struct/matrix/matrix.h"
#include "../data_struct/string/tusk/test_processing_string.h"
#include "../data_struct/string/processing_string.h"
#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__);
#define ASSERT_STRING_INT_ARR(expected, size_expected, got, size_got) assertStringIntArr(expected, size_expected, got, size_got, __FILE__, __FUNCTION__, __LINE__);
#define ASSERT_STRING_INT_ARR_CHAR_ARRAY(expectedInt, size_expectedInt, gotInt, size_gotInt, size_expecded_charArray, charArray_expected, size_got_charArray, charArray_got) assertStringIntArrAndStrArr(expectedInt, size_expectedInt, gotInt, size_gotInt, size_expecded_charArray, charArray_expected, size_got_charArray, charArray_got, __FILE__, __FUNCTION__, __LINE__);
#define ASSERT_INT(expected, got) assertInt(expected, got, __FILE__, __FUNCTION__, __LINE__);

//tusk 1................................................................................................................
typedef struct matrix_point{
    int begig_x;
    int begig_y;
    int end_x;
    int end_y;
}matrix_point;
void submatrix(matrix m, int arr[][4], int size){
    matrix_point submatrix;
    for(int k = 0; k < size; k++){
        submatrix.begig_x = arr[k][0];
        submatrix.begig_y = arr[k][1];
        submatrix.end_x = arr[k][2];
        submatrix.end_y = arr[k][3];
        for(int i = submatrix.begig_x; i <= submatrix.end_x; i++){
            for(int j = submatrix.begig_y; j <= submatrix.end_y; j++){
                m.values[i][j]++;
            }
        }
    }
}
void tusk1_test1(){
    int matrix_arr[] = {0,0,0,0,0,0,0,0,0};
    matrix m = createMatrixFromArray(matrix_arr,3,3);
    int submatrix_arr[2][4] = {{1,1,2,2}, {0,0,1,1}};
    submatrix(m, submatrix_arr,2);
    int arr_res[m.nCols*m.nRows];
    int size = 0;
    for(int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            arr_res[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {1,1,0,1,2,1,0,1,1};
    ASSERT_STRING_INT_ARR(expected,9,arr_res,size)
    freeMemMatrix(&m);
}
void tusk1_test2(){
    int matrix_arr[] = {0,0,0,0,0,0,0,0,0};
    matrix m = createMatrixFromArray(matrix_arr,3,3);
    int submatrix_arr[3][4] = {{1,1,2,2}, {0,0,1,1}, {1,0,2,1}};
    submatrix(m, submatrix_arr,3);
    int arr_res[m.nCols*m.nRows];
    int size = 0;
    for(int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            arr_res[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {1,1,0,2,3,1,1,2,1};
    ASSERT_STRING_INT_ARR(expected,9,arr_res,size)
    freeMemMatrix(&m);
}
void tusk1_test3(){
    int matrix_arr[] = {0,0,0,0,0,0,0,0,0};
    matrix m = createMatrixFromArray(matrix_arr,3,3);
    int submatrix_arr[6][4] = {{1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1},{1,1,1,1}, {1,1,1,1}};
    submatrix(m, submatrix_arr,6);
    int arr_res[m.nCols*m.nRows];
    int size = 0;
    for(int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            arr_res[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {0,0,0,0,6,0,0,0,0};
    ASSERT_STRING_INT_ARR(expected,9,arr_res,size)
    freeMemMatrix(&m);
}


void testLab20(){
    tusk1_test1();
    tusk1_test2();
    tusk1_test3();


}