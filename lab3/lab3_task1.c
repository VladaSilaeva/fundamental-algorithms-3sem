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
#define TOO_SHORT_SIZE_OF_RES -2 

int incr(int n) { //incr(2147483647)=-2147483648
    int i=1;
    while (n&i){
        n ^= i;
        i <<= 1;
    }
    n ^= i;
    return n;
}

int decr(int n) { //decr(-2147483648)=2147483647
    int i=1;
    while (!(n&i)&&(i)){
        n ^= i;
        i <<= 1;
    }
    n ^= i;
    return n;
}

int dec_to_pow_of_two(int num, int r, char* res, int size) {
    int mask=0, i=0, sign=0;
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                     'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                     'U', 'V', 'W', 'X', 'Y', 'Z'};
    if ((r<1)||(r>5)) return INCORRECT_EXPONENT;
    while (!((mask<<1)>>r)){
        mask = 1 | (mask<<1);
    }
    if (num<0) {
        sign=1;
        num=incr(~(num));
    }
    int n = num;
    while(num){
        res[i] = digits[num&mask];
        num >>= r;
        i = incr(i);
        if (i==33) break;
    }
    if (!i) {res[0]='0'; res[1]=0; return OK;}
    if ((i > size)||(sign&&(i==size))) return TOO_SHORT_SIZE_OF_RES;
    if (sign) {
        for (int j=i, k=0; k<j; j=decr(j), k=incr(k)){
            res[j] ^= res[k];
            res[k] ^= res[j];
            res[j] ^= res[k];
        }
        res[0]='-';
        res[incr(i)] = 0;
    } else {
        for (int j=decr(i), k=0; k<j; j=decr(j), k=incr(k)){
            res[j] ^= res[k];
            res[k] ^= res[j];
            res[j] ^= res[k];
        }
        res[i] = 0;
    }
    return OK;
}


int main() {
    int size=33, num1=31, num2=-31;
    char res[size];
    for (int i=0; i<33; i++) res[i]=0;
    printf("%d\t\t(10)\n", num1);
    for (int i=1; i<6; i=incr(i)) {
        dec_to_pow_of_two(num1, i, res, size);
        printf("%s\t\t(%d)\n", res, 1<<i);
    }
    printf("\n%d\t\t(10)\n", num2);
    for (int i=1; i<6; i=incr(i)) {
        dec_to_pow_of_two(num2, i, res, size);
        printf("%s\t\t(%d)\n", res, 1<<i);
    }
    printf("\n0\t\t(10)\n");
    for (int i=1; i<6; i=incr(i)) {
        dec_to_pow_of_two(0, i, res, size);
        printf("%s\t\t(%d)\n", res, 1<<i);
    }
}
/* A(10) B(11) C(12) D(13) E(14) F(15) G(16) H(17) I(18) J(19)
   K(20) L(21) M(22) N(23) O(24) P(25) Q(26) R(27) S(28) T(29)
   U(30) V(31) W(32) X(33) Y(34) Z(35)*/