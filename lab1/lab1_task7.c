/*Заполнить массив фиксированного размера случайными числами. Реализовать поиск максимального 
и минимального элементов, поменять местами максимальный и минимальный элементы массива.*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

void fill_arr_rand(int N, int **arr, int min, int max){
    for (int i=0; i<N; i++){
        (*arr)[i] = min + rand()%(max - min + 1);
    }
}

int main(){
    int arr[SIZE], i_min=0, i_max=0;
    fill_arr_rand(SIZE, &arr, 0, RAND_MAX);
    for (int i=0; i<SIZE; i++){
        printf("%d ", arr[i]);
        if (arr[i]>arr[i_max]) i_max=i;
        if (arr[i]<arr[i_min]) i_min=i;
    }
    arr[i_min] = arr[i_min] + arr[i_max];
    arr[i_max] = arr[i_min] - arr[i_max];
    arr[i_min] = arr[i_min] - arr[i_max];
    for (int i=0; i<SIZE; i++) printf("%d ", arr[i]);
    return 0;
}
