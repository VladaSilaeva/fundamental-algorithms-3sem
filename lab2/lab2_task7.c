/*Реализовать функцию с переменным числом аргументов, принимающую координаты точек многоугольника 
и вычисляющую, является ли этот многоугольник выпуклым.

Реализовать функцию с переменным числом аргументов, которая будет находить значения многочлена 
степени n в заданной точке. Входными параметрами являются точка, в которой определяется значение 
многочлена, степень многочлена и его коэффициенты.
-2.63 5.56
2.69 5.68
4.35 1.92
1.51 -1.9
-2.81 -1.56 // 2 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#define EPS 0.00000000000001
#define bad_alloc -2

typedef struct Point{
    double x;
    double y;
} Point;


int isconvex(int count, ...){
    va_list l;
    Point *polygon=NULL;
    double k=0.0;
    int direction = 0;
    if (count < 3) return -1;
    polygon=(Point*)malloc((count+2)*sizeof(Point));
    if (!polygon) return bad_alloc;
    va_start(l, count);
    for (int i=0; i<count; i++) {
        polygon[i] = va_arg(l, Point);
    }
    va_end(l);
    polygon[count].x = polygon[0].x; polygon[count].y = polygon[0].y;
    polygon[count+1].x = polygon[1].x; polygon[count+1].y = polygon[1].y;
    for (int i=0; i<count; i++) {
        k = (polygon[i+1].x-polygon[i].x)*(polygon[i+2].y-polygon[i+1].y)-(polygon[i+1].y-polygon[i].y)*(polygon[i+2].x-polygon[i+1].x);
        if (k < -EPS) {
            if (direction > 0) {
                free(polygon);
                return 0;
            }
            else direction = -1;
        }
        else if (k > EPS) {
            if (direction < 0) {
                free(polygon);
                return 0;
            }
            else direction = 1;
        }
    }
    free(polygon);
    return 1;
}

double gorner(int n, double x, ...){
    va_list l;
    double res;
    if (n < 0) return NAN;
    va_start(l, x);
    res = va_arg(l, double);
    for (int i=0; i<n; i++) {
        res = res*x + va_arg(l, double);
    }
    va_end(l);
    return res;
}

int main(int argc, char **argv){
    Point polygon[] = {{-2.91, 6.14}, {1.97, 6.78}, {1.71, 1.12}, {5.29, 3.74}, {3.05, -1.28}, {-3.43, 1.06}};
    double x, y, x0, polynomial[5];
    if (argc == 2) {
        if (strcmp(argv[1], "-c")==0 || strcmp(argv[1], "/c")==0) {//is convex?
            if (isconvex(4, polygon[2], polygon[3], polygon[4], polygon[5])){
                printf("Многоугольник выпуклый\n");
            }
            else {
                printf("Многоугольник не выпуклый\n");
            }
        } else if (strcmp(argv[1], "-g")==0 || strcmp(argv[1], "/g")==0) {//gorner
            printf("Значение многочлена в точке %f\n", gorner(5, 2.0, 1.0, 1.0 , 1.0, 1.0, 1.0, 1.0));
        }
    }
    return 0;
}