#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void usage() {
    printf("Через аргументы командной строки введите целое положительное число и флаг,\n");
    printf("определяющий действие с этим числом. Флаг начинается с символа \"-\" или \"/\".\n");
    printf("Программа распознаёт следующие флаги:\n");
    printf("\ti) -h вывести в консоль числа в пределах 100, кратные введённому. Если\n");
    printf("таковых нет - вывести соответствующее сообщение;\n");
    printf("\tii) -p определить, является ли введённое число простым или составным;\n");
    printf("\tiii)-s разделяет число на отдельные цифры и выводит отдельно каждую цифру,\n");
    printf("разделяя их пробелом;\n");
    printf("\tiv) -e вывести в консоль числа от 1 до 10, возводя их во все степени от 1\n");
    printf("до заданного числа (для этого флага работает ограничение на вводимое число:\n");
    printf("оно должно быть не больше 10);\n");
    printf("\tv) -a суммирует все числа от 1 до указанного числа включительно;\n");
    printf("\tvi) -f вычисляет факториал введенного числа\n");
}

int str_to_uns_num(char* str) {
    int i=0, num=0, num2=0;
    do {
        if (!isdigit(str[i])) return -1;
        num2 = num*10+str[i]-'0';
        if (num2<0) return -2;
        num=num2;
        i++;
    } while(str[i]);
    return num;
}

int multiples(int num, int* mults) {
    int N=0, *mults2;
    if (num < 1) return 0;
    N = 100/num;
    printf("%d\n", N);
    mults2 = realloc(mults, N*sizeof(int));
    if (!mults2) {
        free(mults);
        return -1;
    }
    mults = mults2;
    for (int i=0, mult=num; mult<100; i++, mult+=num) {
        mults[i] = mult;
        printf("%d %d\n", i, mult);
    }
    return N;
}

int main(int argc, char **argv)
{
    int num = 0, *res=NULL, N=0;
    //for (int i=0; i<argc; i++) printf("'%s'\n", argv[i]);
    //printf("\n");
    if (argc == 3) {
        num = str_to_uns_num(argv[1]);
        //printf("'%s' %d\n", argv[1], num);
        if (num<0) {
            if (num == -2) printf("num is too large for int type\n");
            else printf("incorrect num\n");
        }
        else {
            if (strcmp(argv[2], "-h")==0 || strcmp(argv[2], "/h")==0) {
                printf("h\n");
                N = multiples(num, res);
                if (N>0){
                    printf("N=%d\n", N);
                    for (int i;i<N;i++) printf("%d ", res[i]);
                    printf("\n");
                }
                else if (N==0) printf("no multiples less then 100\n");
                else printf("memori error\n");
                return 0;
            } else if (strcmp(argv[2], "-p")==0 || strcmp(argv[2], "/p")==0) {
                printf("p\n");
                return 0;
            } else if (strcmp(argv[2], "-s")==0 || strcmp(argv[2], "/s")==0) {
                printf("s\n");
                return 0;
            } else if (strcmp(argv[2], "-e")==0 || strcmp(argv[2], "/e")==0) {
                printf("e\n");
                return 0;
            } else if (strcmp(argv[2], "-a")==0 || strcmp(argv[2], "/a")==0) {
                printf("a\n");
                return 0;
            } else if (strcmp(argv[2], "-f")==0 || strcmp(argv[2], "/f")==0) {
                printf("f\n");
                return 0;
            }
            printf("incorrect flag\n");
        }
    }
    else printf("incorrect number of arguments\n");
    printf("%*s%d\n", 100, "", 0);
    usage();
    return 0;
}
