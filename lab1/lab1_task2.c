#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define EPS 0.000001


void usage(){
    printf("Через аргументы командной строки в программу подается флаг, который определяет \n");
    printf("действие, и набор чисел. Флаг начинается с символа “-” или “/”. Необходимо \n");
    printf("проверять соответствие количества параметров введенному флагу. Программа \n");
    printf("распознает следующие флаги:\n");
    printf("\ti) -q вводимые три параметра являются коэффициентами квадратного уравнения,\n");
    printf("необходимо вывести решения этого уравнения при всевозможных значениях параметров;\n");
    printf("\tii) -m необходимо задать два ненулевых целых числа, после чего определить, \n");
    printf("кратно ли первое число второму;\n");
    printf("\tiii) -t считывает 3 ненулевых значения и проверяет, могут ли они быть сторонами \n");
    printf("прямоугольного треугольника.\n");
}

int strtodouble (char *str, double*d){
    int i=0, num1=0, num2=0, _num, isDot=0, neg=1, k=0;
    *d = 0.0;
    if (str[i] == '-') {
        neg = -1;
        i++;
    }
    else if (str[i] == '+') i++;
    do {
        if (!isdigit(str[i])) {
            if ((str[i] == '.')||(str[i] == ',')) isDot=1-isDot;
            if (!isDot) return -1;
        }
        else {
            if(isDot){
                _num = num2*10+str[i]-'0';
                k++;
                if (_num<num2) break;
                num2 = _num;
            } else {
                _num = num1*10+str[i]-'0';
                if (_num<num1) return -2;
                num1 = _num;
            }
        }
        i++;
    } while(str[i]);
    *d = (double)num2;
    for (;k>0;k--){
        *d /= 10;
    }
    *d += (double)num1;
    *d *= neg;
    return 0;

}

int strtoint(char* str, int*num) {
    int i=0, _num=0, neg=1;
    *num = 0;
    if (str[i] == '-') {
        neg = -1;
        i++;
    }
    else if (str[i] == '+') i++;
    do {
        if (!isdigit(str[i])) return -1;
        _num = *num*10+str[i]-'0';
        if (_num<0) return -2;
        *num = _num;
        i++;
    } while(str[i]);
    *num *= neg;
    return 0;
}

int quadratic_equation(double a, double b, double c, double **ans){
    double D;
    if (abs(a)<EPS) return -1;
    D = b*b-4*a*c;
    if (D<0) return 0;
    else if (abs(D)<EPS) {
        *ans = (double*)malloc(sizeof(double*));
        **ans = -b/2/a;
        return 1;
    }
    else {
        *ans = (double*)malloc(2*sizeof(double*));
        D = sqrt(D);
        (*ans)[0] = (-b-D)/2/a;
        (*ans)[1] = (-b+D)/2/a;
        return 2;
    }
    return 0;
}

int is_rect_triangle(double a, double b, double c){
    double A=a*a, B=b*b, C=c*c;
    if (((abs(A+B-C)<EPS)||(abs(B+C-A)<EPS)||(abs(C+A-B)<EPS))&&(a>0)&&(b>0)&&(c>0)) return 1;
    return 0;
}

int is_multiple(int n1, int n2){
    if (!(n1)||!(n2)) return -1;
    return n1%n2 == 0;
}
int main(int argc, char **argv)
{
    int flag, n[2];
    double *ans=NULL, d[3];
    if (argc == 5) {
        for (int i=0; i<3; i++){
            flag = strtodouble(argv[i+2], &d[i]);
            if (flag<0){
                if (flag == -1) printf("Введено не число\n");
                else printf("Слишком большое число\n");
                return 0;
            }
        }
        if (strcmp(argv[1], "-q")==0 || strcmp(argv[1], "/q")==0) {
            flag = quadratic_equation(d[0], d[1], d[2], &ans);
            if (flag==-1) printf("Не является квадратным уравнением\n");
            else if (flag==0) printf("Нет корней\n");
            else if (flag==1) printf("Один корень: x=%.5f", *ans);
            else if (flag==2) printf("Два корня: x1=%.5f, x2=%.5f\n", ans[0], ans[1]);
            free(ans);
            return 0;
        } else if (strcmp(argv[1], "-t")==0 || strcmp(argv[1], "/t")==0) {
            flag = is_rect_triangle(d[0], d[1], d[2]);
            if (flag) printf("Является прямоугольным треугольником\n");
            else printf("Не является прямоугольным треугольником\n");
            return 0;
        } 
        printf("Неправильный флаг\n");
    }
    else if (argc == 4){
        for (int i=0; i<2; i++){
            flag = strtoint(argv[i+2], &n[i]);
            if (flag<0){
                if (flag == -1) printf("Введено не число\n");
                else printf("Слишком большое число\n");
                return 0;
            }
        }
        if (strcmp(argv[1], "-m")==0 || strcmp(argv[1], "/m")==0) {
            flag = is_multiple(n[0], n[1]);
            if (flag==-1) printf("Одно из чисел равно нулю\n");
            else if (flag) printf("Первое число кратно второму\n");
            else printf("Первое число не кратно второму\n");
            return 0;
        }
        printf("Неправильный флаг\n");
    }
    else printf("Неправильное количество аргументов\n");
    usage();
    return 0;
}