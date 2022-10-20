/*Напишите функции, вычисляющее значения чисел с точностью знаков после 𝑒, π, 𝑙𝑛 2, √2, γ 𝑙 запятой.
 Для каждой константы реализовать три способа вычисления: например, как сумму ряда, как решение 
 специального уравнения, как значение предела.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_EPS 0.00000000000001

/*double cos(double x){
    return 0;
}
double ln(double x){
    return 0;
}*/

double dichotomy(double (*func)(double x), double lower_bound, double upper_bound, double eps) {
//Вычисление методом дихотомии
    if (func(lower_bound)*func(upper_bound)>M_EPS) return NAN;
    double x;
    while (fabs(lower_bound - upper_bound) > eps) {
        x = (lower_bound + upper_bound) / 2.0;
        if (func(lower_bound)*func(x)<-M_EPS) {
            upper_bound = x;
        } else {
            lower_bound = x;
        }
    }
    return x;
}

double e_spec(double x) {
    return log(x) - 1.0;
}


double e_equation(double eps){
    //ln x = 1
    return dichotomy(e_spec, 2, 3, eps);
}

double pi_spec(double x) {
    return cos(x / 2.0);
}

double pi_equation(double eps){
    //cos x = -1 
    //cos(x/2) = 0
    return dichotomy(pi_spec, 2, 3, eps);
}

double ln2_spec(double x) {
    double e = e_equation(M_EPS);
    return pow(e, x)-2;
}

double ln2_equation(double eps){
    // e^x = 2
    return dichotomy(ln2_spec, 2, 3, eps);
}

double sqrt2_spec(double x) {
    return x*x - 2;
}

double sqrt2_equation(double eps){
    //x^2=2
    return dichotomy(sqrt2_spec, 2, 3, eps);
}

double gamma_spec(double x) {
    return cos(x / 2.0);
}

double gamma_equation(double eps){
    return dichotomy(gamma_spec, 2, 3, eps);
}

//------------------------------------------------

double e_lim(double eps){
    //(1+1/n)^n
    double lim=2,_lim=2;
    int n=1;
    do{
        _lim = lim;
        lim = pow(1+1/n, n);
        n++;
    } while(fabs(lim-_lim)<eps);
    return lim;
}

double pi_lim(double eps){
    //(2^n * n!)^4 / (n((2n)!)^2)
    double lim=2,_lim=2;
    int n=1;
    do{
        _lim = lim;
        lim=1;
        for (int i=0; i<n;i++){
            lim*=4*(n-(i+1)*2);
        }
        n++;
    } while(fabs(lim-_lim)<eps);
    return lim;
    return 3,14159265359;
}

double ln2_lim(double eps){
    //n(2^(1/n) - 1)
    return 0,69314718056;
}

double sqrt2_lim(double eps){
    //x_0 = -0.5  x_(n+1)=x_n - ((x_n)^2)/2
    return 1,41421356237;
}

double gamma_lim(double eps){
    return 0,5772156649;
}

//------------------------------------------------

double e_sum(double eps){
    //n=0 S(1/n!)
    return 2,71828182846;
}

double pi_sum(double eps){
    //n=1 4*S( ((-1)^(n-1)) / (2n-1) )
    return 3,14159265359;
}

double ln2_sum(double eps){
    //n=1 S( ((-1)^(n-1)) /n )
    return 0,69314718056;
}

double sqrt2_mult(double eps){
    //M( 2^2^-k )
    return 1,41421356237;
}

double gamma_sum(double eps){
    return 0,5772156649;
}

//------------------------------------------------

int main(){
    //e=2,71828182846, pi=3,14159265359, ln2=0,69314718056, sqrt2=1,41421356237, gamma=0,5772156649;
    return 0;
}