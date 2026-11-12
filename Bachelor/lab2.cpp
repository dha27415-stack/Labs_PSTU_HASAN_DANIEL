#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <clocale>
#include <windows.h>
#include <iomanip>

using namespace std;

int main() {
    // Настройка кодировки консоли для поддержки кириллицы в комментариях
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Laboratory Work 2. Variant 23 ===" << endl;
 
    int total_terms; // Переменная для ввода количества членов ряда пользователем
    cout << "Enter number of terms: ";
    cin >> total_terms;

    double sum = 0.0;       // Переменная для накопления суммы ряда
    double factorial = 1.0; // Переменная для последовательного расчета факториала n!

    // Цикл для вычисления суммы введенного числа членов ряда: a_n = n! / (n^(sqrt(n)))
    for (int n = 1; n <= total_terms; n++) {
        factorial *= n;

        // Вычисление знаменателя: n в степени квадратного корня из n
        double denominator = pow(n, sqrt(n));

        // Вычисление значения текущего члена ряда a_n
        double a_n = factorial / denominator;

        // Добавление члена ряда к общей сумме
        sum += a_n;

        // Вывод значения каждого отдельного члена
        cout << "Term " << n << " = " << a_n << endl;
    }

    // Вывод итоговой суммы с высокой точностью
    cout << fixed << setprecision(6);
    cout << "\nTotal sum = " << sum << endl;

    return 0;
}
