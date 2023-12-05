#ifndef ROOT_CPP
#define ROOT_CPP

#include "Root.hpp"

// Метод золотого сечения для нахождения шага (lambda)
double GoldenSelection(Compose &f2, double grad, double x, double eps, double a, double b)
{
    const double fi = 1.6180339887;
    double x1, x2, y1, y2;

    x1 = b - ((b - a) / fi);
    x2 = b + ((b - a) / fi);
    y1 = f2(x - x1 * grad);
    y2 = f2(x - x2 * grad);

    while (std::abs(b - a) > eps)
    {
        if (y1 <= y2)
        {
            b = x2;
            x2 = x1;
            x1 = b - ((b - a) / fi);
            y2 = y1;
            y1 = f2(x - x1 * grad);
        }
        else
        {
            a = x1;
            x1 = x2;
            x2 = a + ((b - a) / fi);
            y1 = y2;
            y2 = f2(x - x2 * grad);
        }
    }
    return (a + b) / 2;
}

#endif //ROOT_CPP