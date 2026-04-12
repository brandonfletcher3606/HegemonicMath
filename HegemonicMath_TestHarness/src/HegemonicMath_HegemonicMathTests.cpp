#include <gtest/gtest.h>
#include "HegemonicMath.h"
#include "HegemonicMath_GTestSupport.h"
#include "HegemonicMath_PrinterSupport.h"

/**
 * INFO: Test HegemonicMath Minimum
 */
TEST(HegemonicMath, Minimum)
{
    double a = 1.0;
    double b = 2.0;
    double c = Hegemonic::minimum(a, b);
    EXPECT_TRUE(c == 1.0);
}

/**
 * INFO: Test HegemonicMath Minimum for Vectors
 */
TEST(HegemonicMath, MinimumVector)
{
    Hegemonic::Vector3d v = Hegemonic::Vector3d({326.0, 101.1, 302.0});
    std::pair<double, std::size_t> c = Hegemonic::minimum(v);
    EXPECT_TRUE(c.first == 101.1);
    EXPECT_TRUE(c.second == 1);
}

/**
 * INFO: Test HegemonicMath Minimum for Matrix
 */
TEST(HegemonicMath, MinimumMatrix)
{
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>();
    m[0][0] = -100.0;
    m[1][1] = -200.0;
    m[2][2] = -300.0;

    Hegemonic::Vector<std::pair<double, std::size_t>, 3> v = Hegemonic::minimum(m);

    EXPECT_TRUE(v[0].first == -100.0);
    EXPECT_TRUE(v[0].second == 0);

    EXPECT_TRUE(v[1].first == -200.0);
    EXPECT_TRUE(v[1].second == 1);

    EXPECT_TRUE(v[2].first == -300.0);
    EXPECT_TRUE(v[2].second == 2);
}

/**
 * INFO: Test HegemonicMath Maximum
 */
TEST(HegemonicMath, Maximum)
{
    double a = 1.0;
    double b = 2.0;
    double c = Hegemonic::maximum(a, b);
    EXPECT_TRUE(c == 2.0);
}

/**
 * INFO: Test HegemonicMath Maximum for Vectors
 */
TEST(HegemonicMath, MaximumVector)
{
    Hegemonic::Vector3d v = Hegemonic::Vector3d({326.0, 101.1, 302.0});
    std::pair<double, std::size_t> c = Hegemonic::maximum(v);
    EXPECT_TRUE(c.first == 326.0);
    EXPECT_TRUE(c.second == 0);
}

/**
 * INFO: Test HegemonicMath Maximum for Matrix
 */
TEST(HegemonicMath, MaximumMatrix)
{
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>();
    m[0][0] = 100.0;
    m[1][1] = 200.0;
    m[2][2] = 300.0;

    Hegemonic::Vector<std::pair<double, std::size_t>, 3> v = Hegemonic::maximum(m);

    EXPECT_TRUE(v[0].first == 100.0);
    EXPECT_TRUE(v[0].second == 0);

    EXPECT_TRUE(v[1].first == 200.0);
    EXPECT_TRUE(v[1].second == 1);

    EXPECT_TRUE(v[2].first == 300.0);
    EXPECT_TRUE(v[2].second == 2);
}

/**
 * INFO: Test HegemonicMath Clamp
 */
TEST(HegemonicMath, Clamp)
{
    double a = 1.0;
    double b = 2.0;
    double c1 = 1.5;
    double c2 = 3;
    double c3 = 0.5;

    double d = Hegemonic::clamp(a, b, c1);
    EXPECT_TRUE(d == c1);

    d = Hegemonic::clamp(a, b, c2);
    EXPECT_TRUE(d == b);

    d = Hegemonic::clamp(a, b, c3);
    EXPECT_TRUE(d == a);
}