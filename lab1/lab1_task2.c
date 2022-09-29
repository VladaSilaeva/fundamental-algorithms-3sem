#include <stdio.h>

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
    int i=0, num1=0, num2=0, _num, isDot=0, Neg=1, k=0;
    *d=0.0;
    if (str[i] == '-') {
        Neg=-1;
        i++;
    }
    else if (str[i] == '+') i++;
    do {
        if (!isdigit(str[i])) {
            if (((str[i] == '.')||(str[i] == ','))&&!isDot) isDot=1;
            else return -1;
        }
        if(isDot){
            _num = num2*10+str[i]-'0';
            k++;
            if (_num<num2) return -2;
        } else {
            _num = num1*10+str[i]-'0';
            if (_num<num1) return -2;
        }
        i++;
    } while(str[i]);
    *d=(double)num2;
    for (;k>0;k--){
        *d/=10;
    }
    *d+=(double)num1;
    *d*=Neg;
    return 0;

}

int flag_q(double a, double b, double c){
    return 0;
}

int main(int argc, char **argv)
{
    int num = 0, *res=NULL, N=0, flag=0;
    if (argc == 4) {
        if (strcmp(argv[2], "-q")==0 || strcmp(argv[2], "/q")==0) {
            return 0;
        } else if (strcmp(argv[2], "-t")==0 || strcmp(argv[2], "/t")==0) {
            return 0;
        } 
        printf("incorrect flag\n");
    }
    else if (argc == 3){
        if (strcmp(argv[2], "-m")==0 || strcmp(argv[2], "/m")==0) {
            return 0;
        }
        printf("incorrect flag\n");
    }
    else printf("incorrect number of arguments\n");
    usage();
    return 0;
}