//
// Created by admin on 10.04.2024.
//

#include "test_processing_string.h"
#include "../string_.h"
#include "../processing_string.h"
#include <assert.h>

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_STRING_INT(expected, got) assertStringInt(expected, got, __FILE__, __FUNCTION__, __LINE__)
void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (!strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void assertStringInt(int expected, int got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (expected != got) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%d\"\n", expected);
        fprintf(stderr, "Got: \"%d\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}
void printInt(int *arr, int size){
    for(int i = 0; i < size;i++){
        fprintf(stderr,"%d ", arr[i]);
    }
}
void assertStringIntArr(int *expected, int size_expected, int *got,int size_got,
                     char const *fileName, char const *funcName,
                     int line) {
    bool flag = size_expected == size_got;
    if(flag) {
        for (int i = 0; i < size_got; i++) {
            if (expected[i] != got[i]) {
                flag = false;
                break;
            }
        }
    }
    if (!flag) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr,"expected: ");
        printInt(expected,size_expected);
        fprintf(stderr,"got: ");
        printInt(got, size_got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}
void print_char_array(int size, char array[size][1000]){
    for(int i = 0; i < size; i++){
        char *begin = array[i];
        while(*begin!='\0'){
            fprintf(stderr,"%c", *begin);
            begin++;
        }
        printf(" ");
    }
}
void assertStringIntArrAndStrArr(int *expectedInt, int size_expectedInt, int *gotInt,int size_gotInt, int size_charArr_expected, char charArr_expected[size_charArr_expected][1000],int size_charArr_got, char charArr_got[size_charArr_got][1000],
                                 char const *fileName, char const *funcName,
                                 int line) {
    bool flag = size_expectedInt == size_gotInt;
    if(flag) {
        for (int i = 0; i < size_gotInt; i++) {
            if (expectedInt[i] != gotInt[i]) {
                flag = false;
                break;
            }

        }
    }if(flag){
        flag = size_charArr_expected == size_charArr_got;
    }
    if(flag){
        for(int i = 0; i < size_charArr_expected; i++){
            if(!(strcmp_(charArr_expected[i], charArr_got[i]))){
                flag = false;
                break;
            }
        }
    }
    if (!flag) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr,"expected: ");
        printInt(expectedInt,size_expectedInt);
        printf("\n");
        fprintf(stderr,"got: ");
        printInt(gotInt, size_gotInt);
        printf("\n");
        print_char_array(size_charArr_expected,charArr_expected);
        printf("\n");
        print_char_array(size_charArr_got,charArr_got);

    } else
        fprintf(stderr, "%s - OK\n", funcName);
}
void assertInt(int expected, int got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (expected!=got) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%d\"\n", expected);
        fprintf(stderr, "Got: \"%d\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}
//tusk 1.........................................................................................
void test_removeNonLetters_first(){
    char words[] = "hello, how are you";
    removeNonLetters(words);
    ASSERT_STRING("hello,howareyou", words);
}
void test_removeNonLetters_second(){
    char words[] = "hi 12 3     25548\n 15 jkk";
    removeNonLetters(words);
    ASSERT_STRING("hi1232554815jkk", words);
}
void test_removeNonLetters_third(){
    char words[] = "hi1232554815jkk";
    removeNonLetters(words);
    ASSERT_STRING("hi1232554815jkk", words);
}
void test_removeNonLetters_fourth(){
    char words[] = "  ";
    removeNonLetters(words);
    ASSERT_STRING("", words);
}
//tusk 2.1......................................................................................
void test_removeAdjacentEqualLetters_first(){
    char words[] = "aaaaa";
    removeAdjacentEqualLetters(words);
    ASSERT_STRING("a", words);
}
void test_removeAdjacentEqualLetters_second(){
    char words[] = "aaa bb bb";
    removeAdjacentEqualLetters(words);
    ASSERT_STRING("a b b", words);
}
void test_removeAdjacentEqualLetters_third(){
    char words[] = "  ";
    removeAdjacentEqualLetters(words);
    ASSERT_STRING(" ", words);
}
void test_removeAdjacentEqualLetters_fourth(){
    char words[] = "";
    removeAdjacentEqualLetters(words);
    ASSERT_STRING("", words);
}
//2.2..............................................................................
void test_removeExtraSpaces_first(){
    char words[] = "aaaaa";
    removeExtraSpaces(words);
    ASSERT_STRING("aaaaa", words);
}
void test_removeExtraSpaces_second(){
    char words[] = "aaa  bb  b";
    removeExtraSpaces(words);
    ASSERT_STRING("aaa bb b", words);
}
void test_removeExtraSpaces_third(){
    char words[] = "  ";
    removeExtraSpaces(words);
    ASSERT_STRING(" ", words);
}
void test_removeExtraSpaces_fourth(){
    char words[] = "";
    removeExtraSpaces(words);
    ASSERT_STRING("", words);
}
//3.......................................................................................................................
void test_digitToStart_first(){
    char s[] = "hello81 F822";
    changeWords_numb(s);
    ASSERT_STRING("18hello 228F", s);
}
void test_digitToStart_second(){
    char s[] = "hello81 zxc123456789 856947";
    changeWords_numb(s);
    ASSERT_STRING("18hello 987654321zxc 749658", s);
}
void test_digitToStart_third(){
    char s[] = "";
    changeWords_numb(s);
    ASSERT_STRING("", s);
}
void test_getWordReverse(){
    WordDescriptor word;
    char s[] = "123 222 8585";
    getWordReverse(s,s + strlen_(s)-1, &word);
    ASSERT_STRING("8585", word.begin);
}
//решение задачи №1
void test_LettersToStart_first(){
    char s[] = "hello81 tF822";
    changeWords_Letters(s);
    ASSERT_STRING("olleh81 Ft822", s);
}
void test_LettersToStart_second(){
    char s[] = "18hello 987654321zxc 749658";
    changeWords_Letters(s);
    ASSERT_STRING("olleh18 cxz987654321 749658", s);
}

//4.....................................................................................................................
void test_doSpace_first(){
    char s[100] = "he3l1lo5";
    doSpace(s);
    ASSERT_STRING("he   l lo     ", s);
}
void test_doSpace_second(){
    char s[100] = "123";
    doSpace(s);
    ASSERT_STRING("      ", s);
}
void test_doSpace_third(){
    char s[100] = "";
    doSpace(s);
    ASSERT_STRING("", s);
}

//5.....................................................................................................................
void test_replace_first(){
    char s[] = "hhhhh hhhhhf hhh";
    char s1[] = "hhhhh";
    char s2[] = "hhh";
    replace(s, s1, s2);
    ASSERT_STRING("hhh hhhhhf hhh", s);
}
void test_replace_second(){
    char s[] = "hhhhh hhhhh hhhhh hhhhh";
    char s1[] = "hhhhh";
    char s2[] = "hhh";
    replace(s, s1, s2);
    ASSERT_STRING("hhh hhh hhh hhh", s);
}
void test_replace_third(){
    char s[] = "adfg adfg adfg adfg ,adfg";
    char s1[] = "adfg";
    char s2[] = "hhh";
    replace(s, s1, s2);
    ASSERT_STRING("hhh hhh hhh hhh ,adfg", s);
}
void test_replace_fourth(){
    char s[] = ",adfg ,adfg ,adfg ,adfg ,adfg";
    char s1[] = "adfg";
    char s2[] = "hhh";
    replace(s, s1, s2);
    ASSERT_STRING(",adfg ,adfg ,adfg ,adfg ,adfg", s);
}
void test_replace_fifth(){
    char s[] = "hh hh hha";
    char s1[] = "hh";
    char s2[] = "hhh";
    replace(s, s1, s2);
    ASSERT_STRING("hhh hhh hha", s);
}
void test_replace_sixth(){
    char s[] = "hh hh h";
    char s1[] = "hh";
    char s2[] = "hhh";
    replace(s, s1, s2);
    ASSERT_STRING("hhh hhh h", s);
}
//6.......................................................................................................................
void test_areWordsEqual_first(){
    char s1[] = "abc";
    char s2[] = "abcg";
    WordDescriptor w1, w2;
    getWord(s1,&w1);
    getWord(s2,&w2);
    ASSERT_STRING_INT(0, areWordsEqual_comparison(w1, w2));
}
void test_areWordsEqual_second(){
    char s1[] = "abc";
    char s2[] = "abc";
    WordDescriptor w1, w2;
    getWord(s1,&w1);
    getWord(s2,&w2);
    ASSERT_STRING_INT(2, areWordsEqual_comparison(w1, w2));
}
void test_areWordsEqual_third(){
    char s1[] = "bcd";
    char s2[] = "abcd";
    WordDescriptor w1, w2;
    getWord(s1,&w1);
    getWord(s2,&w2);
    ASSERT_STRING_INT(1, areWordsEqual_comparison(w1, w2));
}

void test_OrderedWords_first(){
    int ans;
    char s[100] = "abcdd mdfgh zxc";
    if(OrderedWords(s))
        ans = 1;
    else
        ans = 0;
    ASSERT_STRING_INT(1, ans);
}
void test_OrderedWords_second(){
    int ans;
    char s[100] = "abcdd mdfgh axc";
    if(OrderedWords(s))
        ans = 1;
    else
        ans = 0;
    ASSERT_STRING_INT(0, ans);
}
void test_OrderedWords_third(){
    int ans;
    char s[100] = "abcdd abcdd abvc aa";
    if(OrderedWords(s))
        ans = 1;
    else
        ans = 0;
    ASSERT_STRING_INT(0, ans);
}
void test_OrderedWords_fourth(){
    int ans;
    char s[100] = "abcdd abcdd abvc abvz aa";
    if(OrderedWords(s))
        ans = 1;
    else
        ans = 0;
    ASSERT_STRING_INT(0, ans);
}
void test_OrderedWords_sixth(){
    int ans;
    char s[100] = "abcd abcdd abvc abvz";
    if(OrderedWords(s))
        ans = 1;
    else
        ans = 0;
    ASSERT_STRING_INT(1, ans);
}
//8...........................................................,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//работает
/*
void test_print_string_revers_first(){
    char s[MAX_STRING_SIZE] = "aaaa ssss dddd ff ggg hhhh j";
    print_string_revers(s);
}
void test_print_string_revers_second(){
    char s[MAX_STRING_SIZE] = "";
    print_string_revers(s);
}
*/
//8...........................................................,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
void test_count_count_palindrome_first(){
    char s[MAX_STRING_SIZE] = "Nun, Level, Deed, Sagas, Peep, h";
    ASSERT_STRING_INT(5, count_palindrome(s));
}
void test_count_count_palindrome_second(){
    char s[MAX_STRING_SIZE] = "Nun, Level, Deed, Saga, Peep";
    ASSERT_STRING_INT(4, count_palindrome(s));
}
//9...........................................................,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
void test_switch_words_first(){
    char s1[MAX_STRING_SIZE] = "fff ggg hhh jjj";
    char s2[MAX_STRING_SIZE] = "kkk lll qqq www";
    char ans[MAX_STRING_SIZE];
    switch_words(s1,s2,ans);
    ASSERT_STRING("fff kkk ggg lll hhh qqq jjj www", ans);
}
void test_switch_words_second(){
    char s1[MAX_STRING_SIZE] = "fff ggg hhh jjj";
    char s2[MAX_STRING_SIZE] = "kkk lll qqq www mmmmm fffffffafa";
    char ans[MAX_STRING_SIZE];
    switch_words(s1,s2,ans);
    ASSERT_STRING("fff kkk ggg lll hhh qqq jjj www mmmmm fffffffafa", ans);
}
void test_switch_words_third(){
    char s1[MAX_STRING_SIZE] = "fff ggg hhh jjj mmmmm fffffffafa";
    char s2[MAX_STRING_SIZE] = "kkk lll qqq www";
    char ans[MAX_STRING_SIZE];
    switch_words(s1,s2,ans);
    ASSERT_STRING("fff kkk ggg lll hhh qqq jjj www mmmmm fffffffafa", ans);
}
//10....................................................................................................................
void test_reverse_string_first(){
    char s[MAX_STRING_SIZE] = "fff ggg hhh jjj";
    reverse_string(s);
    ASSERT_STRING("jjj hhh ggg fff", s);
}
void test_reverse_string_second(){
    char s[MAX_STRING_SIZE] = "a d f  g";
    reverse_string(s);
    ASSERT_STRING("g f d a", s);
}
//11......................................................................................................................
/*
void test_printWordBeforeFirstWordWithA_first(){
    char s[MAX_STRING_SIZE] = "  tttt g skldk aggg";
    printWordBeforeFirstWordWithA(s);
    //ответ: skldk, сошлось
}
void test_printWordBeforeFirstWordWithA_second(){
    char s[MAX_STRING_SIZE] = "  tttt g hkldk gggg";
    printWordBeforeFirstWordWithA(s);
    //ответ:no one word with A, сошлось
}
void test_printWordBeforeFirstWordWithA_third(){
    char s[MAX_STRING_SIZE] = "   ";
    printWordBeforeFirstWordWithA(s);
    //ответ: no one word in string, сошлось
}
void test_printWordBeforeFirstWordWithA_fourth(){
    char s[MAX_STRING_SIZE] = "  attt g akldk gggg";
    printWordBeforeFirstWordWithA(s);
    //ответ: word with letter A first, сошлось
}
*/
//12.......................................................................................................................
void test_wordDescriptorToString_first(){
    char s[MAX_STRING_SIZE] = "hgh gg ggg";
    WordDescriptor word;
    char ans[MAX_STRING_SIZE];
    getWord(s,&word);
    wordDescriptorToString(word, ans);
    ASSERT_STRING("hgh", ans);
}
void test_wordDescriptorToString_second(){
    char s[MAX_STRING_SIZE] = "  hgh gg ggg";
    WordDescriptor word;
    char ans[MAX_STRING_SIZE];
    getWord(s,&word);
    wordDescriptorToString(word, ans);
    ASSERT_STRING("hgh", ans);
}
void test_word_in_string_frist(){
    char s[MAX_STRING_SIZE] = "hgh gg ggg";
    WordDescriptor word;
    char string[MAX_STRING_SIZE] = "vnev eee edjvj hgh veve";
    int ans;
    getWord(s,&word);
    if(word_in_string(word,string)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_word_in_string_second(){
    char s[MAX_STRING_SIZE] = "hgh gg ggg";
    WordDescriptor word;
    char string[MAX_STRING_SIZE] = "vnev eee edjvj egeg hgh";
    int ans;
    getWord(s,&word);
    if(word_in_string(word,string)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_word_in_string_third(){
    char s[MAX_STRING_SIZE] = "hgh gg ggg";
    WordDescriptor word;
    char string[MAX_STRING_SIZE] = "vnev eee edjvj egeg ss";
    int ans;
    getWord(s,&word);
    if(word_in_string(word,string)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(0, ans);
}
void test_wordFromEndFirstLineWhichStayInSecondLine_first(){
    char s1[MAX_STRING_SIZE] = "hgh gg ggg";
    char s2[MAX_STRING_SIZE] = "vnev eee gg egeg ss";
    WordDescriptor ansW = wordFromEndFirstLineWhichStayInSecondLine(s1,s2);
    char ans [MAX_STRING_SIZE];
    wordDescriptorToString(ansW,ans);
    ASSERT_STRING("gg", ans);
}
void test_wordFromEndFirstLineWhichStayInSecondLine_second(){
    char s1[MAX_STRING_SIZE] = "hgh gg ggg";
    char s2[MAX_STRING_SIZE] = "vnev eee sgg egeg ss";
    WordDescriptor ansW = wordFromEndFirstLineWhichStayInSecondLine(s1,s2);
    char ans [MAX_STRING_SIZE];
    wordDescriptorToString(ansW,ans);
    ASSERT_STRING("hgh", ans);
}
//13..................................................................................................................
void test_equaleWordsInstring_frist(){
    char s2[MAX_STRING_SIZE] = "ss eee sgg egeg ss";
    int ans;
    if(equaleWordsInstring(s2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_equaleWordsInstring_second(){
    char s2[MAX_STRING_SIZE] = "s eee sgg egeg s";
    int ans;
    if(equaleWordsInstring(s2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_equaleWordsInstring_third(){
    char s2[MAX_STRING_SIZE] = "ss eee sgg egeg sg";
    int ans;
    if(equaleWordsInstring(s2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(0, ans);
}
void test_equaleWordsInstring_fourth(){
    char s2[MAX_STRING_SIZE] = "ss ssg sgg egeg sg";
    int ans;
    if(equaleWordsInstring(s2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
//14......................................................................................................................
void test_equaleLettersInwords_first(){
    WordDescriptor w1,w2;
    char s1[MAX_STRING_SIZE] = "asdf";
    char s2[MAX_STRING_SIZE] = "fdsa";
    getWord(s1,&w1);
    getWord(s2,&w2);
    int ans;
    if(equaleLettersInwords(w1,w2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_equaleLettersInwords_second(){
    WordDescriptor w1,w2;
    char s1[MAX_STRING_SIZE] = "dafs";
    char s2[MAX_STRING_SIZE] = "fdsa";
    getWord(s1,&w1);
    getWord(s2,&w2);
    int ans;
    if(equaleLettersInwords(w2,w1)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_equaleLettersInwords_third(){
    WordDescriptor w1,w2;
    char s1[MAX_STRING_SIZE] = "ddfs";
    char s2[MAX_STRING_SIZE] = "fdsa";
    getWord(s1,&w1);
    getWord(s2,&w2);
    int ans;
    if(equaleLettersInwords(w2,w1)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(0, ans);
}
void test_equaleLettersInWordsInstring_first(){
    char s[MAX_STRING_SIZE] = "ddfs jeejjej kkkk fdsa dafs";
    int ans;
    if(equaleLettersInWordsInstring(s)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_equaleLettersInWordsInstring_second(){
    char s[MAX_STRING_SIZE] = "ddfs jeejjej kkkk fdsa drfs";
    int ans;
    if(equaleLettersInWordsInstring(s)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(0, ans);
}
void test_equaleLettersInWordsInstring_third(){
    char s[MAX_STRING_SIZE] = "drfs jeejjej kkkk fdsa drfs";
    int ans;
    if(equaleLettersInWordsInstring(s)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
//15..................................................................................................................................
void test_equalewords_first(){
    WordDescriptor w1,w2;
    char s1[MAX_STRING_SIZE] = "ddfs";
    char s2[MAX_STRING_SIZE] = "ddfs";
    getWord(s1,&w1);
    getWord(s2,&w2);
    int ans;
    if(equalewords(w2,w1)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_equalewords_second(){
    WordDescriptor w1,w2;
    char s1[MAX_STRING_SIZE] = "ddfd";
    char s2[MAX_STRING_SIZE] = "ddfs";
    getWord(s1,&w1);
    getWord(s2,&w2);
    int ans;
    if(equalewords(w2,w1)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(0, ans);
}
void test_reverseString(){
    char s1[MAX_STRING_SIZE] = "asdffgg";
    ASSERT_STRING("ggffdsa", reverseString(s1));
}
void test_wordsWhitchNotEqualeWithLast_first(){
    char *s = "ff ggg hh ds fd sssss ll";
    ASSERT_STRING("ff ggg hh ds fd sssss", wordsWhitchNotEqualeWithLast(s));
}
void test_wordsWhitchNotEqualeWithLast_second(){
    char *s = "ff ggg hh ds fd hhh hh";
    ASSERT_STRING("ff ggg ds fd hhh", wordsWhitchNotEqualeWithLast(s));
}
//16.....................................................................................................................
void test_wordBeforeEqualeWords_first(){
    char *s1 = "ff ggg hh ds fd hhh hh";
    char *s2 = "ghg hhh hh effff";
    WordDescriptor ans = wordBeforeEqualeWords(s1,s2);
    char ans_str[128];
    wordDescriptorToString(ans,ans_str);
    ASSERT_STRING("hhh", ans_str);
}
void test_wordBeforeEqualeWords_second(){
    char *s1 = "ff ggg hh ds fd hhh hh";
    char *s2 = "ghg hhh ss effff";
    WordDescriptor ans = wordBeforeEqualeWords(s1,s2);
    char ans_str[128];
    wordDescriptorToString(ans,ans_str);
    ASSERT_STRING("ghg", ans_str);
}
void test_wordBeforeEqualeWords_third(){
    char *s1 = "ff ggg hh ds fd hfsfs hh";
    char *s2 = "ghg hhh ss effff";
    WordDescriptor ans = wordBeforeEqualeWords(s1,s2);
    char ans_str[128];
    wordDescriptorToString(ans,ans_str);
    ASSERT_STRING("ff", ans_str);
}
void test_wordBeforeEqualeWords_fourth(){
    char *s1 = "ff ggg hh ds fd hfsfs ghg";
    char *s2 = "ghg hhh ss effff";
    WordDescriptor ans = wordBeforeEqualeWords(s1,s2);
    char ans_str[128];
    wordDescriptorToString(ans,ans_str);
    ASSERT_STRING("ff", ans_str);
}
//17.....................................................................................................................
void test_DeletePalindrome_frist(){
    char s[MAX_STRING_SIZE] = "fgff ggg hfsh ff ds fd hfsfs ghg";
    DeletePalindrome(s);
    ASSERT_STRING("fgff hfsh ds fd hfsfs", s);
}
void test_DeletePalindrome_second(){
    char s[MAX_STRING_SIZE] = "f fgff ggfg hfsh ffs ds hfsfs ghsg";
    DeletePalindrome(s);
    ASSERT_STRING("f fgff ggfg hfsh ffs ds hfsfs ghsg", s);
}
//18....................................................................................................................
void test_additionString_first(){
    char s1[MAX_STRING_SIZE] = "fgff ggg hfsh ff";
    char s2[MAX_STRING_SIZE] = "fgggff ff hj ff ds fd";
    additionString(s1,s2,4,6);
    ASSERT_STRING("fgff ggg hfsh ff ds fd", s1);
}
void test_additionString_second(){
    char s1[MAX_STRING_SIZE] = "fgggff ff hj ff ds fd";
    char s2[MAX_STRING_SIZE] = "fgff ggg hfsh ff";
    additionString(s1,s2,6,4);
    ASSERT_STRING("fgff ggg hfsh ff ds fd", s2);
}//19............................................................................................................................
void test_allLettersInString_first(){
    char s1[MAX_STRING_SIZE] = "fgggff ff hj ff as fd";
    char s2[MAX_STRING_SIZE] = "aghj";
    int ans;
    if(allLettersInString(s1,s2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}
void test_allLettersInString_second(){
    char s1[MAX_STRING_SIZE] = "fgggff ff hj ff s fd";
    char s2[MAX_STRING_SIZE] = "aghj";
    int ans;
    if(allLettersInString(s1,s2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(0, ans);
}
void test_allLettersInString_third(){
    char s1[MAX_STRING_SIZE] = "fgggfvf ff hjra ff se fd";
    char s2[MAX_STRING_SIZE] = "avvveerveveevr";
    int ans;
    if(allLettersInString(s1,s2)){
        ans = 1;
    } else{
        ans = 0;
    }
    ASSERT_STRING_INT(1, ans);
}

void test_find_symbl_first(){
    char s[100] = "asdfghjkl.gf";
    char symbl = '.';
    assert(find_symbl(s,symbl) == s+9);
}
void test_find_symbl_second(){
    char s[100] = "asdfghjklgf";
    char symbl = '.';
    assert(find_symbl(s,symbl) == s+11);
}
void test_find_symbl_third(){
    char s[100] = ".asdfghjklgf";
    char symbl = '.';
    assert(find_symbl(s,symbl) == s);
}

void test_lab18(){
    test_removeNonLetters_first();
    test_removeNonLetters_second();
    test_removeNonLetters_third();
    test_removeNonLetters_fourth();
    test_removeAdjacentEqualLetters_first();
    test_removeAdjacentEqualLetters_second();
    test_removeAdjacentEqualLetters_third();
    test_removeAdjacentEqualLetters_fourth();
    test_removeExtraSpaces_first();
    test_removeExtraSpaces_second();
    test_removeExtraSpaces_third();
    test_removeExtraSpaces_fourth();
    test_digitToStart_first();
    test_digitToStart_second();
    test_digitToStart_third();
    test_LettersToStart_first();
    test_LettersToStart_second();
    test_getWordReverse();
    test_doSpace_first();
    test_doSpace_second();
    test_doSpace_third();
    test_replace_first();
    test_replace_second();
    test_replace_third();
    test_replace_fourth();
    test_replace_fifth();
    test_replace_sixth();
    test_areWordsEqual_first();
    test_areWordsEqual_second();
    test_areWordsEqual_third();
    test_OrderedWords_first();
    test_OrderedWords_second();
    test_OrderedWords_third();
    test_OrderedWords_fourth();
    test_OrderedWords_sixth();
    /*
    test_print_string_revers_first();
    test_print_string_revers_second();
    */
    test_count_count_palindrome_first();
    test_count_count_palindrome_second();
    test_switch_words_first();
    test_switch_words_second();
    test_switch_words_third();
    test_reverse_string_first();
    test_reverse_string_second();
    /*
    test_printWordBeforeFirstWordWithA_first();
    test_printWordBeforeFirstWordWithA_second();
    test_printWordBeforeFirstWordWithA_third();
    test_printWordBeforeFirstWordWithA_fourth();
     */
    test_wordDescriptorToString_first();
    test_wordDescriptorToString_second();
    test_word_in_string_frist();
    test_word_in_string_second();
    test_word_in_string_third();
    test_wordFromEndFirstLineWhichStayInSecondLine_first();
    test_wordFromEndFirstLineWhichStayInSecondLine_second();
    test_equaleWordsInstring_frist();
    test_equaleWordsInstring_second();
    test_equaleWordsInstring_third();
    test_equaleWordsInstring_fourth();
    test_equaleLettersInwords_first();
    test_equaleLettersInwords_second();
    test_equaleLettersInwords_third();
    test_equaleLettersInWordsInstring_first();
    test_equaleLettersInWordsInstring_second();
    test_equaleLettersInWordsInstring_third();
    test_equalewords_first();
    test_equalewords_second();
    test_reverseString();
    test_wordsWhitchNotEqualeWithLast_first();
    test_wordsWhitchNotEqualeWithLast_second();
    test_wordBeforeEqualeWords_first();
    test_wordBeforeEqualeWords_second();
    test_wordBeforeEqualeWords_third();
    test_wordBeforeEqualeWords_fourth();
    test_DeletePalindrome_frist();
    test_DeletePalindrome_second();
    test_additionString_first();
    test_additionString_second();
    test_allLettersInString_first();
    test_allLettersInString_second();
    test_allLettersInString_third();
    test_find_symbl_first();
    test_find_symbl_second();
    test_find_symbl_third();
}