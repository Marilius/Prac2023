#include <map>

#include "Function.hpp"

class IFunction
{
public:
    virtual ~IFunction(){};
    virtual auto Create() -> std::shared_ptr<BaseFunction> const = 0;
    virtual auto Create(double param) -> std::shared_ptr<BaseFunction> const = 0;
    virtual auto Create(std::vector<double> params) -> std::shared_ptr<BaseFunction> const = 0;
};

template <class TFunction>
class FunctionCreator : public IFunction
{
public:
    auto Create() -> std::shared_ptr<BaseFunction> const override
    {
        return std::make_shared<TFunction>(TFunction());
    }

    auto Create(double param) -> std::shared_ptr<BaseFunction> const override
    {
        return std::make_shared<TFunction>(TFunction(param));
    }

    auto Create(std::vector<double> params) -> std::shared_ptr<BaseFunction> const override
    {
        return std::make_shared<TFunction>(TFunction(params));
    }
};

/* Factory */

class FuncFactory
{
public:
    FuncFactory()
    {
        FuncTypes =
            {
                {"ident", std::make_shared<FunctionCreator<Identical>>()},
                {"const", std::make_shared<FunctionCreator<Constant>>()},
                {"power", std::make_shared<FunctionCreator<Power>>()},
                {"exp", std::make_shared<FunctionCreator<Exponential>>()},
                {"polynomial", std::make_shared<FunctionCreator<Polynomial>>()}};
    }

    std::shared_ptr<BaseFunction> Create(const std::string &type)
    {
        return FuncTypes[type]->Create();
    }

    std::shared_ptr<BaseFunction> Create(const std::string &type, double param)
    {
        return FuncTypes[type]->Create(param);
    }

    std::shared_ptr<BaseFunction> Create(const std::string &type, std::vector<double> params)
    {
        return FuncTypes[type]->Create(params);
    }

private:
    std::map<std::string, std::shared_ptr<IFunction>> FuncTypes;
};
