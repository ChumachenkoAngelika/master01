//
// Created by admin on 01.04.2024.
//
#include <stdio.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef LABA_STRING_H
#define LABA_STRING_H



//подсчёт длины строки
size_t strlen_(char *begin);

//возвращает указатель
//на первый элемент с кодом ch,
char* find(char *begin, char *end, int ch);

//возвращает указатель на первый
//символ, отличный от пробельных
char* findNonSpace(char *begin);

//возвращает указатель на первый пробельный символ
char* findSpace(char *begin);

//возвращает указатель на первый справа символ, отличный от пробельных
char* findNonSpaceReverse(char *rbegin, const char *rend);

//возвращает указатель на первый справа пробельный символ
char* findSpaceReverse(char *rbegin, const char *rend);

//сравнение сторк, true если равны
bool strcmp_(const char *lhs, const char *rhs);

//записывает по адресу beginDestination
//фрагмент памяти, начиная с адреса beginSource до endSource
char* copy(const char *beginSource, const char *endSource, char *beginDestination);

// записывает по адресу
//beginDestination элементы из фрагмента памяти начиная с beginSource
//заканчивая endSource, удовлетворяющие функции-предикату f
char* copyIf(char *beginSource, const char *endSource, char *beginDestination, bool(*f)(char*));

//// записывает по адресу
////beginDestination элементы из фрагмента памяти начиная с rbeginSource
////заканчивая rendSource, удовлетворяющие функции-предикату f
char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, bool(*f)(char*));
#endif //LABA_STRING_H
