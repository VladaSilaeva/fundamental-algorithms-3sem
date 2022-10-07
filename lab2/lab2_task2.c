#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


void usage(){
    printf("На вход программе подается строка и флаг, определяющий действие с этой строкой.\n");
    printf("Программа распознает следующие флаги:\n");
    printf("\ti) -l подсчет длины строки;\n");
    printf("\tii) -r переворот (reverse) строки;\n");
    printf("\tiii) -u преобразовать каждый элемент, стоящий на нечетной позиции в верхний\n");
    printf("регистр;\n");
    printf("\tiv) -n переписать строку так, чтобы в начале строки были символы цифр, затем\n");
    printf("символы букв, а в конце – прочие символы в порядке, определённом исходной строкой;\n");
    printf("\tv) -c конкатенация со строкой, которая передается третьим аргументом.\n");
}

int len(const char *str) {
    int n=0;
    while(str[n]) n++;
    return n;
}

void reverse(const char *str, char **buf){
    int N=len(str);
    char *p = (char*)realloc(*buf, (N+1)*sizeof(char));
    if (!p) return;
    p += N;
    *(p--)=0;
    for(int i=0; i<N; i++, p--) *p = str[i];
    *buf = p;
}

void toupperodds(const char *str, char **buf){
    int N=len(str);
    char *p = (char*)realloc(*buf, (N+1)*sizeof(char));
    if (!p) return;
    *buf = p;
    int i=0;
    for(; str[i]; i++){
        (*buf)[i] = i%2?toupper(str[i]):str[i];
    }
    (*buf)[i+1]=0;
}

void separate_num_alp_other(const char *str, char **buf){
    int N=len(str), l=0, o=0;
    char *letters, *others, *p;
    p = (char*)realloc(*buf, (N+1)*sizeof(char));
    if (!p) return;
    *buf = p;
    letters = (char*)malloc(N*sizeof(char));
    others = (char*)malloc(N*sizeof(char));
    for(int i=0; str[i]; i++){
        if (isdigit(str[i])) *(p++) = str[i];
        else if(isalpha(str[i])) letters[l++]=str[i];
        else others[o++]=str[i];
    }
    for(int i=0; i<l; i++) *(p++) = letters[i];
    for(int i=0; i<o; i++) *(p++) = others[i];
    p=0;
}

void concatenation(const char *str1, const char *str2, char **buf){
    int N=len(str1)+len(str2);
    char *p = (char*)realloc(*buf, (N+1)*sizeof(char));
    if (!p) return;
    *buf = p;
    for(int i=0; str1[i]; i++){
        *(p++) = str1[i];
    }
    for(int i=0; str2[i]; i++){
        *(p++) = str2[i];
    }
    *p=0;
}

int main(int argc, char **argv)
{
    char *buf=NULL;
    int ans, is_flags_correct=1;
    if (argc == 3) {
        if (strcmp(argv[1], "-l")==0 || strcmp(argv[1], "/l")==0) {//len
            ans=len(argv[2]);
            printf("Длина строки равна %d\n", ans);
        } else if (strcmp(argv[1], "-r")==0 || strcmp(argv[1], "/r")==0) {//reverse
            reverse(argv[2], &buf);
            printf("Реверс строки %s\n", buf);
        } else if (strcmp(argv[1], "-u")==0 || strcmp(argv[1], "/u")==0) {//toupperodds
            toupperodds(argv[2], &buf);
            printf("Измененная строка %s\n", buf);
        } else if (strcmp(argv[1], "-n")==0 || strcmp(argv[1], "/n")==0) {//flag_n        
            separate_num_alp_other(argv[2], &buf);
            printf("Измененная строка %s\n", buf);
        } else {
            is_flags_correct = 0;
            printf("Неправильный флаг или число аргументов\n");
        }
    }
    else if (argc == 4) {
        if (strcmp(argv[1], "-c")==0 || strcmp(argv[1], "/c")==0) {//concatenation
            concatenation(argv[2], argv[3], &buf);
            printf("Конкатенация строк %s\n", buf);
        } else {
            is_flags_correct = 0;
            printf("Неправильный флаг или число аргументов\n");
        }
    }
    else {
        is_flags_correct = 0;
        printf("Неправильное число аргументов\n");
    }
    if (!is_flags_correct) usage();
    free(buf);
    return 0;
}