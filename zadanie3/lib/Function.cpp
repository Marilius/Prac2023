#ifndef FUNCTION_CPP
#define FUNCTION_CPP

#include <math.h>

#include "Function.hpp"

Compose::Compose(BaseFunction &lop_, BaseFunction &rop_, std::string type_) : lop(lop_.Copy()), rop(rop_.Copy()), type(type_) {}

double Compose::Deriative(double x)
{
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

Exponential::Exponential(std::vector<double> coef_) : coef(coef_[0])
{
    if (!coef_.empty())
        coef = coef_[0];
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

Polynomial::Polynomial(double coef_)
{
    PolyDict[0] = coef_;
}

Polynomial::Polynomial(std::vector<double> coef_)
{
    for (int idx = 0; idx < coef_.size(); idx++)
        PolyDict[idx] = coef_[idx];
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

Identical::Identical(double coef_)
{
    PolyDict[1] = coef_;
}

Identical::Identical(std::vector<double> coef_)
{
    PolyDict[1] = coef_[0];
}

Constant::Constant()
{
    PolyDict[0] = 0;
}

Constant::Constant(double coef_)
{
    PolyDict[0] = coef_;
}

Constant::Constant(std::vector<double> coef_)
{
    if (!coef_.empty())
        PolyDict[0] = coef_[0];
    else
        PolyDict[0] = 0;
}

Power::Power()
{
    PolyDict[0] = 0;
}

Power::Power(double coef_)
{
    PolyDict[coef_] = 1;
}

Power::Power(std::vector<double> coef_)
{
    for (int idx = 0; idx < coef_.size(); idx++)
        PolyDict[coef_[idx]] = 1;
}

#endif // FUNCTION_CPP