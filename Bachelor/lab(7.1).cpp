#include <iostream>
#include <cstdlib>

using namespace std;

// [RU] Перегруженная функция 1 (для массива типа int, начинающегося на четное число):
// Выполняет циклический сдвиг влево на количество элементов, равное первому элементу.
// [AR] الدالة المحملة زائداً 1 (لمصفوفة من نوع int تبدأ بعدد زوجي):
// تقوم بعمل إزاحة دائرية لليسار بمقدار قيمة أول عنصر في المصفوفة.
void cyclic_shift(int n, int a[]) {
    if (n <= 1) return;

    // [RU] Проверяем, что первый элемент четный | [AR] نتأكد أن العنصر الأول زوجي
    if (a[0] % 2 == 0) {
        int steps = abs(a[0]) % n; // [RU] Количество шагов сдвига | [AR] عدد خطوات الإزاحة
        for (int s = 0; s < steps; s++) {
            int first = a[0];
            for (int i = 0; i < n - 1; i++) {
                a[i] = a[i + 1];
            }
            a[n - 1] = first;
        }
    }
}

// [RU] Перегруженная функция 2 (для массива типа long, начинающегося на нечетное число):
// Выполняет циклический сдвиг вправо на количество элементов, равное последнему элементу.
// [AR] الدالة المحملة زائداً 2 (لمصفوفة من نوع long تبدأ بعدد فردي):
// تقوم بعمل إزاحة دائرية لليمين بمقدار قيمة آخر عنصر في المصفوفة.
void cyclic_shift(int n, long a[]) {
    if (n <= 1) return;

    // [RU] Проверяем, что первый элемент нечетный | [AR] نتأكد أن العنصر الأول فردي
    if (a[0] % 2 != 0) {
        long steps = abs(a[n - 1]) % n; // [RU] Количество шагов сдвига | [AR] عدد خطوات الإزاحة
        for (long s = 0; s < steps; s++) {
            long last = a[n - 1];
            for (int i = n - 1; i > 0; i--) {
                a[i] = a[i - 1];
            }
            a[0] = last;
        }
    }
}

int main() {
    // [RU] Настройка кодировки консоли | [AR] ضبط ترميز الكونسول
    system("chcp 65001 > nul");

    const int MAX_SIZE = 100;

    // ================= Часть (а) / الفرع (أ) =================
    int x[MAX_SIZE];
    int n1;

    cout << "--- Part (a): Array starting with an EVEN number ---" << endl;
    cout << "Enter array size (n1): ";
    cin >> n1;

    cout << "Enter " << n1 << " integers (first must be EVEN): ";
    for (int i = 0; i < n1; i++) {
        cin >> x[i];
    }

    // [RU] Вызов первой перегруженной функции (для int)
    // [AR] استدعاء الدالة المحملة زائداً الأولى (لنوع int)
    cyclic_shift(n1, x);

    cout << "Result after left shift: ";
    for (int i = 0; i < n1; i++) {
        cout << x[i] << " ";
    }
    cout << endl << endl;

    // ================= Часть (б) / الفرع (б) =================
    long y[MAX_SIZE];
    int n2;

    cout << "--- Part (b): Array starting with an ODD number ---" << endl;
    cout << "Enter array size (n2): ";
    cin >> n2;

    cout << "Enter " << n2 << " numbers (first must be ODD): ";
    for (int i = 0; i < n2; i++) {
        cin >> y[i];
    }

    // [RU] Вызов второй перегруженной функции (для long)
    // [AR] استدعاء الدالة المحملة زائداً الثانية (لنوع long)
    cyclic_shift(n2, y);

    cout << "Result after right shift: ";
    for (int i = 0; i < n2; i++) {
        cout << y[i] << " ";
    }
    cout << endl;

    return 0;
}