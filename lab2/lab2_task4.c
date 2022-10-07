#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#define EPS 0.00000000000001


double gmean(int count, ...){
    va_list l;
    double res = 1.0;
    va_start(l, count);
    for (int i=0; i<count; i++) res *= va_arg(l, double);
    va_end(l);
    if (res < EPS) return NAN;
    return pow(res, 1./count);
}


double intpow(double a, int b){
  double r = 1.0;
  if (b < 0){
    if (a<EPS) return NAN;
    a = 1.0 / a;
    b = -b;
  }
  if (b == 0) return 1.0;
  if (b & 1) return a * intpow(a, b-1);
  r = intpow(a, b>>1);
  return r*r;
}


int main(int argc, char **argv)
{
    int N = 4;
    double arr[4] = {2.0, 4.0, 8.0, 4.0};
    printf("gmean(%.1f, %.1f, %.1f, %.1f) = %f\n", arr[0], arr[1], arr[2], arr[3], gmean(N, arr[0], arr[1], arr[2], arr[3]));
    printf("pow(%.1f, %d)=%f\n", arr[1], 2, intpow(arr[1], 2));
    printf("pow(%.1f, %d)=%f\n", -arr[1], 3, intpow(-arr[1], 3));
    printf("pow(%.1f, %d)=%f\n", arr[1], -2, intpow(arr[1], -2));
    printf("pow(%.1f, %d)=%f\n", -arr[1], 3, intpow(-arr[1], -3));
    return 0;
}