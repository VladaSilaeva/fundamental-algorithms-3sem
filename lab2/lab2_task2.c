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

char* reverse(const char *str, char **buf, int b_size){
    char *p = *buf+b_size-1;
    *(p--) = 0;
    for(int i=0; (str[i]&&(i<b_size)); i++){
        *(p--) = str[i];
    }
    return p;
}

void reverse2(const char *str, char **buf, int b_size){
    int N=len(str);
    char *p = (char*)realloc(*buf, (N+1)*sizeof(char));
    if (!p) return;
    p += N;
    *(p--)=0;
    for(int i=0; i<N; i++, p--) *p = str[i];
    *buf = p;
}

void toupperodds(const char *str, char **buf, int b_size){
    int i=0;
    for(; (str[i]&&(i<b_size-1)); i++){
        (*buf)[i] = i%2?toupper(str[i]):str[i];
    }
    (*buf)[i+1]=0;
}

void flag_n(const char *str, char **buf, int b_size){
    int n=0, l=0, o=0;
    char *letters, *others, *p=*buf;
    letters = (char*)malloc(b_size*sizeof(char));
    others = (char*)malloc(b_size*sizeof(char));
    for(int i=0; (str[i]&&(i<b_size)); i++){
        if (isdigit(str[i])){
            *(p++) = str[i];
            n++;
        } else if(isalpha(str[i])) letters[l++]=str[i];
        else others[o++]=str[i];
    }
    for(int i=0; (i<l)&&(n+i<b_size); i++) *(p++) = letters[i];
    for(int i=0; (i<o)&&(n+l+i<b_size); i++) *(p++) = others[i];
    p=0;
}

void concatenation(const char *str1, const char *str2, char **buf, int b_size){
    char *p = *buf;
    for(int i=0; (str1[i]&&(i<b_size)); i++){
        *(p++) = str1[i];
    }
    for(int i=0; (str2[i]&&(i<b_size)); i++){
        *(p++) = str2[i];
    }
    *p=0;
}

int main(int argc, char **argv)
{
    char *buf=NULL;
    int SIZE=100, ans;
    if (argc > 2) SIZE=len(argv[2])+1;
    buf = (char*)malloc(SIZE*sizeof(char)); //можно изначально выделить память
    if (argc == 3) {
        if (strcmp(argv[1], "-l")==0 || strcmp(argv[1], "/l")==0) {//len
            ans=len(argv[2]);
            printf("Длина строки равна %d\n", ans);
        } else if (strcmp(argv[1], "-r")==0 || strcmp(argv[1], "/r")==0) {//reverse
            //str = reverse(argv[2], &buf, SIZE);
            reverse2(argv[2], &buf, SIZE);
            printf("Реверс строки %s\n", buf);
        } else if (strcmp(argv[1], "-u")==0 || strcmp(argv[1], "/u")==0) {//toupperodds
            toupperodds(argv[2], &buf, SIZE);
            printf("Измененная строка %s\n", buf);
        } else if (strcmp(argv[1], "-n")==0 || strcmp(argv[1], "/n")==0) {//flag_n        
            flag_n(argv[2], &buf, SIZE);
            printf("Измененная строка %s\n", buf);
        } else printf("Неправильный флаг или число аргументов\n");
    }
    else if (argc == 4) {
        if (strcmp(argv[1], "-c")==0 || strcmp(argv[1], "/c")==0) {//concatenation
            concatenation(argv[2], argv[3], &buf, SIZE);
            printf("Конкатенация строк %s\n", buf);
        } else printf("Неправильный флаг или число аргументов\n");
    }
    else printf("Неправильное число аргументов\n");
    //usage();
    free(buf);
    return 0;
}