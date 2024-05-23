#include<stdio.h>
#include<stdlib.h>
#include <signal.h>
#include "libs/data_struct/string/processing_string.h"
void testLab20();
char *find_suffix(char *s);




volatile sig_atomic_t print_next = 0;
void handle_signal(int sig){
    if(sig==SIGINT){
        print_next = 1;
    }
}
int main(int argc, char *argv[]) {
    char lines[] = "gggggggg aaaaaaaaa\npppppp\nkkkkkkkk llllllll pppppppp\nprogram\nend\nnow\nfffff\nnnnnnnn\nmmmmmmmm\nwait\n1\nsec";
    FILE *f = fopen(argv[1], "w+");
    if(f==NULL) {
        fprintf(stderr, "Fail");
        exit(1);
    }
    fputs(lines, f);
    fseek(f, 0L, 0);
    int count_line = 0;
    int N = atoi(argv[2]);
    while(fgets(lines, 1000, f) > 0){
        signal(SIGINT, handle_signal);
        while (!print_next){}
        if(print_next){
            printf("%s", lines);
            count_line++;
        }
        if(count_line == N) {
            print_next = 0;
            count_line = 0;
        }
    }
    printf("\n");
    testLab20();
    return 0;
}
