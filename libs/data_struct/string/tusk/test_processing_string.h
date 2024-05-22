//
// Created by admin on 10.04.2024.
//


#ifndef PROJECT17_TEST_PROCESSING_STRING_H
#define PROJECT17_TEST_PROCESSING_STRING_H
void test_lab18();

void assertString(const char *expected, char *got, char const *fileName, char const *funcName,int line);

void assertStringIntArr(int *expected, int size_expected, int *got,int size_got, char const *fileName, char const *funcName, int line);

void assertStringIntArrAndStrArr(int *expectedInt, int size_expectedInt, int *gotInt,int size_gotInt, int size_charArr_expected, char charArr_expected[size_charArr_expected][1000],int size_charArr_got, char charArr_got[size_charArr_got][1000],
                                 char const *fileName, char const *funcName,
                                 int line);

void assertInt(int expected, int got,
               char const *fileName, char const *funcName,
               int line);
#endif //PROJECT17_TEST_PROCESSING_STRING_H
