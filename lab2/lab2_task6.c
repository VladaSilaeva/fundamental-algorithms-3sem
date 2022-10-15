#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#define cant_open_file -2
#define not_found -1

int str_search(const char* str, const char* f_name){
    FILE* fin = fopen(f_name, "r");
    int j_in_str=0, i_first=-1, i_in_file=0;
    if (!fin) return cant_open_file;
    if (!str[0]) {fclose(fin); return 0;}
    while(!feof(fin)) {
        if (fgetc(fin)==str[j_in_str]) {
            if (i_first==-1) i_first = i_in_file;
            j_in_str++;            
        }
        else {
            if (!str[j_in_str]) {fclose(fin); return i_first;}
            j_in_str=0;
            i_first=-1;
        }
        i_in_file++;
    }
    fclose(fin);
    return not_found;
}

int* str_search_in_files(const char* str, int count, ...){
    va_list l;
    int *ans = (int*)malloc(count*sizeof(int));
    if (!ans) return NULL;
    va_start(l, count);
    for (int i=0; i<count; i++){
        ans[i] = str_search(str, va_arg(l, char*));
    }
    va_end(l);
    return ans;
}

int main(int argc, char **argv)
{
    int *ans, count = 5;
    char *f_names[] = {"1.txt", "2.txt", "3.txt", "4.txt", "5.txt"};
    ans = str_search_in_files("", count, f_names[0], f_names[1], f_names[2], f_names[3], f_names[4]);
    if (!ans) return 0;
    for (int i=0; i<count; i++){
        if (ans[i] == cant_open_file) {
            printf("Не получилось открыть файл `%s`\n", f_names[i]);
        }
        else if (ans[i] == not_found) {
            printf("Подстрока не найдена в фале `%s`\n", f_names[i]);
        }
        else {
            printf("Первое вхождение подстроки в файл `%s` %d\n", f_names[i], ans[i]);
        }
    }
    free(ans);
    return 0;
}