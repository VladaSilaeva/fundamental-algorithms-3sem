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

typedef struct Point{
    double x;
    double y;
} Point;

void f(Point * p, double x, double y){
    p->x=x;
    p->y=y;
}

int isconvex(int count, ...){
    va_list l;
    Point P0, P1, A, B, C;
    double k=0.0;
    int direction = 0;
    if (count < 3) return -1;
    va_start(l, count);
    A = va_arg(l, Point);
    B = va_arg(l, Point);
    P0 = A; P1 = B;
    for (int i=2; i<count; i++) {
        C = va_arg(l, Point);
        k = (B.x-A.x)*(C.y-B.y)-(B.y-A.y)*(C.x-B.x);
        printf("A(%.2f; %.2f) B(%.2f; %.2f) C(%.2f; %.2f)\t\t\t\t", A.x,A.y, B.x,B.y, C.x,C.y);
        printf("AB(%.2f; %.2f) BC(%.2f; %.2f)\tk=%f\n", (B.x-A.x), (B.y-A.y), (C.x-B.x), (C.y-B.y), k);
        if (k < -EPS) {
            if (direction > 0) return 0;
            else direction = -1;
        }
        else if (k > EPS) {
            if (direction < 0) return 0;
            else direction = 1;
        }
        A = B;
        B = C;
    }
    C = P0;
    k = (B.x-A.x)*(C.y-B.y)-(B.y-A.y)*(C.x-B.x);
    printf("A(%.2f; %.2f) B(%.2f; %.2f) C(%.2f; %.2f)\t\t\t\t", A.x,A.y, B.x,B.y, C.x,C.y);
    printf("AB(%.2f; %.2f) BC(%.2f; %.2f)\tk=%f\n", (B.x-A.x), (B.y-A.y), (C.x-B.x), (C.y-B.y), k);
    if (k < -EPS) {
        if (direction > 0) return 0;
        else direction = -1;
    }
    else if (k > EPS) {
        if (direction < 0) return 0;
        else direction = 1;
    }
    A = B;
    B = C;
    C = P1;
    k = (B.x-A.x)*(C.y-B.y)-(B.y-A.y)*(C.x-B.x);
    printf("A(%.2f; %.2f) B(%.2f; %.2f) C(%.2f; %.2f)\t\t\t\t", A.x,A.y, B.x,B.y, C.x,C.y);
    printf("AB(%.2f; %.2f) BC(%.2f; %.2f)\tk=%f\n", (B.x-A.x), (B.y-A.y), (C.x-B.x), (C.y-B.y), k);
    if (k < -EPS) {
        if (direction > 0) return 0;
        else direction = -1;
    }
    else if (k > EPS) {
        if (direction < 0) return 0;
        else direction = 1;
    }
    va_end(l);
    return 1;
}

double gorner(int n, double x, ...){
    va_list l;
    double res;
    if (n < 0) return NAN;
    va_start(l, x);
    res = va_arg(l, double);
    for (int i=0; i<n; i++) {
        res= res*x + va_arg(l, double);
    }
    va_end(l);
    return res;
}

int main(int argc, char **argv){
    //Point polygon[5] = {{-2.91, 6.14}, {1.97, 6.78}, {5.29, 3.74}, {3.05, -1.28}, {-3.43, 1.06}};
    Point polygon[5] = {{1.71, 1.12}, {1.71, 1.12}, {5.29, 3.74}, {3.05, -1.28}, {-3.43, 1.06}};
    double x, y, x0, polynomial[5];
    if (argc == 2) {
        if (strcmp(argv[1], "-c")==0 || strcmp(argv[1], "/c")==0) {//is convex?
            if (isconvex(4, polygon[1], polygon[2], polygon[3], polygon[4])){
                printf("Многоугольник выпуклый\n");
            }
            else {
                printf("Многоугольник не выпуклый\n");
            }

        } else if (strcmp(argv[1], "-g")==0 || strcmp(argv[1], "/g")==0) {//gorner
            printf("Введите коэффициенты многочлена пятой степени\n");
            for (int i=0; i<6; i++){
                scanf("%f %f", &polynomial[i]);
            }
            printf("Введите значение x0\n");
            scanf("%f", &x0);
            printf("Значение многочлена в точке %f\n", gorner(5, x0, polynomial[0], polynomial[1], polynomial[2], polynomial[3], polynomial[4]));
        }
    }
    return 0;
}