#ifndef FUNCTION_CPP
#define FUNCTION_CPP

#include <math.h>

#include "Function.hpp"

Compose::Compose(BaseFunction &lop_, BaseFunction &rop_, std::string type_) : lop(lop_.Copy()), rop(rop_.Copy()), type(type_) {}

double Compose::Deriative(double x)
{
    // производная сложной функции
    if (type == "+")
    {
        return (*lop).Deriative(x) + (*rop).Deriative(x);
    }
    else if (type == "-")
    {
        return (*lop).Deriative(x) - (*rop).Deriative(x);
    }
    else if (type == "*")
    {
        return ((*lop).Deriative(x) * (*rop)(x) + (*rop).Deriative(x) * (*lop)(x));
    }
    else if (type == "/")
    {
        return ((*lop).Deriative(x) * (*rop)(x) - (*rop).Deriative(x) * (*lop)(x)) / ((*rop)(x) * (*rop)(x));
    }
    else
    {
        throw std::logic_error("No such type!");
    }
}

double Compose::operator()(double x)
{
    if (type == "+")
    {
        return (*lop)(x) + (*rop)(x);
    }
    else if (type == "-")
    {
        return (*lop)(x) - (*rop)(x);
    }
    else if (type == "*")
    {
        return (*lop)(x) * (*rop)(x);
    }
    else if (type == "/")
    {
        return (*lop)(x) / (*rop)(x);
    }
    else
    {
        throw std::logic_error("No such type!");
    }
}

std::string Compose::ToString() const
{
    if (type == "+")
    {
        return (*lop).ToString() + " + " + (*rop).ToString();
    }
    else if (type == "-")
    {
        return (*lop).ToString() + " - " + (*rop).ToString();
    }
    else if (type == "*")
    {
        return "(" + (*lop).ToString() + ") * (" + (*rop).ToString() + ")";
    }
    else if (type == "/")
    {
        return "(" + (*lop).ToString() + ") / (" + (*rop).ToString() + ")";
    }
    else
    {
        throw std::logic_error("No such type!");
    }
}

std::shared_ptr<BaseFunction> Compose::Copy()
{
    return std::make_shared<Compose>(*lop, *rop, type);
}

Exponential::Exponential(std::vector<double> _coef) : coef(_coef[0])
{
    if (!_coef.empty())
        coef = _coef[0];
    else
        coef = 0;
}

double Exponential::Deriative(double x)
{
    return (coef * exp(coef * x));
}

double Exponential::operator()(double x)
{
    return (exp(coef * x));
}

std::string Exponential::ToString() const
{
    if (coef == 0)
        return "1";
    else
        return "exp(" + std::to_string(coef) + "*x)";
}

std::shared_ptr<BaseFunction> Exponential::Copy()
{
    return std::make_shared<Exponential>(*this);
}

Polynomial::Polynomial()
{
    PolyDict[0] = 0;
}

Polynomial::Polynomial(double _coef)
{
    PolyDict[0] = _coef;
}

Polynomial::Polynomial(std::vector<double> _coef)
{
    for (int idx = 0; idx < _coef.size(); idx++)
        PolyDict[idx] = _coef[idx];
}

double Polynomial::Deriative(double x)
{
    double res = 0;
    for (auto &[key, val] : PolyDict)
    {
        if (key > 0)
            res += key * val * pow(x, key - 1);
    }
    return res;
}

double Polynomial::operator()(double x)
{
    double res = 0;
    for (auto &[key, val] : PolyDict)
    {
        if (val != 0)
            res += val * pow(x, key);
    }
    return res;
}

std::string Polynomial::ToString() const
{
    std::string res = "";
    for (auto &[key, val] : PolyDict)
    {
        if (val != 0)
        {
            if (key == 0)
            {
                res += std::to_string(val) + " + ";
            }
            else
            {
                res += std::to_string(val) + "*x**" + std::to_string(key) + " + ";
            }
        }
    }
    return res.substr(0, res.length() - 3);
}

std::shared_ptr<BaseFunction> Polynomial::Copy()
{
    return std::make_shared<Polynomial>(*this);
}

Identical::Identical()
{
    PolyDict[1] = 0;
}

Identical::Identical(double _coef)
{
    PolyDict[1] = _coef;
}

Identical::Identical(std::vector<double> _coef)
{
    PolyDict[1] = _coef[0];
}

Constant::Constant()
{
    PolyDict[0] = 0;
}

Constant::Constant(double _coef)
{
    PolyDict[0] = _coef;
}

Constant::Constant(std::vector<double> _coef)
{
    if (!_coef.empty())
        PolyDict[0] = _coef[0];
    else
        PolyDict[0] = 0;
}

Power::Power()
{
    PolyDict[0] = 0;
}

Power::Power(double _coef)
{
    PolyDict[_coef] = 1;
}

Power::Power(std::vector<double> _coef)
{
    for (int idx = 0; idx < _coef.size(); idx++)
        PolyDict[_coef[idx]] = 1;
}

#endif // FUNCTION_CPP