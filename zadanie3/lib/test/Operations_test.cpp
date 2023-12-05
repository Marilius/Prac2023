#include "gtest/gtest.h"
#include <iostream>
#include <math.h>

#include "../Factory.hpp"

class Functions_test : public testing::Test
{
};

TEST(Functions_test, Arithmetic)
{
    FuncFactory F;

    auto A1 = F.Create("polynomial", {0, 2, 1});
    auto A2 = F.Create("polynomial", {0, 1, 2});
    auto A3 = *A1 + *A2;
    ASSERT_EQ(A3(1), 6);
    ASSERT_EQ(A3(2), 18);
    ASSERT_EQ((*A1 - *A2)(1), 0);
    ASSERT_EQ((*A1 - *A2)(2), -2);
    ASSERT_EQ((*A1 * *A2)(1), 9);
    ASSERT_EQ((*A1 * *A2)(2), 80);

    auto A4 = F.Create("exp", 0);
    ASSERT_EQ((A3 / *A4)(1), 6);
    ASSERT_EQ((A3 / *A4)(2), 18);

    auto A5 = A3 / *A4;
    auto A6 = F.Create("const", 18);
    ASSERT_EQ((A5 / *A6)(2), 1);
}

TEST(Functions_test, Deriation)
{
    FuncFactory F;

    auto f = F.Create("power", 2);
    auto g = F.Create("polynomial", {7, 0, 3, 15});
    auto p = *f + *g;
    ASSERT_EQ(p.GetDeriv(1), 53);
    ASSERT_THROW(*f + "abc", std::logic_error);
    ASSERT_EQ(f->GetDeriv(3), 6);

    auto k = F.Create("exp", 2);
    ASSERT_EQ((*k).GetDeriv(2), ((*k) + (*k))(2));
    ASSERT_EQ((*k).GetDeriv(20), ((*k) + (*k))(20));
}

TEST(Functions_test, LogicError)
{
    FuncFactory F;

    auto A1 = F.Create("polynomial", {0, 2});
    ASSERT_THROW(*A1 + "abc", std::logic_error);
    ASSERT_THROW(*A1 + A1, std::logic_error);

    auto A2 = F.Create("ident", 2);
    auto A3 = *A1 + *A2;
    ASSERT_THROW(A3 + "abc", std::logic_error);
    ASSERT_THROW(A3 + A1, std::logic_error);
}
