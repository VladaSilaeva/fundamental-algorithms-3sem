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

int str_to_uns_num(char* str, int*num) {
    int i=0, num2=0;
    *num=0;
    do {
        if (!isdigit(str[i])) return -1;
        num2 = *num*10+str[i]-'0';
        if (num2<0) return -2;
        *num=num2;
        i++;
    } while(str[i]);
    return 0;
}

int multiples(int num, int** mults) {
    int N=0, *mults2;
    if (num < 1) return 0;
    N = 100/num;
    mults2 = (int*)realloc(*mults, N*sizeof(int));
    if (!mults2) {
        free(mults);
        return -1;
    }
    *mults = mults2;
    for (int i=0, mult=num; mult<101; i++, mult+=num) (*mults)[i] = mult;
    return N;
}

int isprime(int num){
    if (num<2) return 0;
    if (num<4) return 1;
    if (!(num%2)) return 0;
    for (int div=3; div<num/2+1; div+=2){
        if (!(num%div)) return 0;
    }
    return 1;
}

void split(char *str){
    while(*str){
        printf("%c ", *str++);
    }
    printf("\n");
}

int powers(int num){
    int nums[10], cur_n=1;
    if ((num > 10)||(num<0)) return -1;
    for (int i=0; i<10; i++) nums[i] = 1;
    for (int k=1; k<num; k++){
        for (int i=0; i<10; i++){
            cur_n = nums[i]*(i+1);
            if (cur_n<nums[i]) return -1;
            nums[i]=cur_n;
            printf("%d ", cur_n);
        }
        printf("\n");
    }
    return 0;
}

int sum(int num){
    int s=0;
    if (num>0) s=num*(num+1)/2;
    if (s<0) s = -1;
    return s;
}

int fact(int num){
    int f=1, _f=1;
    if (num<0) return -1;
    if (num<2) return f;
    for (int i=2; i<num+1; i++){
        _f = f*i;
        if (_f<f) return -2;
        f = _f;
    }
    return f;
}

int main(int argc, char **argv)
{
    int num = 0, *res=NULL, N=0, flag=0;
    if (argc == 3) {
        flag = str_to_uns_num(argv[1], &num);
        printf("'%s' %d\n", argv[1], num);
        if (flag < 0) {
            if (flag == -2) printf("num is too large for int type\n");
            else printf("incorrect num\n");
        }
        else {
            if (strcmp(argv[2], "-h")==0 || strcmp(argv[2], "/h")==0) {
                printf("h\n");
                N = multiples(num, &res);
                printf("%d\n", N);
                if (N>0){
                    printf("%d multiples\n", N);
                    for (int i;i<N;i++) printf("%d ", res[i]);
                    printf("\n");
                }
                else if (N==0) printf("no multiples\n");
                else printf("memori error\n");
                return 0;
            } else if (strcmp(argv[2], "-p")==0 || strcmp(argv[2], "/p")==0) {
                printf("p\n");
                flag = isprime(num);
                if (flag) printf("num=%d is prime\n", num);
                else printf("num=%d is not prime\n", num);
                return 0;
            } else if (strcmp(argv[2], "-s")==0 || strcmp(argv[2], "/s")==0) {
                printf("s\n");
                split(argv[1]);
                return 0;
            } else if (strcmp(argv[2], "-e")==0 || strcmp(argv[2], "/e")==0) {
                printf("e\n");
                flag = powers(num);
                if (flag) printf("\nnum > 10\n"); 
                return 0;
            } else if (strcmp(argv[2], "-a")==0 || strcmp(argv[2], "/a")==0) {
                printf("a\n");
                N = sum(num);
                if (N<0) printf("num is too large\n");
                else printf("sum = %d\n", N);
                return 0;
            } else if (strcmp(argv[2], "-f")==0 || strcmp(argv[2], "/f")==0) {
                printf("f\n");
                N=fact(num);
                if (N<0) printf("num is too large\n");
                else printf("fact=%d\n", N);
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
