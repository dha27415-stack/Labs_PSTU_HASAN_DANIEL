#include <iostream>
#include <cmath>
#include <cstdarg>

using namespace std;

// Макроопределение для вычисления длины отрезка по координатам двух точек
#define SIDE_LEN(x1, y1, x2, y2) (sqrt(((x2) - (x1)) * ((x2) - (x1)) + ((y2) - (y1)) * ((y2) - (y1))))

// Вспомогательная функция для векторного произведения (AB x AM)
double crossProduct(double ax, double ay, double bx, double by, double mx, double my) {
    return (bx - ax) * (my - ay) - (by - ay) * (mx - ax);
}

// Функция belong: проверяет, принадлежит ли точка M(mx, my) треугольнику A(ax,ay), B(bx,by), C(cx,cy)
bool belong(double mx, double my,
    double ax, double ay,
    double bx, double by,
    double cx, double cy) {
    double c1 = crossProduct(ax, ay, bx, by, mx, my);
    double c2 = crossProduct(bx, by, cx, cy, mx, my);
    double c3 = crossProduct(cx, cy, ax, ay, mx, my);

    // Точка внутри или на границе, если все векторные произведения неотрицательны или неположительны
    bool has_neg = (c1 < -1e-9) || (c2 < -1e-9) || (c3 < -1e-9);
    bool has_pos = (c1 > 1e-9) || (c2 > 1e-9) || (c3 > 1e-9);

    return !(has_neg && has_pos);
}

// Функция с переменным числом параметров: проверяет принадлежность точки M выпуклому многоугольнику
// Параметры: mx, my, vertexCount (количество вершин), далее пары координат x, y для каждой вершины
bool belongsToConvexPolygon(double mx, double my, int vertexCount, ...) {
    if (vertexCount < 3) {
        return false;
    }

    double* px = new double[vertexCount];
    double* py = new double[vertexCount];

    va_list args;
    va_start(args, vertexCount);

    for (int i = 0; i < vertexCount; ++i) {
        px[i] = va_arg(args, double);
        py[i] = va_arg(args, double);
    }

    va_end(args);

    bool has_neg = false;
    bool has_pos = false;

    for (int i = 0; i < vertexCount; ++i) {
        int next = (i + 1) % vertexCount;
        double cp = crossProduct(px[i], py[i], px[next], py[next], mx, my);

        if (cp < -1e-9) has_neg = true;
        if (cp > 1e-9)  has_pos = true;
    }

    delete[] px;
    delete[] py;

    return !(has_neg && has_pos);
}

int main() {
    // 1. Проверка макроопределения длины стороны
    double x1 = 0.0, y1 = 0.0, x2 = 3.0, y2 = 4.0;
    cout << "Side length between (0,0) and (3,4): " << SIDE_LEN(x1, y1, x2, y2) << endl;

    // 2. Проверка функции belong для треугольника
    double mx = 1.0, my = 1.0;
    bool inTri = belong(mx, my,
        0.0, 0.0,
        4.0, 0.0,
        0.0, 4.0);
    cout << "Point M(" << mx << ", " << my << ") belongs to triangle: "
        << (inTri ? "YES" : "NO") << endl;

    // 3. Проверка функции с переменным числом параметров для выпуклого многоугольника (квадрат 4 вершины)
    bool inPoly4 = belongsToConvexPolygon(mx, my, 4,
        0.0, 0.0,
        4.0, 0.0,
        4.0, 4.0,
        0.0, 4.0);
    cout << "Point M(" << mx << ", " << my << ") belongs to convex polygon (4 vertices): "
        << (inPoly4 ? "YES" : "NO") << endl;

    // 4. Дополнительный вызов для выпуклого пятиугольника (5 вершин)
    bool inPoly5 = belongsToConvexPolygon(10.0, 10.0, 5,
        0.0, 0.0,
        4.0, 0.0,
        5.0, 3.0,
        2.0, 5.0,
        -1.0, 3.0);
    cout << "Point M(" << mx << ", " << my << ") vs (10,10) in convex polygon (5 vertices): "
        << (inPoly5 ? "YES" : "NO") << endl;

    return 0;
}