/* Gradient method */
/* Source: https://vlab.fandom.com/ru/wiki/%D0%93%D1%80%D0%B0%D0%B4%D0%B8%D0%B5%D0%BD%D1%82%D0%BD%D1%8B%D0%B9_%D1%81%D0%BF%D1%83%D1%81%D0%BA */

#ifndef ROOT_HPP
#define ROOT_HPP

#include "Function.hpp"

double GoldenSelection(Compose &f2, double grad, double x, double eps, double a = 0, double b = 0.05);

template <typename TFunction>
double FindRoot(TFunction &f, unsigned long it, double init_x = 0, double eps = 0.00000001)
{
    double cur_x = init_x;
    double last_x;
    auto f2 = f * f;

    for (unsigned long i = 0; i < it; i++)
    {
        last_x = cur_x;
        double grad = f2.Deriative(cur_x);
        double lambda = GoldenSelection(f2, grad, cur_x, eps);
        cur_x = cur_x - lambda * grad;
        if (std::abs(f2(cur_x) - f2(last_x)) < eps)
            break;
    }
    return cur_x;
}

#endif //ROOT_HPP