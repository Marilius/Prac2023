#include <iostream>
#include <vector>
#include "lib/Factory.hpp"
#include "lib/Root.hpp"

using namespace std;

int main()
{
    std::vector<std::shared_ptr<BaseFunction>> cont;
    auto funcFactory = FuncFactory();
    auto f = funcFactory.Create("power", 2); // PowerFunc x^2
    cont.push_back(f);
    auto g = funcFactory.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3
    cont.push_back(g);
    for (const auto ptr : cont)
    {
        std::cout << ptr->ToString() << " for x = 10 is " << (*ptr)(10) << std::endl;
    }
    auto p = *f + *g;
    std::cout << "GetDeriv " << p.GetDeriv(1) << std::endl; // 53

    try
    {
        auto h = *f + "abc"; // std::logic_error
    }
    catch (const std::logic_error &e)
    {
        std::cout << "std::logic_error" << std::endl;
    }

    std::cout << "GetDeriv " << f->GetDeriv(3) << std::endl; // 6

    std::cout << p.ToString() << std::endl;


    auto z = funcFactory.Create("polynomial", {1, 1, 0, 1});
    std::cout << (*z).ToString() << std::endl;
    std::cout << "Root " << FindRoot(*z, 10000) << std::endl;

}
