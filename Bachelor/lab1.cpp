#include <iostream>
#include <cmath>
#include <clocale>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian.UTF8");

    cout << "=========================================\n";
    cout << " Лабораторная работа №1. Вариант 23\n";
    cout << "=========================================\n\n";

    // Задание 1: Вычисление выражения для float и double
    float a_f = 1000.0f, b_f = 0.0001f;
    float num_f = pow(a_f + b_f, 3) - (pow(a_f, 3) + 3 * pow(a_f, 2) * b_f);
    float den_f = 3 * a_f * pow(b_f, 2) + pow(b_f, 3);
    float result_f = num_f / den_f;

    double a_d = 1000.0, b_d = 0.0001;
    double num_d = pow(a_d + b_d, 3) - (pow(a_d, 3) + 3 * pow(a_d, 2) * b_d);
    double den_d = 3 * a_d * pow(b_d, 2) + pow(b_d, 3);
    double result_d = num_d / den_d;

    cout << fixed << setprecision(7);
    cout << "Результат для float  : " << result_f << endl;
    cout << "Результат для double : " << result_d << endl << endl;

    // Задание 2: Инкремент и декремент
    int n = 5, m = 10;
    cout << "Исходные значения: n = " << n << ", m = " << m << endl << endl;

    int n1 = n, m1 = m;
    cout << "1) n---m   = " << (n1-- - m1) << endl;

    int n2 = n, m2 = m;
    bool res2 = m2-- < -n2;
    cout << "2) m--<-n  = " << (res2 ? "true" : "false") << endl;

    int n3 = n, m3 = m;
    bool res3 = n3++ > m3;
    cout << "3) n++>m   = " << (res3 ? "true" : "false") << endl;

    return 0;
}