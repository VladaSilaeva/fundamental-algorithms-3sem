#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void fill_arr_rand(int N, int **arr, int min, int max){
    for (int i=0; i<N; i++){
        (*arr)[i] = min + rand()%(max - min + 1);
    }
}

int* find_min(int *arr, int n){
    int i_min = 0;
    for (int i=1; i<n; i++){
        if (arr[i]<arr[i_min]) i_min = i;
    }
    return arr+i_min;
}

int* find_max(int *arr, int n){
    int i_max = 0;
    for (int i=1; i<n; i++){
        if (arr[i]>arr[i_max]) i_max = i;
    }
    return arr+i_max;
}

void swap(int* a, int* b){
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void uniq(int* arr, int** u_arr, int N, int* M){
    int isuniq=1;
    *M=0;
    int *p = (int*)realloc(*u_arr, N*sizeof(int));
    if(!p) return;
    *u_arr = p;
    for (int i=0; i<N; i++){
        isuniq=1;
        for (int j=0; j<i; j++){
            if (arr[i] == arr[j]) {
                isuniq=0;
            }
        }
        if (isuniq){
            *(p++) = arr[i];
            (*M)++;
        }
    }
}

int main(int argc, char **argv){
    srand(time(NULL));
    int *arr=NULL, *u_arr=NULL, n=5, m=0;
    arr = (int*)malloc(n*sizeof(int));
    fill_arr_rand(n, &arr, 0, 2);
    for (int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    if (argc == 2) {
        if (strcmp(argv[1], "-m")==0 || strcmp(argv[1], "/m")==0) {//swap min max
            int *min_el=find_min(arr, n), *max_el=find_max(arr, n);
            printf("%d %d\n", *min_el, *max_el);
            swap(min_el, max_el);
            for (int i=0; i<n; i++) printf("%d ", arr[i]);
            printf("\n");
        } else if (strcmp(argv[1], "-u")==0 || strcmp(argv[1], "/u")==0) {//unique
            uniq(arr, &u_arr, n, &m);
            for (int i=0; i<m; i++) printf("%d ", u_arr[i]);
            printf("\n");
        }
    }
    return 0;
}
