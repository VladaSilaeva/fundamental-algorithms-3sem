#include <stdio.h>
#include <math.h>

double dichotomy(double (*func)(double x), double a, double b, int l) {
/*Вычисление методом дихотомии*/
  double x, e=pow(10, -l);
  printf("%.16f\n", e);
  printf("[%f, %f, %f]\n", a, 0.0, b);
  while (fabs(a - b) > e) {
    x = (a + b) / 2.0;
    //if (fabs(func(x)) < e) break;
    printf("[%f, %f, %f] %f %f %f\n", a, x, b, func(a), func(x), func(b));
    if ((func(a)<e && func(x)>-e)||(func(a)>-e && func(x)<e)) {
      b = x;
    } else {
      a = x;
    }
  }
  return x;
}

double func1(double x) {
  return log(x) - 1.0;
}

double func2(double x) {
  return cos(x/2.0);
}

int main() {
  double a1 = 2.0, b1 = 3.0;
  double a2 = 2.0, b2 = 4.0;
  int l1=14, l2=14;
  double f1=dichotomy(func1, a1, b1, l1), f2=dichotomy(func2, a2, b2, l2);
  //printf("%.20f\n", func2(3.141592653589793238));
  printf("------------------------------------------------------\n");
  printf("|    F(x) = 0   |  Отрезок   | Метод %*s дихотомии |\n", fmax(l1, l2)>15?(int)fmax(l1, l2)-15:0, "");
  printf("|-----------------------------------------------------\n");
  printf("| ln(x) - 1 = 0 | [%.1f, %.1f] | %.*f |\n", a1, b1, l1, f1);
  printf("| cos(x/2)  = 0 | [%.1f, %.1f] | %.*f |\n", a2, b2, l2, f2);
  printf("-------------------------------------------------------\n");
  return 0;
}