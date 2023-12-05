#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>

#include <stdio.h>

/* BaseFunction class */

class BaseFunction {
public:
    virtual std::string ToString() const = 0;
    virtual double Deriative(double x) = 0;
    virtual double operator()(double x) = 0;
    virtual std::shared_ptr<BaseFunction> Copy() = 0;
    
    double GetDeriv(double x) {
        return Deriative(x);
    }
};

/* Operation handlers */

class Compose : public BaseFunction {
public:
    Compose(BaseFunction& lop_, BaseFunction& rop_, std::string type_);
    std::string ToString() const;
    double Deriative(double x);
    double operator()(double x);
    std::shared_ptr<BaseFunction> Copy();

private:
    std::shared_ptr<BaseFunction> lop, rop;
    std::string type;
};

/* Others.. */

class Exponential : public BaseFunction {
public:
    Exponential() : coef(0) {};
    explicit Exponential(double coef_) : coef(coef_) {};
    explicit Exponential(std::vector<double> coef_);
    std::string ToString() const;
    double Deriative(double x);
    double operator()(double x);
    std::shared_ptr<BaseFunction> Copy();

protected:
    double coef;
};

class Polynomial : public BaseFunction {
public:
    Polynomial();
    explicit Polynomial(double coef_);
    explicit Polynomial(std::vector<double> coef_);
    std::string ToString() const;
    double Deriative(double x);
    double operator()(double x);
    std::shared_ptr<BaseFunction> Copy();

protected:
    std::map<unsigned int, double> PolyDict;
};

class Identical : public Polynomial {
public:
    Identical();
    explicit Identical(double coef_);
    explicit Identical(std::vector<double> coef_); 

};

class Constant : public Polynomial {
public:
    Constant();
    explicit Constant(double coef_);
    explicit Constant(std::vector<double> coef_);

};

class Power : public Polynomial {
public:
    Power();
    explicit Power(double coef_);
    explicit Power(std::vector<double> coef_);

};

template <typename TFunction>
Compose operator+(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "+");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

template <typename TFunction>
Compose operator-(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "-");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

template <typename TFunction>
Compose operator*(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "*");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

template <typename TFunction>
Compose operator/(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "/");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

#endif // FUNCTION_CPP