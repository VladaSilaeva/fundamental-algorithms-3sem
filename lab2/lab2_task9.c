#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#define bad_alloc -2
#define not_a_base_num -3
#define bad_base -4
#define insufficient_len -5


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
    return -1;
}

char int2char(int b, int d){
    if (b<1||b>36||d<0||d>b-1) return 0;
    return (d>9)?'A'+d-10:'0'+d;
}

int sum_base(char** str, int *first, int base, int count, ...){
    if (base<2||base>36) return bad_base;
    if (count<0) count = 0;
    va_list l;
    char **nums, *p;
    int *len_nums, j_digit=0, cur_digit=0, i=0;
    nums = (char**)malloc(count*sizeof(char*));
    if (!nums) return bad_alloc;
    len_nums = (int*)malloc(count*sizeof(int));
    if (!len_nums) {free(nums); return bad_alloc;}

    va_start(l, count);
    for (int i=0; i<count; i++){
        nums[i] = va_arg(l, char*);
        len_nums[i] = len(nums[i]);
    }
    va_end(l);
    p =*str+*first;
    *(p--)=0;
    for (; i<*first+1; i++){
        for (int j=0; j<count; j++){
            if (len_nums[j]<i+1) continue;
            j_digit = char2int(base, nums[j][len_nums[j]-1-i]);
            if (j_digit<0) {free(nums); free(len_nums); return not_a_base_num;}
            cur_digit += j_digit;
        }
        *(p--)=int2char(base, cur_digit % base);
        cur_digit /= base;
        if(!cur_digit) break;
    }
    free(nums);
    free(len_nums);
    if (cur_digit) return insufficient_len;
    *first = *first -1- i;
    return 0;
}

int main(int argc, char **argv)
{
    int count = 5, size=10, first, base=16, flag;
    char *res, *nums[] = {"1", "9", "AA", "AB", "8"};
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