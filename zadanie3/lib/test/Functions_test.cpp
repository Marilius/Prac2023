#include "gtest/gtest.h"
#include <iostream>
#include <math.h>

#include "../Factory.hpp"

class Operations_test : public testing::Test
{
};

TEST(Operations_test, ToString)
{
    FuncFactory F;

    auto A1 = F.Create("polynomial", {0, 2});
    auto A2 = F.Create("ident", 2);
    ASSERT_EQ((*A1).ToString(), (*A2).ToString());

    auto B1 = F.Create("polynomial", {0, 0, 1, 0, 1});
    auto B2 = F.Create("power", {2, 4});
    ASSERT_EQ((*B1).ToString(), (*B2).ToString());

    auto C1 = F.Create("polynomial", {10});
    auto C2 = F.Create("const", 10);
    ASSERT_EQ((*C1).ToString(), (*C2).ToString());

    auto D1 = F.Create("exp", {10});
    auto D2 = F.Create("exp", 10);
    ASSERT_EQ((*D1).ToString(), (*D2).ToString());
}
