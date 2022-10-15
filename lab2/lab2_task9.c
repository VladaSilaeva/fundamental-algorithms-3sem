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

int sum_base(char** str, int *first, int base, int count, ...){
    if (base<2||base>36) return bad_base;
    if (count<0) count = 0;
    va_list l;
    char **nums, *p;
    int *len_nums, j_digit=0, cur_digit=0, i=0, flag=0, max_len=0;
    nums = (char**)malloc(count*sizeof(char*));
    if (!nums) return bad_alloc;
    len_nums = (int*)malloc(count*sizeof(int));
    if (!len_nums) {free(nums); return bad_alloc;}

    va_start(l, count);
    for (int i=0; i<count; i++){
        nums[i] = va_arg(l, char*);
        len_nums[i] = len(nums[i]);
        if (max_len<len_nums[i]) max_len=len_nums[i];
    }
    va_end(l);
    p =*str+*first;
    *(p--)=0;
    for (; i<*first; i++){
        if (i>max_len-1 && cur_digit<0){
            for (int j=1; j<i; j++){
                *(p+j) = int2char(base, base-char2int(base, *(p+j))-1, &flag);
            }
            *(p+i) = int2char(base, base-char2int(base, *(p+i)), &flag);
            *p='-';
            cur_digit=0;
            break;
        }
        for (int j=0; j<count; j++){
            if (len_nums[j]<i+1) continue;
            j_digit = char2int(base, nums[j][len_nums[j]-1-i]);
            if (j_digit<-1) {free(nums); free(len_nums); return not_a_base_num;}
            else if (j_digit>0) cur_digit += j_digit*((nums[j][0]=='-')?-1:1);
        }
        *p=int2char(base, cur_digit % base, &flag);
        if (flag==not_a_digit) {
            *p=int2char(base, cur_digit % base + base, &flag);
            cur_digit-=base;
        }
        cur_digit /= base;
        p--;
        if(i>max_len-1 &&!cur_digit) break;
    }
    free(nums);
    free(len_nums);
    if (cur_digit) return insufficient_len;
    int k=0, sign=0;
    if (*(p++)=='-') sign=1;
    while(*(p+k)=='0'){
        k++;
    }
    if (sign) {
        *(p+k-1) = '-';
    }
    *first = *first-1-i+k;
    return OK;
}

int main(int argc, char **argv)
{
    int count = 5, size=20, first, base=3, flag;
    char *res, *nums[] = {"0000000000", "9999", "-9", "0", "0"};
    res = (char*)malloc(size*sizeof(char));
    first=size-1;
    flag = sum_base(&res, &first, base, count, nums[0], nums[1], nums[2], nums[3], nums[4]);
    if(flag!=0) {
        printf("cant calculate\n");
        return 0;
    }
    printf("(base=%d)\n", base);
    if (!res) return 0;
    for (int i=0; i<count; i++){
        printf("%10s\n", nums[i]);
    }
    printf("--------------------\n");
    printf("%10s\n", res+first);
    free(res);
    return 0;
}