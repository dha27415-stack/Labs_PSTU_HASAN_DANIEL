#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <clocale>
#include <windows.h>
#include <iomanip>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Task 1 ===" << endl;

    // Переменные для ввода пользователем 
    double a_in, b_in;
    cout << "Enter value for a: ";
    cin >> a_in;
    cout << "Enter value for b: ";
    cin >> b_in;

    // 1. Вычисление с использованием типа float
    float a_f = (float)a_in;
    float b_f = (float)b_in;

    float num_f = pow(a_f + b_f, 3) - (pow(a_f, 3) + 3 * pow(a_f, 2) * b_f);
    float den_f = 3 * a_f * pow(b_f, 2) + pow(b_f, 3);
    float res_float = (den_f != 0) ? (num_f / den_f) : 0;

    // 2. Вычисление с использованием типа double
    double num_d = pow(a_in + b_in, 3) - (pow(a_in, 3) + 3 * pow(a_in, 2) * b_in);
    double den_d = 3 * a_in * pow(b_in, 2) + pow(b_in, 3);
    double res_double = (den_d != 0) ? (num_d / den_d) : 0;

    // Вывод результатов
    cout << fixed << setprecision(7);
    cout << "Result for float  : " << res_float << endl;
    cout << "Result for double : " << res_double << endl;

    // ==========================================
    // Задание 2: Инкремент и декремент
    // ==========================================
    cout << "\n=== Task 2 ===" << endl;

    int n, m;
    cout << "Enter integer n: ";
    cin >> n;
    cout << "Enter integer m: ";
    cin >> m;

    int n1 = n, m1 = m;
    int n2 = n, m2 = m;
    int n3 = n, m3 = m;

    int expr1 = (n1--) - m1;
    bool expr2 = (m2-- < n2);
    bool expr3 = (n3++ > m3);

    cout << "1) n---m = " << expr1 << endl;
    cout << "2) m--<n = " << (expr2 ? "true (1)" : "false (0)") << endl;
    cout << "3) n++>m = " << (expr3 ? "true (1)" : "false (0)") << endl;

    return 0;
}