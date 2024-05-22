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

void median_filter(matrix *m, int filter) {
    int temp[filter * filter];
    int half = filter / 2;

    for (int i = half; i < m->nRows - half; i++) {
        for (int j = half; j < m->nCols - half; j++) {
            int k = 0;
            for (int x = i - half; x <= i + half; x++) {
                for (int y = j - half; y <= j + half; y++) {
                    temp[k++] = m->values[x][y];
                }
            }
            for (int p = 0; p < filter * filter - 1; p++) {
                for (int q = 0; q < filter * filter - p - 1; q++) {
                    if (temp[q] > temp[q+1]) {
                        int a = temp[q];
                        temp[q] = temp[q+1];
                        temp[q+1] = a;
                    }
                }
            }
            m->values[i][j] = temp[filter * filter / 2];
        }
    }
}

void tusk3_test1(){
    int arr[] = {10,20,30,25,35,45,15,25,35};
    matrix m = createMatrixFromArray(arr, 3,3);
    median_filter(&m ,3);
    int res_arr[9];
    int size = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            res_arr[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {10,20,30,25,25,45,15,25,35};
    ASSERT_STRING_INT_ARR(expected, 9, res_arr, size)
}
void tusk3_test2(){
    int arr[] = {10,20,30,25,35,45,15,25,35, 20,20,20,20,35,40,5,10,15,35,25,20,30,50,25,10};
    matrix m = createMatrixFromArray(arr, 5,5);
    median_filter(&m ,5);
    int res_arr[25];
    int size = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            res_arr[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {10, 20, 30, 25, 35, 45, 15, 25, 35, 20, 20, 20, 25, 35, 40, 5, 10, 15, 35, 25, 20, 30, 50, 25, 10};
    ASSERT_STRING_INT_ARR(expected, 25, res_arr, size)
}
void tusk3_test3(){
    int arr[] = {10,20,30,25,25,45,15,25,35};
    matrix m = createMatrixFromArray(arr, 3,3);
    median_filter(&m ,3);
    int res_arr[9];
    int size = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            res_arr[size] = m.values[i][j];
            size++;
        }
    }
    int expected[] = {10,20,30,25,25,45,15,25,35};
    ASSERT_STRING_INT_ARR(expected, 9, res_arr, size)
}


//tusk 4................................................................................................................
typedef struct domain_string_value{
    char name[1000];
    int data;
}domain_string_value;
typedef struct array_domain_count{
    int size;
    domain_string_value array[1000];
}array_domain_count;
void add_in_array_domain_count(array_domain_count *bag, domain_string_value domain){
    bool flag_new = true;
    if(bag->size!=0) {
        for (int i = 0; i < bag->size; i++) {
            if (strcmp_(bag->array[i].name, domain.name)) {
                bag->array[i].data += domain.data;
                flag_new = false;
            }
        }
    }
    if(flag_new){
        char *begin = domain.name;
        *copy(begin, begin + strlen_(begin), bag->array[bag->size].name) = '\0';
        bag->array[bag->size].data=domain.data;
        bag->size++;
    }
}
void count_search(char *string, char *res, int *size){
    char *begin = string;
    while (*begin != '\0'){
        if(*begin >= '0' && *begin <='9'){
            res[*size] = *begin;
            (*size)++;
            begin++;
        } else{
            res[*size] = '\0';
            *size += 1;
            return;
        }
    }
}
//main

void count_domain(char (*arr)[100], int size, array_domain_count *bag_domain){
    bag_domain->size=0;
    for(int i = 0; i < size; i++){
        char count_str[100];
        char *begin = arr[i];
        int shift = 0;
        count_search(begin, count_str,&shift);
        int count = atoi(count_str);
        begin += shift;
        while(point_in_string(begin-1)){
            domain_string_value data_domain;
            data_domain.data = count;
            char *copy_in = data_domain.name;
            *copy(begin, begin+ strlen_(begin),copy_in) = '\0';
            add_in_array_domain_count(bag_domain, data_domain);
            begin = find_symbl(begin,'.');
            begin++;
        }
    }
}
void tusk4_test1(){
    array_domain_count bag;
    char arr[][100] = {"9001 discuss.codeforces.com"};
    count_domain(arr, 1, &bag);
    int array_count_got[1000];
    char array_name_got[1000][1000];
    int size_array = 0;
    for(int i = 0; i < bag.size; i++){
        char *begin = bag.array[i].name;
        copy(begin, begin+ strlen_(begin), array_name_got[size_array]);
        array_count_got[size_array] = bag.array[size_array].data;
        size_array++;
    }
    int int_arr_expected[] = {9001,9001,9001};
    char char_arr_expected[][1000] = {"discuss.codeforces.com", "codeforces.com", "com"};
    ASSERT_STRING_INT_ARR_CHAR_ARRAY(int_arr_expected, 3, array_count_got, size_array, 3, char_arr_expected, size_array, array_name_got)
}
void tusk4_test2(){
    array_domain_count bag;
    char arr[][100] = {"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"};
    count_domain(arr, 4, &bag);
    int array_count_got[1000];
    char array_name_got[1000][1000];
    int size_array = 0;
    for(int i = 0; i < bag.size; i++){
        char *begin = bag.array[i].name;
        copy(begin, begin+ strlen_(begin), array_name_got[size_array]);
        array_count_got[size_array] = bag.array[size_array].data;
        size_array++;
    }
    int int_arr_expected[] = {900,901,951,50,1,5,5};
    char char_arr_expected[][1000] = {"google.mail.com", "mail.com", "com", "yahoo.com", "intel.mail.com", "wiki.org", "org"};
    ASSERT_STRING_INT_ARR_CHAR_ARRAY(int_arr_expected, 7, array_count_got, size_array, 7, char_arr_expected, size_array, array_name_got)
}

int countSubmatrices(matrix m) {
    int count = 0;
    int nums[m.nCols];
    for(int i = 0; i < m.nCols; i++){
        nums[i] = 0;
    }
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] == 0) {
                nums[j] = 0;
            } else {
                nums[j] = nums[j]+1;
            }
        }
        for (int j = 0; j < m.nCols; j++) {
            int minVal = nums[j];
            for (int k = j; k < m.nCols; k++) {
                minVal = minVal < nums[k] ? minVal : nums[k];
                count += minVal;
            }
        }
    }
    return count;
}
void tusk5_test1(){
    int arr[] = {1,0,1,1,1,0,1,1,0};
    matrix m = createMatrixFromArray(arr,3,3);
    int res = countSubmatrices(m);
    int expected = 13;
    ASSERT_INT(expected, res)
}
void tusk5_test2(){
    int arr[] = {1,0,0,1,0,1,0,0,1};
    matrix m = createMatrixFromArray(arr,3,3);
    int res = countSubmatrices(m);
    int expected = 6;
    ASSERT_INT(expected, res)
}
void tusk5_test3(){
    int arr[] = {1,0,0,0,0,0,0,0,1};
    matrix m = createMatrixFromArray(arr,3,3);
    int res = countSubmatrices(m);
    int expected = 2;
    ASSERT_INT(expected, res)
}
void testLab20(){
    tusk1_test1();
    tusk1_test2();
    tusk1_test3();
    tusk2_test1();
    tusk2_test2();
    tusk2_test3();
    tusk3_test1();
    tusk3_test2();
    tusk3_test3();
    tusk4_test1();
    tusk4_test2();
    tusk5_test1();
    tusk5_test2();
    tusk5_test3();
}