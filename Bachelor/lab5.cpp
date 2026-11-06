#include <iostream>
using namespace std;

int main() {
    // Объявление констант и переменных для размерности массива
    const int MAX_SIZE = 100;
    int n;

    // Ввод размерности массива с клавиатуры
    cout << "Enter size N (max 100): ";
    cin >> n;

    int a[MAX_SIZE];

    // Ввод элементов одномерного массива
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Объявление двумерного массива N x N
    int matrix[MAX_SIZE][MAX_SIZE];

    // Алгоритм формирования двумерного массива так, чтобы сумма каждого столбца была равна соответствующему элементу массива 'a'
    for (int j = 0; j < n; j++) {
        int target_sum = a[j];
        int remaining = target_sum;

        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                // Последний элемент в столбце принимает оставшуюся сумму
                matrix[i][j] = remaining;
            }
            else {
                // Присваиваем единицу остальным элементам
                matrix[i][j] = 1;
                remaining -= 1;
            }
        }
    }

    // Вывод полученного двумерного массива на экран
    cout << "\nResulting Matrix N x N:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}