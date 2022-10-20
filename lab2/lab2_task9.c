#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#define OK 0
#define bad_alloc -2
#define bad_base -3
#define not_a_base_num -4
#define not_a_digit -5
#define insufficient_len -6

int len(const char *str) {
    int n=0;
    while(str[n]) n++;
    return n;
}

int max(int a, int b){
    return (a>b)?a:b;
}

int intpow(int a, int b){
  int r = 0;
  if (b < 0) return 0;
  if (b == 0) return 1;
  if (b & 1) return a * intpow(a, b-1);
  r = intpow(a, b>>1);
  return r*r;
}

int char2int(int b, char c){
    if (b<1) return -1;
    if (b<11){
        if ('0'-1<c && c<'0'+b) return c-'0';
    }
    else if (b<37) {
        c = toupper(c);
        if ('0'-1<c && c<'0'+10) return c-'0';
        else if ('A'-1<c && c<'A'+b-10) return 10+c-'A';
    }
    if (c=='-'||c=='+') return -1;
    return -2;
}

char int2char(int b, int d, int*flag){
    *flag=OK;
    if (b<1||b>36) {*flag=bad_base; return 0;}
    if (d<0||d>b-1) {*flag=not_a_digit; return 0;}
    return (d>9)?'A'+d-10:'0'+d;
}

int to_negative(char **num, int base, int base_pow){ //F("345", 10, 5) = -(10^5 - 345) = -99655
    int cur_digit=0, digit=0, flag=OK;
    **num='+';
    for (int j=base_pow; j>0; j--){
        digit = char2int(base, *(*num+j));
        if (digit<-1) return not_a_base_num;
        else if (digit>0) cur_digit -= digit;
        *(*num+j)=int2char(base, cur_digit % base, &flag);
        if (flag==not_a_digit) {
            *(*num+j)=int2char(base, cur_digit % base + base, &flag);
            cur_digit-=base;
        }
        cur_digit /= base;
    }
    **num='-';
    return flag;
}

int del_zeros(char **num, int *first){
    int k=0, sign=0;
    if (*(*num+*first)=='-') sign=1;
    while(*((*num+*first)+sign+k)=='0') k++;
    if(*((*num+*first)+sign+k)==0) k--;
    if (sign) *((*num+*first)+k) = '-';
    *first = *first+k;
    return 0;
}

int increasing_the_num(char** num, int *first, int base, char* num2){
    if (base<2||base>36) return bad_base;
    int l1=len(*num+*first), l2=len(num2), digit=0, cur_digit=0, i=0, flag;
    char *p =*num+*first+l1-1;
    for (; i<*first+l1; i++){
        if (i>max(l1, l2)-1 && cur_digit<0){
            flag = to_negative(&p, base, i);
            if (flag) return flag;
            cur_digit=0;
            break;
        }
        digit=0;
        if (i<l1) digit = char2int(base, *p);
        if (digit<-1) return not_a_base_num;
        else if (digit>0) cur_digit += digit*((*(*num+*first)=='-')?-1:1);
        digit=0;
        if (i<l2) digit = char2int(base, num2[l2-1-i]);
        if (digit<-1) return not_a_base_num;
        else if (digit>0) cur_digit += digit*((num2[0]=='-')?-1:1);

        *p=int2char(base, cur_digit % base, &flag);
        if (flag==not_a_digit) {
            *p=int2char(base, cur_digit % base + base, &flag);
            cur_digit-=base;
        }
        cur_digit /= base;
        p--;
        if(i>max(l1, l2)-1 && !cur_digit) break;
    }
    if (cur_digit) return insufficient_len;
    *first = *first+(l1-1-i);
    del_zeros(num, first);
    return OK;
}

int sum_base(char** str, int *first, int base, int count, ...){
    if (base<2||base>36) return bad_base;
    if (count<0) count = 0;
    va_list l;
    int flag=0;
    char *p=*str+*first;
    *(p--)=0;
    *p='0';
    *first -= 1;
    va_start(l, count);
    for (int i=0; i<count; i++){
        flag = increasing_the_num(str, first, base, va_arg(l, char*));
        if (flag) return flag;
    }
    va_end(l);
    return OK;
}

int main(int argc, char **argv)
{
    int count = 5, size=100, first, base=10, flag;
    char *res, *nums[] = {"-1", "000", "0002", "-3", "2"};
    res = (char*)malloc(size*sizeof(char));
    first=size-1;
    flag = sum_base(&res, &first, base, count, nums[0], nums[1], nums[2], nums[3], nums[4]);
    if(flag!=0) {
        printf("%d cant calculate\n", flag);
        return 0;
    }
    printf("(base=%d)\n", base);
    if (!res) return 0;
    for (int i=0; i<count; i++){
        printf("%10s\n", nums[i]);
    }
    printf("---------------------------------\n");
    printf("%10s\n", res+first);
    free(res);
    return 0;
}