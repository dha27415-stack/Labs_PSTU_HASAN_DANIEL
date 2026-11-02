#include <iostream>
#include <cstdio>
#include <clocale>
#include <cmath>

using namespace std;

double factorial(int n) {
    double fact = 1.0;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    setlocale(LC_ALL, "Russian.UTF8");

    int n_terms = 10;
    double sum = 0.0;

    printf("=========================================\n");
    printf(" Лабораторная работа №2. Вариант 23\n");
    printf("=========================================\n\n");
    printf("%-5s | %-20s | %-20s\n", "n", "a_n", "Сумма (S)");
    printf("-----------------------------------------\n");

    for (int n = 1; n <= n_terms; n++) {
      
        double num = factorial(n);
        
        
        double den = pow((double)n, sqrt((double)n));
        
       
        double a_n = num / den;
        
        
        sum += a_n;

        printf("%-5d | %-20.6f | %-20.6f\n", n, a_n, sum);
    }

    printf("-----------------------------------------\n");
    printf("\nИтоговая сумма 10 членов ряда: %.6f\n", sum);

    return 0;
}