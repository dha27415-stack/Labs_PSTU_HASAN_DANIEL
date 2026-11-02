#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian.UTF-8");

    double a = 0.1;
    double b = 1.0;
    int k = 10;
    double h = (b - a) / k;
    double eps = 0.0001;

    cout << "x\t|\tY exact\t|\tSum (n=10)\t|\tSum (eps)" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (double x = a; x <= b + h / 2; x += h) {
        
        double cos_x = cos(x);
        double y_exact = 2.0 * (cos_x * cos_x - 1.0);

       
        double sum_n = 0.0;
        for (int n = 1; n <= 10; n++) {
            double fact = 1.0;
            for (int i = 1; i <= 2 * n; i++) {
                fact *= i;
            }
            double term = pow(-1, n) * pow(2.0 * x, 2 * n) / fact;
            sum_n += term;
        }

        
        double sum_eps = 0.0;
        int n = 1;
        double term = 0.0;
        do {
            double fact = 1.0;
            for (int i = 1; i <= 2 * n; i++) {
                fact *= i;
            }
            term = pow(-1, n) * pow(2.0 * x, 2 * n) / fact;
            sum_eps += term;
            n++;
        } while (fabs(term) >= eps);

         cout << x << "\t|\t" << y_exact << "\t|\t" << sum_n << "\t|\t" << sum_eps << endl;
    }

    return 0;
}
