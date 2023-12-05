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

    auto f = F.Create("ident", 1);
    ASSERT_EQ(FindRoot((*f), 2), 0);
    auto g = F.Create("polynomial", {4, -1});
    ASSERT_EQ(std::round(FindRoot((*g), 1000, -10)), 4);
    auto p = F.Create("polynomial", {1, 0, -1});
    ASSERT_EQ(std::round(FindRoot((*p), 20, -2)), -1);
    ASSERT_EQ(std::round(FindRoot((*p), 20, 2)), 1);
    auto h = F.Create("polynomial", {8, 0, 0, -1});
    ASSERT_EQ(std::round(FindRoot((*h), 1000, 2)), 2);
}
