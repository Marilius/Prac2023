#include "gtest/gtest.h"
#include <iostream>
#include <math.h>

#include "../Factory.hpp"
#include "../Root.hpp"

class Root_test : public testing::Test
{
};

TEST(Root_test, RootSearch)
{
    FuncFactory F;

    auto a = F.Create("ident", 2);
    // std::cout << (*f).ToString() << std::endl;
    ASSERT_EQ(FindRoot((*a), 2), 0);

    auto b = F.Create("polynomial", {4, -1});
    ASSERT_EQ(std::round(FindRoot((*b), 1000, -10)), 4);

    auto c = F.Create("polynomial", {4, 1});
    ASSERT_EQ(std::round(FindRoot((*c), 1000, -10)), -4);

    auto d = F.Create("polynomial", {1, 0, -1});
    ASSERT_EQ(std::round(FindRoot((*d), 20, -2)), -1);
    ASSERT_EQ(std::round(FindRoot((*d), 20, 2)), 1);

    auto e = F.Create("polynomial", {8, 0, 0, -1});
    ASSERT_EQ(std::round(FindRoot((*e), 1000, 2)), 2);

    auto f = F.Create("polynomial", {8, 0, 0, 1});
    ASSERT_EQ(std::round(FindRoot((*f), 1000, -2)), -2);
}
