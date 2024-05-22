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
//tusk 2................................................................................................................
void game_life(matrix *m){
    matrix temp_matrix = getMemMatrix(m->nRows,m->nCols);
    for(int i = 0; i < m->nRows; i++){
        for(int j = 0; j < m->nCols; j++){
            temp_matrix.values[i][j] = 0;
            int count_numb_one = 0;
            for(int indx_y = i - 1; indx_y <= i + 1; indx_y++){
                for(int indx_x = j - 1; indx_x <= j + 1; indx_x++){
                    if(indx_y >= 0 && indx_y < m->nRows && indx_x >= 0 && indx_x < m->nCols){
                        count_numb_one+=m->values[indx_y][indx_x];
                    }
                }
            }
            if(m->values[i][j] == 1 && (count_numb_one == 3 || count_numb_one == 4)){
                temp_matrix.values[i][j] = 1;
            }
            if(m->values[i][j] == 0 && count_numb_one == 3){
                temp_matrix.values[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < m->nRows; i++){
        for(int j = 0; j < m->nCols; j++){
            m->values[i][j] = temp_matrix.values[i][j];
        }
    }
    freeMemMatrix(&temp_matrix);
}
void tusk2_test1(){
    int arr[] = {0,1,0,1,1,0,1,0,0};
    matrix m = createMatrixFromArray(arr, 3,3);
    game_life(&m);
    int res[m.nCols*m.nRows];
    int size = 0;
    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            res[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {1,1,0,1,1,0,1,1,0};
    ASSERT_STRING_INT_ARR(expected,9,res,size)
    freeMemMatrix(&m);
}
void tusk2_test2(){
    int arr[] = {0,1,0,0,0,1,1,1,1,0,0,0};
    matrix m = createMatrixFromArray(arr, 4,3);
    game_life(&m);
    int res[m.nCols*m.nRows];
    int size = 0;
    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            res[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {0,0,0,1,0,1,0,1,1,0,1,0};
    ASSERT_STRING_INT_ARR(expected,12,res,size)
    freeMemMatrix(&m);
}
void tusk2_test3(){
    int arr[] = {1,1,};
    matrix m = createMatrixFromArray(arr, 2,1);
    game_life(&m);
    int res[m.nCols*m.nRows];
    int size = 0;
    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            res[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {0,0};
    ASSERT_STRING_INT_ARR(expected,2,res,size)
    freeMemMatrix(&m);
}


void testLab20(){
    tusk1_test1();
    tusk1_test2();
    tusk1_test3();
    tusk2_test1();
    tusk2_test2();
    tusk2_test3();

}