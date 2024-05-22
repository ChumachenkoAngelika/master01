//
// Created by admin on 01.04.2024.
//
#include "string_.h"

//подсчёт длины строки
size_t strlen_(char *begin) {
    char *end = begin;
    while (*end != '\0') {
        end++;
    }
    return end - begin;
}

//возвращает указатель
//на первый элемент с кодом ch,
char* find(char *begin, char *end, int ch){
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

//возвращает указатель на первый
//символ, отличный от пробельных
char* findNonSpace(char *begin){
    while (*begin != '\0'){
        if(!(isspace(*begin))){
            return begin;
        }
        begin++;
    }
    return begin;
}

//возвращает указатель на первый пробельный символ
char* findSpace(char *begin){
    while (*begin != '\0'){
        if(isspace(*begin)){
            return begin;
        }
        begin++;
    }
    return begin;
}

//возвращает указатель на первый справа символ, отличный от пробельных
char* findNonSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend){
        if(!(isspace(*rbegin))){
            return rbegin;
        }
        rbegin--;
    }
    return rbegin;
}

//возвращает указатель на первый справа пробельный символ
char* findSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend){
        if(isspace(*rbegin)){
            return rbegin;
        }
        rbegin--;
    }
    return rbegin;
}

//сравнение сторк, true если равны
bool strcmp_(const char *lhs, const char *rhs){
    while(*lhs == *rhs && *lhs != '\0'){
        lhs++;
        rhs++;
    }
    return *lhs == *rhs;
}

//записывает по адресу beginDestination
//фрагмент памяти, начиная с адреса beginSource до endSource
char* copy(const char *beginSource, const char *endSource, char *beginDestination){
    memcpy(beginDestination, beginSource, endSource-beginSource);
    beginDestination += endSource - beginSource;
    return beginDestination;
}

// записывает по адресу
//beginDestination элементы из фрагмента памяти начиная с beginSource
//заканчивая endSource, удовлетворяющие функции-предикату f
char* copyIf(char *beginSource, const char *endSource, char *beginDestination, bool(*f)(char*)){
    while (beginSource < endSource){
        if(f(beginSource)){
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    return beginDestination;
}

//// записывает по адресу
////beginDestination элементы из фрагмента памяти начиная с rbeginSource
////заканчивая rendSource, удовлетворяющие функции-предикату f
char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, bool(*f)(char*)){
    while (rbeginSource > rendSource){
        if(f(rbeginSource)){
            *beginDestination = *rbeginSource;
            beginDestination++;
        }
        rbeginSource--;
    }
    return beginDestination;
}