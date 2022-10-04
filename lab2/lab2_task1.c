#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_arr_rand(int N, int **arr, int min, int max){
    if(N<0) return;
    int*p = (int*)realloc((*arr), N*sizeof(int));
    if (!p) return;
    (*arr) = p;
    for (int i=0; i<N; i++){
        (*arr)[i] = min + rand()%(max - min + 1);
    }
}

void print_arr(int N, int *arr, const char* sep, const char* end){
    if (!arr) {
        printf("NULL%s", end);
        return;
    }
    for (int i=0; i<N; i++) printf("%d%s", arr[i], sep);
    printf("%s", end);
}

int main(){
    srand(time(NULL));
    int *A=NULL, *B=NULL, *C=NULL, N, M;
    printf("Введитете размер массивов через пробел\n");
    scanf("%d %d", &N, &M);
    C = (int*)malloc(N*sizeof(int));
    fill_arr_rand(N, &A, 0, RAND_MAX);
    fill_arr_rand(M, &B, 0, RAND_MAX);
    for (int i=0; i<N; i++){
        if (i>M-1) C[i] = A[i]+B[M-1];
        else C[i] = A[i]+B[i];
    }
    printf("A:"); print_arr(N, A, "\t", "\n");
    printf("B:"); print_arr(M, B, "\t", "\n");
    printf("C:"); print_arr(N, C, "\t", "\n");
    free(A); 
    free(B); 
    free(C);
    return 0;
}