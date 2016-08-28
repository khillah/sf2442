#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/TargetCalculator.hpp"

using namespace ::testing;

void checkCoords(const Coordinates& expected, const Coordinates& received)
{
    EXPECT_EQ(expected.x, received.x);
    EXPECT_EQ(expected.y, received.y);
}

TEST(TargetCalculatorTestSuite, properlyCalculates)
{
    TargetCalculator calc;
    Coordinates ship {3873, 6886};
    Coordinates target {13552, 2394};
    Coordinates next {13005, 7161};

    ASSERT_NO_FATAL_FAILURE(checkCoords({13245, 2818}, calc.calculate(ship, target, next)));
}

void checkFunction(const Coordinates& p1, const Coordinates& p2, double a, double b)
{
    LinearFunction f(p1, p2);
    ASSERT_EQ(a, f.a);
    ASSERT_EQ(b, f.b);
}

TEST(TargetCalculatorTestSuite, linearFunctionSolver)
{
    ASSERT_NO_FATAL_FAILURE(checkFunction({0,0}, {10, 10}, 1, 0));
    ASSERT_NO_FATAL_FAILURE(checkFunction({0,10}, {10, 10}, 0, 10));
    ASSERT_NO_FATAL_FAILURE(checkFunction({2,6}, {3, 8}, 2, 2));
}

TEST(TargetCalculatorTestSuite, trinomialExpressionSolver)
{
    ASSERT_THROW(TrinomialExpression(1, 0, 1), std::runtime_error);

    TrinomialExpression ex1(1, 0, -9);
    ASSERT_NO_FATAL_FAILURE(checkCoords({-3, 0}, ex1.s1));
    ASSERT_NO_FATAL_FAILURE(checkCoords({3, 0}, ex1.s2));

    TrinomialExpression ex2(1, 0, 0);
    ASSERT_NO_FATAL_FAILURE(checkCoords({0, 0}, ex2.s1));
    ASSERT_NO_FATAL_FAILURE(checkCoords({0, 0}, ex2.s2));
}

void checkVector(double x, double y, const Vector& v)
{
    EXPECT_EQ(x, v.x);
    EXPECT_EQ(y, v.y);
}

TEST(TargetCalculatorTestSuite, vectorConstructorCalculatesFromCords)
{
    ASSERT_NO_FATAL_FAILURE(checkVector(10, 10, Vector({0, 0}, {10, 10})));
    ASSERT_NO_FATAL_FAILURE(checkVector(5, 5, Vector({5, 5}, {10, 10})));
    ASSERT_NO_FATAL_FAILURE(checkVector(59, -3, Vector({-50, 5}, {9, 2})));
}

TEST(TargetCalculatorTestSuite, vectorNormalize)
{
    ASSERT_NO_FATAL_FAILURE(checkVector(1, 0, Vector({0, 10}, {10, 10}).normalize()));
    ASSERT_NO_FATAL_FAILURE(checkVector(0, -1, Vector({-17, 5}, {-17, -10}).normalize()));
    double value = 1.0 / std::sqrt(2.0);
    ASSERT_NO_FATAL_FAILURE(checkVector(-value, value, Vector({-15, 5}, {-16, 6}).normalize()));
}

TEST(TargetCalculatorTestSuite, vectorTranslateGivenPointTimes)
{
    Vector v({0, 0}, {10, 10});
    ASSERT_NO_FATAL_FAILURE(checkCoords({11, 11}, v.translateGivenPointTimes({1, 1}, 1)));
    ASSERT_NO_FATAL_FAILURE(checkCoords({31, 31}, v.translateGivenPointTimes({1, 1}, 3)));
}

TEST(TargetCalculatorTestSuite, lineCircleNearestIntersectionCalculation)
{
    LineCircleNearestIntersection t({0, 0}, {0, 1200});
    ASSERT_NO_FATAL_FAILURE(checkCoords({0, 600}, t.target));

    t = LineCircleNearestIntersection({0, 0}, {1000, 1000});
    ASSERT_NO_FATAL_FAILURE(checkCoords({575, 575}, t.target));
}
