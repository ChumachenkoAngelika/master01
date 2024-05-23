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


void end_pattern_numb(const char *pattern, int cur, int *arr, int *bin_arr,bool *flag_end){

    for (int i = 1; i <= 9; i++) {
        if(cur == strlen_(pattern)){
            *flag_end = true;
            return;
        }
        if (bin_arr[i - 1] == 1) {
            arr[cur+1] = i;
            bin_arr[i - 1] = 0;
            if (pattern[cur] == 'I' && arr[cur] < arr[cur+1]) {
                end_pattern_numb(pattern, cur + 1, arr, bin_arr,flag_end);
                if(sumOfValueArray(bin_arr, 9) == 0){
                    *flag_end = true;
                    return;
                }
            }
            else if (pattern[cur] == 'D' && arr[cur] > arr[cur+ 1]) {
                end_pattern_numb(pattern, cur + 1, arr, bin_arr, flag_end);
                if(sumOfValueArray(bin_arr, 9) == 0){
                    *flag_end = true;
                    return;
                }
            }
            if(*flag_end){
                return;
            }
            bin_arr[i - 1] = 1;

        }
    }

}
void start_pattern_numb(const char *pattern, int cur, int *arr, int *bin_arr, bool *flag_end) {
    for (int i = 1; i < 10; i++) {
        arr[cur] = i;
        bin_arr[i - 1] = 0;
        end_pattern_numb(pattern, cur, arr, bin_arr, flag_end);
        if(*flag_end){
            return;
        }
        bin_arr[i - 1] = 1;
    }
}


void tusk6_test1(){
    char *pattern = "IIIDIDDD";
    int size = strlen_(pattern)+1;
    int arr[9] = {0};
    int bin_arr[9] = {1,1,1,1,1,1,1,1,1};
    bool flag = false;
    start_pattern_numb(pattern, 0, arr,bin_arr, &flag);
    int got_arr[size];
    for(int i = 0; i < size; i++){
        got_arr[i] = arr[i];
    }
    int expected[] = {1,2,3,5,4,9,8,7,6};
    ASSERT_STRING_INT_ARR(expected, 9, got_arr,size)
}
void tusk6_test2(){
    char *pattern = "DDD";
    int size = strlen_(pattern)+1;
    int arr[9] = {0};
    int bin_arr[9] = {1,1,1,1,1,1,1,1,1};
    bool flag = false;
    start_pattern_numb(pattern, 0, arr,bin_arr, &flag);
    int got_arr[size];
    for(int i = 0; i < size; i++){
        got_arr[i] = arr[i];
    }
    int expected[] = {4,3,2,1};
    ASSERT_STRING_INT_ARR(expected, 4, got_arr,size)
}
void tusk6_test3(){
    char *pattern = "DDDI";
    int size = strlen_(pattern)+1;
    int arr[9] = {0};
    int bin_arr[9] = {1,1,1,1,1,1,1,1,1};
    bool flag = false;
    int got_arr[size];
    start_pattern_numb(pattern, 0, arr,bin_arr, &flag);
    for(int i = 0; i < size; i++){
        got_arr[i] = arr[i];
    }
    int expected[] = {4,3,2,1,5};
    ASSERT_STRING_INT_ARR(expected, 5, got_arr,size)
}


typedef struct list{
    int data;
    struct list *left;
    struct list *right;
    int neighbour;
}list;
list *creat_list(int data){
    list *node = malloc(sizeof(list));
    node->data = data;
    node->neighbour=0;
    return node;
}
list *push_list(int data, int flag, list *node){
    node->data = data;
    list *temp = creat_list(0);
    if(flag == 0){
        node->left = temp;
        if(node->neighbour == 0){
            node->neighbour = 1;
        } else{
            node->neighbour = 3;
        }
    } else{
        node->right = temp;
        if(node->neighbour == 0){
            node->neighbour = 2;
        } else{
            node->neighbour = 3;
        }
    }
    return temp;
}
int find_indx_maxValue_border(int *arr, int border_left, int border_right){
    int max_value = INT_MIN;
    int indx;
    for(int i = border_left; i < border_right; i++){
        if(max_value < arr[i]){
            max_value = arr[i];
            indx = i;
        }
    }
    return indx;
}
void trees(int *arr, int border_left, int border_right, list *tree, int max_size_arr){
    if(border_right == border_left) {
        return;
    }
    int max_index = find_indx_maxValue_border(arr, border_left,border_right);
    if(max_index != border_left) {
        trees(arr, border_left, max_index, push_list(arr[max_index], 0, tree),max_size_arr);
        if(border_right - border_left == 1)
            tree->neighbour=0;
    }
    if(max_index != border_right && max_index+1 != max_size_arr ||  border_right-border_left==1) {
        trees(arr, max_index + 1, border_right, push_list(arr[max_index], 1, tree),max_size_arr);
        if(border_right - border_left == 1)
            tree->neighbour=0;
    }
}
void BFS_list(list *tree[1000], int size, int *arr_res, int  *res_size){
    int temp_size = 0;
    list *tempArr[1000];
    for(int i = 0; i < size; i++){
        arr_res[*res_size] = tree[i]->data;
        (*res_size)++;
        if(tree[i]->neighbour == 1){
            tempArr[temp_size] = tree[i]->left;
            temp_size++;
        }
        if(tree[i]->neighbour == 2){
            tempArr[temp_size] = tree[i]->right;
            temp_size++;
        }
        if(tree[i]->neighbour == 3){
            tempArr[temp_size] = tree[i]->left;
            temp_size++;
            tempArr[temp_size] = tree[i]->right;
            temp_size++;
        }
        tree[i]->neighbour=0;
        if(size>1)
            free(tree[i]);
        if(size == 1)
            tree[0]->neighbour=0;

    }
    if(temp_size == 0)
        return;
    BFS_list(tempArr, temp_size, arr_res, res_size);

}
void tusk7_test1(){
    int arr[] = {3,2,1,6,0,5};
    list *main_list = creat_list(0);
    trees(arr, 0, 6,main_list, 6);
    list *arrRes[1000] = {main_list};
    int arr_res[1000];
    int arr_size =0;
    BFS_list(arrRes, 1, arr_res, &arr_size);
    free(main_list);
    int expected[] = {6,3,5,2,0,1};
    ASSERT_STRING_INT_ARR(expected, 6, arr_res, arr_size)
}
void tusk7_test2(){
    int arr[] = {3,2,1};
    list *main_list = creat_list(0);
    trees(arr, 0, 3,main_list, 3);
    list *arrRes[1000] = {main_list};
    int arr_res[1000];
    int arr_size =0;
    BFS_list(arrRes, 1, arr_res, &arr_size);
    free(main_list);
    int expected[] = {3,2,1};
    ASSERT_STRING_INT_ARR(expected, 3, arr_res, arr_size)
}
void tusk7_test3(){
    int arr[] = {3,0,2,1};
    list *main_list = creat_list(0);
    trees(arr, 0, 4,main_list, 4);
    list *arrRes[1000] = {main_list};
    int arr_res[1000];
    int arr_size =0;
    BFS_list(arrRes, 1, arr_res, &arr_size);
    free(main_list);
    int expected[] = {3,2,0,1};
    ASSERT_STRING_INT_ARR(expected, 4, arr_res, arr_size)
}


void change_letters(int *arr, char *s){
    int size_s = strlen_(s);
    char temp_string[size_s+1];
    for(int i = 0; i < size_s; i++){
        *(temp_string+arr[i]) = *(s+i);
    }
    for (int i = 0; i < size_s; i++) {
        *(s+i )= *(temp_string+i);
    }
}

void tusk8_test1(){
    int arr[] = {0,1,2};
    char s[] = "abc";
    change_letters(arr,s);
    char expected[] = "abc";
    ASSERT_STRING(expected, s)
}
void tusk8_test2(){
    int arr[] = {0,3,2,1};
    char s[] = "abap";
    change_letters(arr,s);
    char expected[] = "apab";
    ASSERT_STRING(expected, s)
}
void tusk8_test3(){
    int arr[] = {5,4,3,2,1,0};
    char s[] = "zxcvbn";
    change_letters(arr,s);
    char expected[] = "nbvcxz";
    ASSERT_STRING(expected, s)
}


void make_file(FILE *f, int N){
    FILE *res = fopen("res.txt", "w");
    while (feof(f) == 0){
        int value;
        if(fscanf(f,"%d",&value) != 0){
            if(value < N)
                fprintf(res, "%d ", value);
        }
    }
    fclose(res);
}

char *find_suffix(char *s){
    char *dot = find_symbl(s, '.');
    if(*dot == '\0')
        return NULL;
    return dot;
}

void tusk9_test1(){
    int N;
    char name[64];
    scanf("%s", name);
    char *suffix = find_suffix(name);
    if(find_suffix(name) == NULL || !strcmp_(suffix, ".txt")){
        fprintf(stderr, "add to file suffix: .txt");
        exit(1);
    }

    if(scanf("%d", &N) == 1){
        FILE *f = fopen(name, "w+");
        if(f==NULL){
            fprintf(stderr, "Fail");
            exit(1);
        }
        for(int i = 0; i < 25; i++){
            fprintf(f, "%d ", i);
        }
        fseek(f, 0L, 0);
        make_file(f, N);
        fclose(f);
        remove(name);
    } else{
        fprintf(stderr, "not a number entered");
    }
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
    tusk6_test1();
    tusk6_test2();
    tusk6_test3();
    tusk7_test1();
    tusk7_test2();
    tusk7_test3();
    tusk8_test1();
    tusk8_test2();
    tusk8_test3();
    tusk9_test1();
}