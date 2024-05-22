//
// Created by admin on 23.04.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io.h"
#include "../data_struct/matrix/matrix.h"
#include "../data_struct/string/string_.h"
#include "../data_struct/string/processing_string.h"
#include "../data_struct/string/tusk/test_processing_string.h"
#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__);
#define ASSERT_STRING_INT_ARR(expected, size_expected, got, size_got) assertStringIntArr(expected, size_expected, got, size_got, __FILE__, __FUNCTION__, __LINE__);
//tusk1
void toColFromRow(FILE *file){
    char n_arr[100];
    fgets(n_arr, 100, file);
    char tempNumb[100];
    copy(n_arr, find(n_arr, n_arr+100, '\n')+1,tempNumb);
    replace(n_arr, "\n", "\0");
    int n = atoi(n_arr);
    int values[1000];
    int size = 0;
    while (feof(file)==0){
        const char numb = (char)fgetc(file);
        if(numb>='0' && numb <='9'){
            values[size] = atoi(&numb);
            size++;
        }
    }
    matrix matrix = createMatrixFromArray(values, n, size/n);
    transposeMatrix(&matrix);
    char result[size];
    int size_res = 0;
    for(int i = 0; i < size/n; i++){
        for(int j = 0; j < n; j++){
            result[size_res] = (char)(matrix.values[i][j] + 48);
            size_res++;
        }
        result[size_res] = '\n';
        size_res++;
    }
    fseek(file, 0l, 0);
    fputs(tempNumb, file);
    fputs(result, file);
}

void test1_tusk1(){
    char s[1000] = "4\n123456789\n963852741\n159236478\n951632874";
    FILE *file = fopen("my_file.txt", "w+");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,file);
    fseek(file,0l,0);
    toColFromRow(file);
    fclose(file);
    file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("4\n1919\n2655\n3391\n4826\n5533\n6262\n7748\n8477\n9184\n",res)
    remove("my_file.txt");
}
void test2_tusk1(){
    char s[1000] = "5\n951632874\n789420000\n556236985\n123456789\n333333333";
    FILE *file = fopen("my_file.txt", "w+");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,file);
    fseek(file,0l,0);
    toColFromRow(file);
    fclose(file);
    file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("5\n97513\n58523\n19633\n64243\n32353\n20663\n80973\n70883\n40593\n",res)
    remove("my_file.txt");
}
void test3_tusk1(){
    char s[1000] = "2\n951632874\n951632874";
    FILE *file = fopen("my_file.txt", "w+");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,file);
    fseek(file,0l,0);
    toColFromRow(file);
    fclose(file);
    file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("2\n99\n55\n11\n66\n33\n22\n88\n77\n44\n",res)
    remove("my_file.txt");
}
//tusk 2,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
void Float_values(FILE *file){
    char values[1000];
    char arr_res[1000][1000];
    int size = 0;
    while(feof(file) == 0){
        if(fgets(values,1000, file)!=0) {
            *findSpaceReverse(values + strlen_(values) - 1, values) == '\n' ? *findSpaceReverse(
                    values + strlen_(values) - 1, values) = '\0' : *findSpaceReverse(values + strlen_(values) - 1,
                                                                                     values);
            char *point = find_symbl(values, '.');
            if (*point == '\0') {
                *point = '.';
                *(point + 1) = '0';
                *(point + 2) = '0';
                *(point + 3) = '\n';
                *(point + 4) = '\0';
            } else if (*point == '.' && *(point + 2) == '\0') {
                *(point + 2) = '0';
                *(point + 3) = '\n';
                *(point + 4) = '\0';
            } else {
                *(point + 3) = '\n';
                *(point + 4) = '\0';
            }
            *copy(values, strlen_(values)+values, arr_res[size]) = '\0';
            size++;
        }
    }
    fseek(file, 0L, 0);

    for(int i = 0; i < size; i++){
        char str[1000] = {0};
        char *begin = str;
        *copy(arr_res[i], arr_res[i]+ strlen_(arr_res[i]), begin) = '\0';
        fputs(str, file);
    }
    chsize(fileno(file), ftell(file));
}

void test1_tusk2(){
    char s[1000] = "159236478\n951632874\n323232.2535";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f,0L,0);
    Float_values(f);
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("159236478.00\n951632874.00\n323232.25\n",res)
    remove("my_file.txt");
}
void test2_tusk2(){
    char s[1000] = "159236478.1\n95.1632874\n323232";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f,0L,0);
    Float_values(f);
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("159236478.10\n95.16\n323232.00\n",res)
    remove("my_file.txt");
}

//tusk 3................................................................................................................
int doSolve(char s, int a, int b){
    if(s == '+')
        return a+b;
    else if(s == '-')
        return a-b;
    else if(s == '*')
        return a*b;
    else if(s == '/')
        return a/b;
    else if(s == '%')
        return a%b;
    fprintf(stderr, "Fail");
    return 0;
}

void arithmetic_solve(FILE *file){
    char data[10];
    fgets(data, 9, file);
    int a, b, c;
    a = atoi(&data[0]);
    b = atoi(&data[2]);
    c = atoi(&data[4]);
    int res = doSolve(data[1],a,b);
    res = doSolve(data[3], res, c);
    fputs("\n", file);
    char ans[4];
    char *begin = ans;
    if(0<=res && res <= 9){
        ans[0] = (char)(res + 48);
        *(begin+1) = '\0';
    }
    if(10<=res && res <= 99){
        ans[0] = (char)((res)/10 + 48);
        ans[1] = (char)((res)%10 + 48);
        *(begin+2) = '\0';
    }
    if(100<=res && res <= 729){
        ans[0] = (char)((res)/100 + 48);
        ans[1] = (char)((res/10)%10 + 48);
        ans[2] = (char)((res)%10 + 48);
        *(begin+3) = '\0';
    }
    if(0>res && res >= -9){
        res*=-1;
        ans[0] = '-';
        ans[1] = (char)(res + 48);
        *(begin+2) = '\0';
    }
    if(-10>=res && res >= -99){
        res*=-1;
        ans[0] = '-';
        ans[1] = (char)((res)/10 + 48);
        ans[2] = (char)((res)%10 + 48);
        *(begin+3) = '\0';
    }
    if(-100>=res && res >= -729){
        res*=-1;
        ans[0] = '-';
        ans[1] = (char)((res)/100 + 48);
        ans[2] = (char)((res/10)%10 + 48);
        ans[3] = (char)((res)%10 + 48);
        *(begin+4) = '\0';
    }
    fputs(ans, file);
}
void test1_tusk3(){
    char s[1000] = "1-5*3";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f, 0L, 0);
    arithmetic_solve(f);
    fclose(f);
    f = fopen("my_file.txt", "r");
    char ans[10];
    fgets(ans, 9, f);
    fgets(ans, 9, f);
    fclose(f);
    ASSERT_STRING("-12", ans)
    remove("my_file.txt");
}
void test2_tusk3(){
    char s[1000] = "9*9*3";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f, 0L, 0);
    arithmetic_solve(f);
    fclose(f);
    f = fopen("my_file.txt", "r");
    char ans[10];
    fgets(ans, 9, f);
    fgets(ans, 9, f);
    fclose(f);
    ASSERT_STRING("243", ans)
    remove("my_file.txt");
}
void test3_tusk3(){
    char s[1000] = "3+8%10";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f, 0L, 0);
    arithmetic_solve(f);
    fclose(f);
    f = fopen("my_file.txt", "r");
    char ans[10];
    fgets(ans, 9, f);
    fgets(ans, 9, f);
    fclose(f);
    ASSERT_STRING("1", ans)
    remove("my_file.txt");
}
//tusk 4................................................................................................................
void removeSomeStr(FILE *f, char *mask){
    char arr[100000];
    char *begin = arr;
    while (feof(f) == 0){
        char str[1000];
        char *beginStr = str;
        fgets(str, 1000, f);
        *find_symbl(str, '\n') = '\0';
        begin = copy(beginStr, beginStr+strlen_(str), begin);
        *begin = ' ';
        begin++;
    }
    *(begin-1) = '\0';
    BagOfWords words;
    getBagOfWords(&words, arr);
    char res_arr[100000];
    char *begin_res = res_arr;
    int countSpase = 0;
    for(int i = 0; i < words.size; i++){
        if(mask_in_str(&words.words[i], mask)){
            countSpase++;
            begin_res = copy(words.words[i].begin, words.words[i].end, begin_res);
            if(countSpase == 7){
                countSpase = 0;
                *begin_res = '\n';
            } else
                *begin_res = ' ';
            begin_res++;

        }
    }
    words.size = 0;
    *(begin_res-1) = '\n';
    *(begin_res) = '\0';
    fseek(f, 0L, 0);
    fputs(res_arr, f);
    chsize(fileno(f), ftell(f));
}

void test1_tusk4(){
    char s[10000] = "asdf ggasfasf elmberr\nekoveuv ejweuvr erwcvuiev";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f, 0L, 0);
    removeSomeStr(f, "e");
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("elmberr ekoveuv ejweuvr erwcvuiev\n", res)
    remove("my_file.txt");
}
void test2_tusk4(){
    char s[10000] = "ggasefasfffff aesdf ggasefasf elmberr\nekoveuv ejweuvr erwhcvuiev daverwer homE verte\newegvsdv egvwvsdv";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f, 0L, 0);
    removeSomeStr(f, "e");
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("ggasefasfffff aesdf ggasefasf elmberr ekoveuv ejweuvr erwhcvuiev\ndaverwer verte ewegvsdv egvwvsdv\n", res);
    remove("my_file.txt");
}
void test3_tusk4(){
    char s[10000] = "ggasefasfffff aesdf\nggasefasf elmberr\nekoveuv ejweuvr\nerwhcvuiev daverwer homE verte\newegvsdv egvwvsdv";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f, 0L, 0);
    removeSomeStr(f, "e");
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("ggasefasfffff aesdf ggasefasf elmberr ekoveuv ejweuvr erwhcvuiev\ndaverwer verte ewegvsdv egvwvsdv\n", res);
    remove("my_file.txt");
}
void test4_tusk4(){
    char s[10000] = "ggasfeasfffff asdf\nggasfasf lmbrr\nkovuv jwuvr\nrwhcvuiv davrwr hom vrt\nwgvsdv gvwvsdv";
    FILE *f = fopen("my_file.txt", "w+");
    if(f==NULL) {
        printf("NULL");
        return;
    }
    fputs(s,f);
    fseek(f, 0L, 0);
    removeSomeStr(f, "e");
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[1000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("ggasfeasfffff\n", res);
    remove("my_file.txt");
}
//tusk 5................................................................................................................
void more_large_word(FILE *f){
    char largeWods[10000];
    char *begin = largeWods;
    while (feof(f) == 0) {
        char string[10000];
        if (fgets(string, 10000, f) != 0) {
            *find_symbl(string, '\n') = '\0';
            char bigWord[1000];
            largestWord(string, bigWord);
            begin = copy(bigWord, bigWord + strlen_(bigWord), begin);
            *begin = '\n';
            begin++;
        }
    }
    *(begin-1) = '\0';
    fseek(f,0L,0);
    fputs(largeWods,f);
    chsize(fileno(f), ftell(f));
}

void test1_tusk5(){
    char s[10000] = "ggasefasfffff aesdf\nggasefasf elmberr\nekoveuv ejweuvr\nerwhcvuiev daverwer homE verte\nttttwegvsdv egvwvsdv";
    FILE *f = fopen("my_file.txt", "w+");
    fputs(s, f);
    fseek(f, 0L,0);
    more_large_word(f);
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[100000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("ggasefasfffff\nggasefasf\nekoveuv\nerwhcvuiev\nttttwegvsdv", res);
    remove("my_file.txt");
}
void test2_tusk5(){
    char s[10000] = "ggasefasff ggasefasfffff\nevv ggasefasf elmberr\nvev ekoveuv ejweuvr\nrrrr erwhcvuiev daverwer homE verte\nv egvwvsdv";
    FILE *f = fopen("my_file.txt", "w+");
    fputs(s, f);
    fseek(f, 0L,0);
    more_large_word(f);
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[100000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("ggasefasfffff\nggasefasf\nekoveuv\nerwhcvuiev\negvwvsdv", res);
    remove("my_file.txt");
}
void test3_tusk5(){
    char s[10000] = "ggasefasff\nelmberr";
    FILE *f = fopen("my_file.txt", "w+");
    fputs(s, f);
    fseek(f, 0L,0);
    more_large_word(f);
    fclose(f);
    FILE *file = fopen("my_file.txt", "r");
    if(file==NULL) {
        printf("NULL");
        return;
    }
    char res[100000];
    int size = 0;
    while (feof(file)==0){
        res[size] = (char)(getc(file));
        size++;
    }
    res[size-1]='\0';
    fclose(file);
    ASSERT_STRING("ggasefasff\nelmberr", res);
    remove("my_file.txt");
}

//tusk 6................................................................................................................
typedef struct polynomial{
    int index;//показатель
    int coefficient;//число
}pol;

void delet_res_x(FILE *f, int x){
    int res = 0;
    int values[10000];
    int size = 0;
    FILE *Fres = fopen("res.txt", "w+b");
    bool flag_add = true;
    while (feof(f) == 0) {
        pol value;
        if (fread(&value, sizeof(pol), 1, f) == 1) {
            values[size] = value.coefficient;
            values[size + 1] = value.index;
            size += 2;
            if (value.index == 0) {
                res += value.coefficient;
                if (res == 0) {
                    flag_add = false;
                }
                res = 0;
                if (flag_add) {
                    pol ans;
                    int i = 0;
                    while (i < size) {
                        ans.coefficient = values[i];
                        ans.index = values[i + 1];
                        i += 2;
                        fwrite(&ans, sizeof(pol), 1, Fres);
                    }
                }
                flag_add = true;
                size = 0;

            } else {
                res += (int) pow((double) x, (double) value.index) * value.coefficient;
            }
        }
    }
    fseek(f, 0L, 0);
    fseek(Fres, 0L, 0);

    pol ans;
    while (feof(Fres) == 0){
        if(fread(&ans, sizeof(ans), 1, Fres) !=0){
            fwrite(&ans, sizeof(ans), 1,f);
        }
    }
    fclose(Fres);
    remove("res.txt");
    chsize(fileno(f), ftell(f));
}

void test1_tusk6(){
    pol structValues;
    int arr[24] = {1,4,5,3,4,2,-3,1,1,0,3,3,2,2,10,1,12,0,1,2,-3,1,2,0};
    FILE *f = fopen("my_file.txt", "w+b");
    if(f == NULL)
        fprintf(stderr, "fail");
    for(int index = 0; index < 24; index+=2){
        structValues.coefficient = arr[index];
        structValues.index = arr[index+1];
        fwrite(&structValues, sizeof(pol), 1, f);
    }

    pol res;
    fseek(f, 0L, 0);
    delet_res_x(f, 2);
    fclose(f);
    f = fopen("my_file.txt", "rb");
    int res_arr[24];
    int size_res_arr = 0;
    while (feof(f)==0){
        if(fread(&res, sizeof(pol), 1, f)==1){
            res_arr[size_res_arr] = res.coefficient;
            res_arr[size_res_arr+1] = res.index;
            size_res_arr+=2;
        }
    }
    fclose(f);
    int expected[] = {1, 4, 5, 3, 4, 2, -3, 1, 1, 0, 3, 3, 2, 2, 10, 1, 12, 0};
    ASSERT_STRING_INT_ARR(expected, 18, res_arr, size_res_arr)
    remove("my_file.txt");
}
void test2_tusk6(){
    pol structValues;
    int arr[22] = {2,4,4,3,-5,2,-1,1,1,0,1,3,2,1,3,0,1,2,-3,1,2,0};
    FILE *f = fopen("my_file.txt", "w+b");
    if(f == NULL)
        fprintf(stderr, "fail");
    for(int index = 0; index < 22; index+=2){
        structValues.coefficient = arr[index];
        structValues.index = arr[index+1];
        fwrite(&structValues, sizeof(pol), 1, f);
    }
    fseek(f, 0L, 0);
    pol res;
    delet_res_x(f, -1);
    fclose(f);
    f = fopen("my_file.txt", "rb");
    int res_arr[22];
    int size_res_arr = 0;
    while (feof(f)==0){
        if(fread(&res, sizeof(pol), 1, f)==1){
            res_arr[size_res_arr] = res.coefficient;
            res_arr[size_res_arr+1] = res.index;
            size_res_arr+=2;
        }
    }
    fclose(f);
    int expected[] = {2,4,4,3,-5,2,-1,1,1,0,1,2,-3,1,2,0};
    ASSERT_STRING_INT_ARR(expected, 16, res_arr, size_res_arr)
    remove("my_file.txt");
}
//tusk 7................................................................................................................
void ordValues(FILE *f){
    int value;
    int size_plus = 0;
    int size_minus = 0;
    int values_plus[100000];
    int values_minus[100000];
    while (feof(f) == 0){
        if(fread(&value, sizeof(int), 1, f) == 1){
            if(value>0) {
                values_plus[size_plus] = value;
                size_plus++;
            }
            else {
                values_minus[size_minus] = value;
                size_minus++;
            }
        }
    }
    fseek(f,0L,0);
    for(int i = 0; i < size_plus; i++){
        fwrite(&values_plus[i], sizeof(int), 1, f);
    }
    for(int i = 0; i < size_minus; i++){
        fwrite(&values_minus[i], sizeof(int), 1, f);
    }
}

void test1_tusk7(){
    int arr[] = {1,-5,-6,-8,-9,2,1,7,-11,-20,2,54,101,-1,INT_MAX, INT_MIN};
    FILE *f = fopen("my_file.txt", "wb");
    if(f == NULL)
        fprintf(stderr, "fail");
    fwrite(arr, sizeof(arr), 1, f);
    fclose(f);
    f = fopen("my_file.txt", "r+b");
    if(f == NULL)
        fprintf(stderr, "fail");
    ordValues(f);
    fclose(f);
    f = fopen("my_file.txt", "rb");
    if(f == NULL)
        fprintf(stderr, "fail");
    int res[100000];
    int size = 0;
    while (feof(f) == 0){
        int value;
        if(fread(&value, sizeof(int), 1, f)==1){
            res[size] = value;
            size++;
        }
    }
    fclose(f);
    int expected[] = {1,2,1,7,2,54,101,INT_MAX,  -5,-6,-8,-9,-11,-20,-1,INT_MIN};
    ASSERT_STRING_INT_ARR(expected, 16, res, size)
    remove("my_file.txt");
}
void test2_tusk7(){
    int arr[] = {-1,2};
    FILE *f = fopen("my_file.txt", "wb");
    if(f == NULL)
        fprintf(stderr, "fail");
    fwrite(arr, sizeof(arr), 1, f);
    fclose(f);
    f = fopen("my_file.txt", "r+b");
    if(f == NULL)
        fprintf(stderr, "fail");
    ordValues(f);
    fclose(f);
    f = fopen("my_file.txt", "rb");
    if(f == NULL)
        fprintf(stderr, "fail");
    int res[100000];
    int size = 0;
    while (feof(f) == 0){
        int value;
        if(fread(&value, sizeof(int), 1, f)==1){
            res[size] = value;
            size++;
        }
    }
    fclose(f);
    int expected[] = {2,-1};
    ASSERT_STRING_INT_ARR(expected, 2, res, size)
    remove("my_file.txt");
}
void test3_tusk7(){
    int arr[] = {-1,-5,-6,-8,-9,-2,-1,7,11,20,2,54,101,1,INT_MAX, INT_MIN};
    FILE *f = fopen("my_file.txt", "wb");
    if(f == NULL)
        fprintf(stderr, "fail");
    fwrite(arr, sizeof(arr), 1, f);
    fclose(f);
    f = fopen("my_file.txt", "r+b");
    if(f == NULL)
        fprintf(stderr, "fail");
    ordValues(f);
    fclose(f);
    f = fopen("my_file.txt", "rb");
    if(f == NULL)
        fprintf(stderr, "fail");
    int res[100000];
    int size = 0;
    while (feof(f) == 0){
        int value;
        if(fread(&value, sizeof(int), 1, f)==1){
            res[size] = value;
            size++;
        }
    }
    fclose(f);
    int expected[] = {7,11,20,2,54,101,1,INT_MAX,-1,-5,-6,-8,-9,-2,-1,INT_MIN};
    ASSERT_STRING_INT_ARR(expected, 16, res, size)
    remove("my_file.txt");
}
//tusk 8................................................................................................................
void change_matrix(FILE *f){
    int matrix_order;
    if(fread(&matrix_order, sizeof(int), 1, f) == 0)
        fprintf(stderr, "fail");
    int matrixValue[matrix_order*matrix_order];
    int res_arr[10000];
    int size_res = 0;
    while (feof(f)==0){
        if(fread(matrixValue, sizeof(matrixValue), 1, f) > 0){
            matrix m = createMatrixFromArray(matrixValue, matrix_order,matrix_order);
            if(!isSymmetricMatrix(&m)){
                transposeSquareMatrix(&m);
            }
            for(int i = 0; i < m.nRows; i++){
                for(int j = 0; j < m.nCols; j++){
                    res_arr[size_res] = m.values[i][j];
                    size_res++;
                }
            }
        }
    }
    fseek(f,0L, 0);
    fwrite(&matrix_order, sizeof(int), 1, f);
    fwrite(res_arr, size_res* sizeof(int), 1, f);
}
void test1_tusk8(){
    int arr[] = {3,1,2,3,4,5,6,7,8,9,1,1,1,2,2,2,3,3,3,9,9,9,8,8,8,7,7,7,4,4,4,5,5,5,6,6,6};
    FILE *f = fopen("my_file.txt", "wb");
    fwrite(arr, sizeof(arr), 1, f);
    fclose(f);
    FILE *file= fopen("my_file.txt", "r+b");
    if(file == NULL)
        fprintf(stderr, "fail");
    change_matrix(file);
    fclose(file);
    f = fopen("my_file.txt", "rb");
    if(f == NULL)
        fprintf(stderr, "fail");
    int res[100000];
    int size = 0;
    while (feof(f) == 0){
        int value;
        if(fread(&value, sizeof(int), 1, f)==1){
            res[size] = value;
            size++;
        }
    }
    fclose(f);
    int expected[] = {3, 1,4,7,2,5,8,3,6,9,1,2,3,1,2,3,1,2,3,9,8,7,9,8,7,9,8,7,4,5,6,4,5,6,4,5,6};
    ASSERT_STRING_INT_ARR(expected, 37, res, size)
    remove("my_file.txt");
}
void test2_tusk8(){
    int arr[] = {3,1,0,0,0,1,0,0,0,1,1,1,1,2,2,2,3,3,3,9,9,9,8,8,8,7,7,7,4,4,4,5,5,5,6,6,6};
    FILE *f = fopen("my_file.txt", "wb");
    fwrite(arr, sizeof(arr), 1, f);
    fclose(f);
    FILE *file= fopen("my_file.txt", "r+b");
    if(file == NULL)
        fprintf(stderr, "fail");
    change_matrix(file);
    fclose(file);
    f = fopen("my_file.txt", "rb");
    if(f == NULL)
        fprintf(stderr, "fail");
    int res[100000];
    int size = 0;
    while (feof(f) == 0){
        int value;
        if(fread(&value, sizeof(int), 1, f)==1){
            res[size] = value;
            size++;
        }
    }
    fclose(f);
    int expected[] = {3, 1,0,0,0,1,0,0,0,1,1,2,3,1,2,3,1,2,3,9,8,7,9,8,7,9,8,7,4,5,6,4,5,6,4,5,6};
    ASSERT_STRING_INT_ARR(expected, 37, res, size)
    remove("my_file.txt");
}
void test3_tusk8(){
    int arr[] = {5,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1};
    FILE *f = fopen("my_file.txt", "wb");
    fwrite(arr, sizeof(arr), 1, f);
    fclose(f);
    FILE *file= fopen("my_file.txt", "r+b");
    if(file == NULL)
        fprintf(stderr, "fail");
    change_matrix(file);
    fclose(file);
    f = fopen("my_file.txt", "rb");
    if(f == NULL)
        fprintf(stderr, "fail");
    int res[100000];
    int size = 0;
    while (feof(f) == 0){
        int value;
        if(fread(&value, sizeof(int), 1, f)==1){
            res[size] = value;
            size++;
        }
    }
    fclose(f);
    int expected[] = {5,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1};
    ASSERT_STRING_INT_ARR(expected, 26, res, size)
    remove("my_file.txt");
}

//tusk 9................................................................................................................
typedef struct name_list{
    char fio[1000][50];
    int size;
}name_list;
void sport(FILE *f, int n){
    name_list names;
    int arr_value[10000];
    int value; //аджумания
    names.size = 0;
    while (feof(f) == 0){
        char name[50] = {0};
        char *begin = name;
        if(fread(name, sizeof(name), 1, f) > 0 && fread(&value, sizeof(int), 1, f) == 1){
            *(copy(begin, begin+ strlen_(begin), names.fio[names.size])) = '\0';
            arr_value[names.size] = value;
            names.size++;
        }
    }
    int arr_max_index[1000];
    int arr_max_value[1000];
    int size_arr_max_value = 0;
    for(int i = 0; i < n; i++){
        int max = 0;
        int index;
        for(int j = 0; j < names.size; j++){
            if(max < arr_value[j]){
                max = arr_value[j];
                index = j;
            }
        }
        arr_max_index[size_arr_max_value] = index;
        arr_max_value[size_arr_max_value] = max;
        size_arr_max_value++;
        arr_value[index] = -1;
    }
    fseek(f,0L,0);
    for(int i = 0; i < size_arr_max_value; i++){
        char tempStr[50] = {0};
        char *begin = tempStr;
        copy(names.fio[arr_max_index[i]], names.fio[arr_max_index[i]] + strlen_(names.fio[arr_max_index[i]]), begin);
        fwrite(tempStr, sizeof(tempStr), 1, f);
        fwrite(&arr_max_value[i], sizeof(int), 1, f);
    }
    chsize(fileno(f), ftell(f));
}
void test1_tusk9(){
    char name[][50] = {"Fokin Sashko Valentinovich", "Sharipov Genadi Antonovich", "James Brown Fedorovich", "Hector Martinez Petrovich", "Ben Floyd Pantileivich", "Shane Owens Aleksandrovich", "Bradley Morales Ivanovich", "Sitnikov Aleksey Pavlovich"};
    int values[] = {15,35,24,40,28,31,27,-1}; //АДЖУМАНИЯ
    FILE *f = fopen("my_file.txt", "w+b");
    if(f == NULL)
        fprintf(stderr, "fail");
    for(int i = 0; i < 8; i++){
        fwrite(name[i], sizeof(name[i]), 1, f);
        fwrite(&values[i], sizeof(int), 1, f);
    }

    fseek(f, 0L,0);
    sport(f, 5);
    fclose(f);
    f = fopen("my_file.txt", "rb");
    char res[1000];
    int values_max[5];
    int size = 0;
    char *begin = res;
    while (feof(f) == 0){
        char fio[50];
        int val;
        if(fread(fio, sizeof(fio), 1, f) > 0 && fread(&val, sizeof(int), 1, f) == 1){
            begin = copy(fio, fio+ strlen_(fio), begin);
            *begin = ' ';
            begin++;
            values_max[size] = val;
            size++;
        }
    }
    *(begin-1) = '\0';
    fclose(f);
    int expected_val[] = {40,35,31,28,27};
    char expect[] = "Hector Martinez Petrovich Sharipov Genadi Antonovich Shane Owens Aleksandrovich Ben Floyd Pantileivich Bradley Morales Ivanovich";
    ASSERT_STRING(expect, res)
    ASSERT_STRING_INT_ARR(expected_val, 5, values_max, size)
    remove("my_file.txt");
}
void test2_tusk9(){
    char name[][50] = {"Fokin Sashko Valentinovich", "Sharipov Genadi Antonovich", "James Brown Fedorovich", "Hector Martinez Petrovich", "Ben Floyd Pantileivich", "Shane Owens Aleksandrovich", "Bradley Morales Ivanovich", "Sitnikov Aleksey Pavlovich"};
    int values[] = {28,35,24,40,28,31,28,-1}; //АДЖУМАНИЯ
    FILE *f = fopen("my_file.txt", "w+b");
    if(f == NULL)
        fprintf(stderr, "fail");
    for(int i = 0; i < 8; i++){
        fwrite(name[i], sizeof(name[i]), 1, f);
        fwrite(&values[i], sizeof(int), 1, f);
    }
    fseek(f, 0L,0);
    sport(f, 5);
    fclose(f);
    f = fopen("my_file.txt", "rb");
    char res[1000];
    int values_max[5];
    int size = 0;
    char *begin = res;
    while (feof(f) == 0){
        char fio[50];
        int val;
        if(fread(fio, sizeof(fio), 1, f) > 0 && fread(&val, sizeof(int), 1, f) == 1){
            begin = copy(fio, fio+ strlen_(fio), begin);
            *begin = ' ';
            begin++;
            values_max[size] = val;
            size++;
        }
    }
    *(begin-1) = '\0';
    fclose(f);
    int expected_val[] = {40,35,31,28,28};
    char expect[] = "Hector Martinez Petrovich Sharipov Genadi Antonovich Shane Owens Aleksandrovich Fokin Sashko Valentinovich Ben Floyd Pantileivich";
    ASSERT_STRING(expect, res)
    ASSERT_STRING_INT_ARR(expected_val, 5, values_max, size)
    remove("my_file.txt");
}
//tusk 10...............................................................................................................
typedef struct product{
    char name_product[30];
    int price_one;
    int prce_all;
    int count;
}product;
typedef struct send{
    char name_product[30];
    int count;
}send;
void sort_product(FILE *f, FILE *g){
    product prod;
    send sendProd;
    FILE *res = fopen("res.txt", "w+b");
    while (feof(f)==0){

        if(fread(&prod, sizeof(product), 1, f) !=0){
            while (feof(g)==0){
                if(fread(&sendProd, sizeof(send), 1, g) != 0){
                    if(strcmp_(prod.name_product, sendProd.name_product)){
                        prod.count-=sendProd.count;
                        prod.prce_all = prod.price_one*prod.count;
                        break;
                    }
                }
            }
            if(prod.count!=0){
                fwrite(&prod, sizeof(prod), 1,res);
            }
        }
    }
    fseek(res, 0L, 0);
    fseek(f, 0L, 0);

    while (feof(res) == 0){
        if(fread(&prod, sizeof(prod), 1, res) !=0){
            fwrite(&prod, sizeof(prod), 1, f);
        }
    }
    fclose(res);
    chsize(fileno(f), ftell(f));
    remove("res.txt");
}
void test1_tusk10(){
    product priseList;
    int arr[] = {50, 3000, 60,300, 30000, 100, 88, 880, 10, 32, 352,11,120,1200, 10, 5000, 10000, 2,45, 360, 8};
    char name[][30] = {"juice", "PIVO", "milk", "chocolate", "vodka", "brandy", "fish"};
    int count_product = 0;
    FILE *f = fopen("F_my_file.txt", "w+b");
    for(int i = 0; i < 7; i++){
        char *beginName = name[i];
        copy(beginName, beginName+30,priseList.name_product);
        priseList.price_one = arr[count_product];
        count_product++;
        priseList.prce_all = arr[count_product];
        count_product++;
        priseList.count = arr[count_product];
        count_product++;
        fwrite(&priseList, sizeof(product), 1, f);
    }
    send sendList;
    FILE *g = fopen("G_my_file.txt", "wb");
    int countSend[] = {30, 60,10,10,3};
    for(int i = 0; i < 5; i++){
        char *beginName = name[i];
        copy(beginName, beginName+30,sendList.name_product);
        sendList.count = countSend[i];
        fwrite(&sendList, sizeof(sendList), 1, g);
    }
    fclose(g);
    g = fopen("G_my_file.txt", "rb");
    fseek(f, 0L, 0);
    sort_product(f,g);
    fclose(f);
    fclose(g);
    int res[1000];
    f = fopen("F_my_file.txt", "rb");
    product got;
    int size = 0;
    char got_arr[3000][30];
    int size_arr = 0;
    while (feof(f) == 0){
        if(fread(&got, sizeof(got), 1, f)!=0){
            res[size] = got.price_one;
            res[size+1] = got.prce_all;
            res[size+2] = got.count;
            size+=3;
            char *begin_expected = got.name_product;
            copy(begin_expected, begin_expected+30, got_arr[size_arr]);
            size_arr++;
        }
    }
    fclose(f);
    int expected_arr[] = {50,1500,30,300,12000,40,32,32,1,120,840,7,5000,10000,2,45,360,8};
    char expected_str[][30] = {"juice", "PIVO", "chocolate", "vodka", "brandy", "fish"};
    bool flag = true;
    for(int i = 0; i < size_arr;i++){
        if(!strcmp_(expected_str[i], got_arr[i])){
            flag = false;
        }
    }
    if(flag){
        ASSERT_STRING_INT_ARR(expected_arr, 18, res, size);
    }
    remove("F_my_file.txt");
    remove("G_my_file.txt");
}
void test2_tusk10(){
    product priseList;
    int arr[] = {50, 3000, 60,300, 30000, 100, 88, 880, 10, 32, 352,11,120,1200, 10, 5000, 10000, 2,45, 360, 8};
    char name[][30] = {"juice", "PIVO", "milk", "chocolate", "vodka", "brandy", "fish"};
    int count_product = 0;
    FILE *f = fopen("F_my_file.txt", "w+b");
    for(int i = 0; i < 7; i++){
        char *beginName = name[i];
        copy(beginName, beginName+30,priseList.name_product);
        priseList.price_one = arr[count_product];
        count_product++;
        priseList.prce_all = arr[count_product];
        count_product++;
        priseList.count = arr[count_product];
        count_product++;
        fwrite(&priseList, sizeof(product), 1, f);
    }
    send sendList;

    FILE *g = fopen("G_my_file.txt", "wb");
    int countSend[] = {60, 100,10,11,10,1,8};
    for(int i = 0; i < 7; i++){
        char *beginName = name[i];
        copy(beginName, beginName+30,sendList.name_product);
        sendList.count = countSend[i];
        fwrite(&sendList, sizeof(sendList), 1, g);
    }
    fclose(g);
    g = fopen("G_my_file.txt", "rb");
    fseek(f,0L,0);
    sort_product(f,g);
    fclose(f);
    fclose(g);
    int res[1000];
    f = fopen("F_my_file.txt", "rb");
    product got;
    int size = 0;
    char got_arr[3000][30];
    int size_arr = 0;
    while (feof(f) == 0){
        if(fread(&got, sizeof(got), 1, f)!=0){
            res[size] = got.price_one;
            res[size+1] = got.prce_all;
            res[size+2] = got.count;
            size+=3;
            char *begin_expected = got.name_product;
            copy(begin_expected, begin_expected+30, got_arr[size_arr]);
            size_arr++;
        }
    }
    fclose(f);
    int expected_arr[] = {5000,5000,1};
    char expected_str[][30] = { "brandy"};
    bool flag = true;
    for(int i = 0; i < size_arr;i++){
        if(!strcmp_(expected_str[i], got_arr[i])){
            flag = false;
        }
    }
    if(flag){
        ASSERT_STRING_INT_ARR(expected_arr, 3, res, size);
    }
    remove("F_my_file.txt");
    remove("G_my_file.txt");
}
void test_lab19(){
    test1_tusk1();
    test2_tusk1();
    test3_tusk1();
    test1_tusk2();
    test2_tusk2();
    test1_tusk3();
    test2_tusk3();
    test3_tusk3();
    test1_tusk4();
    test2_tusk4();
    test3_tusk4();
    test4_tusk4();
    test1_tusk5();
    test2_tusk5();
    test3_tusk5();
    test1_tusk6();
    test2_tusk6();
    test1_tusk7();
    test2_tusk7();
    test3_tusk7();
    test1_tusk8();
    test2_tusk8();
    test3_tusk8();
    test1_tusk9();
    test2_tusk9();
    test1_tusk10();
    test2_tusk10();
}
