/* Реализуйте функцию перевода целого числа из десятичной системы счисления 
в систему счисления с основанием 2^𝑟,  𝑟=1,...,5 (параметрами функции являются
переводимое число и значение r - степень двойки; параметры необходимо проверить
на корректность). При реализации функции разрешается использовать битовые 
операции и операции обращения к памяти, запрещается использовать стандартные 
арифметические операции. Продемонстрируйте работу реализованной функции */
#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define INCORRECT_EXPONENT -1
#define NOT_EMPTY_RES -2 
#define MEMORY_ERROR -3

int incr(int n) {
    int i=1;
    if (n == 1) return 2;
    if (n < 0) {
        //printf("%d\n", i);
        while (!(n&i)) {
            //printf("%d\n", i);
            //printf("(%d&%d)=%d\n", n, i, (n&i));
            n ^= i;
            i <<= 1;
        }
        n ^= i;
        return n;
    }
    else {
        while (n&i){
            n ^= i;
            i >>= 1;
        }
        n ^= i;
    }
    return n;
}

int dec_to_pow_of_two(int num, int r, char** res) {
    int digit=0;
    if ((r<1)||(r>5)) return INCORRECT_EXPONENT;
    if (*res) return NOT_EMPTY_RES;
    *res=(char*)malloc(33*sizeof(char));
    if (!*res) return MEMORY_ERROR;
    
    while (!((digit<<1)>>r)){
        digit = 1 | (digit<<1);
    }
    int d = digit;
    while(num){
        printf("%d (%d)", num&digit, num);
        num >>= r;
    }
    printf("\n");
    return OK;
}


int main() {
    char* res[] = {NULL, NULL};
    for (int i=-10; i<10; i++) printf("%d+1=%d\n", i, incr(i));
    //dec_to_pow_of_two(10, 2, &res[0]);
    //dec_to_pow_of_two(15, 2, &res[1]);
    return 0;
}