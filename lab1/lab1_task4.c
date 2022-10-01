/*Дан файл, содержащий некоторую информацию, которая представлена в трех столбцах 
(каждая строка файла содержит три лексемы). Необходимо перезаписать этот файл 
таким образом, чтобы первый столбец стоял на месте второго, второй – на месте 
третьего, а третий – на месте первого.*/
#include <stdio.h>
#include <ctype.h>

#define SIZE 33

int main(int argc, char **argv){
    FILE *fi = NULL, *fo = NULL;
    char ch, _c=0, buf[SIZE], *ptr;
    ptr = buf;
    if (argc!=3) return 0;
    fi = fopen(argv[1], "r");
    if (!fi) {
        printf("Не удается открыть файл '%s' на чтение\n", argv[1]);
        return 0;
    }
    fo = fopen(argv[2], "w");
    if (!fo) {
        printf("Не удается открыть файл '%s' на запись\n", argv[2]);
        return 0;
    }
    while(!feof(fi)){
        ch = fgetc(fi);
        //printf("'%c' %d\n", ch, ch);
        if (isalnum(ch)) *ptr++=ch;
        else if (!isalnum(_c)) {
            *ptr=0;
            printf("\"%s\"\n", buf);
            ptr = buf;
        }
        _c=ch;
    }
    fclose(fi);
    fclose(fo);
    return 0;
}