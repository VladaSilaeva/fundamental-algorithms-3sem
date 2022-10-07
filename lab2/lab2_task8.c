#include <stdio.h>
#include <math.h>
#define M_EPS 0.00000000000001

double m_eps() {
//Вычисление машинного эпсилон
  double eps = 1.0;
  while (1.0 + eps / 2.0 > 1.0)
    eps /= 2.0;
  return eps;
}

double dichotomy(double (*func)(double x), double a, double b, int l) {
//Вычисление методом дихотомии
  if ((func(a)<-M_EPS && func(b)<-M_EPS)||(func(a)>M_EPS && func(b)>M_EPS)) return NAN;
  double x, e = pow(10, -l-1);
  while (fabs(a - b) > e) {
    x = (a + b) / 2.0;
    if ((func(a)<-M_EPS && func(x)>M_EPS)||(func(a)>M_EPS && func(x)<-M_EPS)) {
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
  return cos(x / 2.0);
}

double func3(double x) {
  return cos(x) + 1.0;
}

void printfline(const char* func_str, double a, double b, int l, double f){
  printf("| %-10.10s = 0 | [%.1f, %.1f] |", func_str, a, b);
  if (_isnan(f)) printf("       NaN         |\n");
  else printf(" %.*f %*s|\n", l, f, 15-l, "");
}

int main() {
  double a1 = 2.0, b1 = 3.0;
  double a2 = 2.0, b2 = 4.0;
  double a3 = 2.0, b3 = 4.0;
  int l1=13, l2=10, l3=13;
  double f1=0.0, f2=0.0, f3=0.0;
  f1=dichotomy(func1, a1, b1, l1);
  f2=dichotomy(func2, a2, b2, l2);
  f3=dichotomy(func3, a3, b3, l3);
  printf("---------------------------------------------------\n");
  printf("|    F(x) = 0    |  Отрезок   | Метод  дихотомии  |\n");
  printf("|-------------------------------------------------|\n");
  printfline("ln(x) - 1", a1, b1, l1, f1);
  printfline("cos(x/2)", a2, b2, l2, f2);
  printfline("cos(x) + 1", a3, b3, l3, f3);
  printf("---------------------------------------------------\n");
  return 0;
}