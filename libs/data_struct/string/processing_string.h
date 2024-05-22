//
// Created by admin on 10.04.2024.
//
#include "string_.h"

#ifndef PROJECT17_PROCESSING_STRING_H
#define PROJECT17_PROCESSING_STRING_H
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 1000
typedef struct WordDescriptor {
    char *begin;
    char *end;
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;



//получает конец
char *getEndOfString(char *s);

//убирает пробелы
void removeNonLetters(char *s);

//Преобразовать строку, оставляя только один символ в каждой последовательности подряд идущих одинаковых символов
void removeAdjacentEqualLetters(char *s);

//Сократить количество пробелов между словами данного предложения до
//одного (void removeExtraSpaces(char *s))
void removeExtraSpaces(char *s);

// выражаем слово из строки
int getWord(char *beginSearch, WordDescriptor *word);

// выражаем слова из строки начиная с конца
bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word);

//цифры записывает в начало слова в обратном порядке,
//а буквы в конец слова без изменения порядка
void changeWords_numb(char *s);

//буквы записывает в начало слова в обратном порядке,
//а цифры в конец слова без изменения порядка
void changeWords_Letters(char *s);

//количество цифр = количиству пробелов
void doSpace(char *s);

//заменя всех слов w1 на w2
void replace(char *source, char *w1, char *w2);

//сравнение слов, словов w1 стоит выше чем w2 по алфавиту 0,
//словов w2 стоит выше чем w1 по алфавиту 1, если слова совпали то 2
int areWordsEqual_comparison(WordDescriptor w1, WordDescriptor w2);

//Определить, упорядочены ли лексикографически слова данного предложения.
bool OrderedWords(char *s);

//получаем алреса начала и конца всех слов
void getBagOfWords(BagOfWords *bag, char *s);

//выводит строку с конца
void print_string_revers(char *s);

//возвращает количиство слов палиндромов
int count_palindrome(char *s);

//Получить строку, в которой чередуются слова первой и второй строки.
// Если в одной из строк число слов больше, чем в другой,
// то оставшиеся слова этой строки должны быть дописаны в строку-результат
void switch_words(char *s1, char *s2, char *ans);

//меняет порядок слов в строке
void reverse_string(char *s);

//выводит словов которое стоит перед первым слововом с буквой а
void printWordBeforeFirstWordWithA(char *s);

//перевод из wordDescriptorToString в char*
void wordDescriptorToString(WordDescriptor word, char *destination);

//есть ли слово в строке
bool word_in_string(WordDescriptor w, char *s);

// Определить последнее из слов первой строки, которое есть
//во второй строке, иначе вернёт первое слово в первой строке
WordDescriptor wordFromEndFirstLineWhichStayInSecondLine(char *s1, char *s2);

//есть ли в данной строке одинаковые слова
bool equaleWordsInstring(char *s);

//состоят ли слова из одинакового набора букв
bool equaleLettersInwords(WordDescriptor w1, WordDescriptor w2);

//есть ли в данной строке слова состоящие из одинаковых букв
bool equaleLettersInWordsInstring(char *s);

//равны ли слова
bool equalewords(WordDescriptor w1, WordDescriptor w2);

//записывает строку с конца
char *reverseString(char *s);

//Получить строку из слов данной строки, которые отличны от последнего слова
char *wordsWhitchNotEqualeWithLast(char *s);

//Даны две строки 𝑠1 и 𝑠2. Пусть 𝑤 – первое из слов строки 𝑠1, которое есть и в
//строке 𝑠2. Найти слово, предшествующее первому вхождению 𝑤 в 𝑠1.
WordDescriptor wordBeforeEqualeWords(char *s1, char *s2);

//удаляет все палиндромы
void DeletePalindrome(char *s);

//Пусть 𝑛1 – число слов в первой строке, а 𝑛2 – во второй.
// Требуется дополнить строку, содержащую меньшее количество слов, последними
//словами строки, в которой содержится большее количество слов.
void additionString(char *s1, char *s2, int n1, int n2);

//Определить, входит ли в данную строку каждая буква данного слова
bool allLettersInString(char *s, char *word);

//получает указатель на первый символ или на последний элемент "\0" если символа нет
char *find_symbl(char *s, char symbl);

//есть ли в слове такая маска mask
bool mask_in_str(WordDescriptor *word, char *mask);

//находит наибольшее слово в строке
void largestWord(char *s, char *big);

//есть ли точка в строке
bool point_in_string(char *string);

//считает количество определённых символов
int cound_symbl(char *str, char symbl);
#endif //PROJECT17_PROCESSING_STRING_H
