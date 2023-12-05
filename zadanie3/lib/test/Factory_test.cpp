#include "gtest/gtest.h"
#include <iostream>

#include "../Factory.hpp"

class Factory_test : public testing::Test
{
};

TEST(Factory_test, Factory)
{
    FuncFactory F;

    auto A1 = F.Create("ident", {});
    Identical A2;
    ASSERT_EQ(typeid(*A1), typeid(A2));

    auto B1 = F.Create("power", {1, 2, 3});
    Power B2(5);
    ASSERT_EQ(typeid(*B1), typeid(B2));

    auto C1 = F.Create("exp");
    Exponential C2(10);
    ASSERT_EQ(typeid(*C1), typeid(C2));

    auto D1 = F.Create("const", {1});
    Constant D2;
    ASSERT_EQ(typeid(*D1), typeid(D2));

    auto E1 = F.Create("polynomial");
    Polynomial E2({1, 2, 3});
    ASSERT_EQ(typeid(*E1), typeid(E2));
}
