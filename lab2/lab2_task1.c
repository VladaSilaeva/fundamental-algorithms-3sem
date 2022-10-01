#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_arr_rand(int N, int **arr, int min, int max){
    for (int i=0; i<N; i++){
        (*arr)[i] = min + rand()%(max - min + 1);
    }
}

void print_arr(int N, int *arr){
    for (int i=0; i<N; i++) printf("%d\t", arr[i]);
    printf("\n");
}

int main(){
    srand(time(NULL));
    int *A, *B, *C, N, M;
    scanf("%d", N);
    scanf("%d", M);
    A = (int*)malloc(N*sizeof(int));
    C = (int*)malloc(N*sizeof(int));
    B = (int*)malloc(M*sizeof(int));
    fill_arr_rand(N, &A, 0, RAND_MAX);
    fill_arr_rand(M, &B, 0, RAND_MAX);
    for (int i=0; i<N; i++){
        if (i>M-1) C[i] = A[i]+B[M-1];
        else C[i] = A[i]+B[i];
    }
    print_arr(N, A);
    print_arr(M, B);
    print_arr(N, C);
    free(A); 
    free(B); 
    free(C);
    return 0;
}