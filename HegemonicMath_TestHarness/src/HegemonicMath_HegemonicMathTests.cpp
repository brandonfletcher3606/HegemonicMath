#include <gtest/gtest.h>
#include "HegemonicMath.h"
#include "HegemonicMath_GTestSupport.h"
#include "HegemonicMath_PrinterSupport.h"
#include "HegemonicMathVersion.h"

/**
 * INFO: Test Version
 */
TEST(HegemonicMath, VERSION)
{
    EXPECT_TRUE(Hegemonic::getHegemonicMathVersion() == "1.0.0");
}

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

/**
 * INFO: Test HegemonicMath Clamp Vector
 */
TEST(HegemonicMath, ClampVector)
{
    Hegemonic::Vector3d v = {1.0, 2.0, 3.0};
    clamp(1.5, 2.5, v);

    Hegemonic::Vector3d c = {1.5, 2.0, 2.5};

    ERROR e;
    EXPECT_TRUE_VECTOR_APPROX(v, c, e.DOUBLE);
}

/**
 * INFO: Test HegemonicMath Clamp Matrix
 */
TEST(HegemonicMath, ClampMatrix)
{
    Hegemonic::Matrix33d m;
    m.setRow({1.0, 2.0, 3.0}, 0);
    m.setRow({1.0, 2.0, 3.0}, 1);
    m.setRow({1.0, 2.0, 3.0}, 2);

    Hegemonic::Matrix33d d;
    d.setRow({1.5, 2.0, 2.5}, 0);
    d.setRow({1.5, 2.0, 2.5}, 1);
    d.setRow({1.5, 2.0, 2.5}, 2);

    clamp(1.5, 2.5, m);

    ERROR e;
    EXPECT_TRUE_MATRIX_APPROX(m, d, e.DOUBLE);
}

/**
 * INFO: Test HegemonicMath Wrap
 */
TEST(HegemonicMath, Wrap)
{
    double a = 1.0;
    double b = 2.0;
    double c = 5.0;

    double d = Hegemonic::wrap(a, b, c);
    EXPECT_TRUE(d == 1.0);
}

/**
 * INFO: Test HegemonicMath Wrap Vector
 */
TEST(HegemonicMath, WrapVector)
{
    Hegemonic::Vector3d v = {0.0, 360.0, 370.0};
    wrap(0.0, 360.0, v);

    Hegemonic::Vector3d c = {0.0, 0.0, 10.0};

    ERROR e;
    EXPECT_TRUE_VECTOR_APPROX(v, c, e.DOUBLE);
}

/**
 * INFO: Test HegemonicMath Wrap Matrix
 */
TEST(HegemonicMath, WrapMatrix)
{
    Hegemonic::Matrix33d m;
    m.setRow({0.0, 360.0, 370.0}, 0);
    m.setRow({0.0, 360.0, 370.0}, 1);
    m.setRow({0.0, 360.0, 370.0}, 2);

    Hegemonic::Matrix33d d;
    d.setRow({0.0, 0.0, 10.0}, 0);
    d.setRow({0.0, 0.0, 10.0}, 1);
    d.setRow({0.0, 0.0, 10.0}, 2);

    wrap(0.0, 360.0, m);

    ERROR e;
    EXPECT_TRUE_MATRIX_APPROX(m, d, e.DOUBLE);
}

/**
 * INFO: Test HegemonicMath Lerp
 */
TEST(HegemonicMath, Lerp)
{
    double a = 1.0;
    double b = 2.0;
    double c = 0.5;

    double d = Hegemonic::lerp(a, b, c);
    EXPECT_TRUE(d == 1.5);
}

/**
 * INFO: Test HegemonicMath Lerp Vector
 */
TEST(HegemonicMath, LerpVector)
{
    Hegemonic::Vector3d v = {1.0, 2.0, 3.0};
    Hegemonic::Vector3d c = {4.0, 5.0, 6.0};
    Hegemonic::Vector3d b = {2.5, 3.5, 4.5};
    Hegemonic::Vector3d a = Hegemonic::lerp(v, c, 0.5);

    ERROR e;
    EXPECT_TRUE_VECTOR_APPROX(a, b, e.DOUBLE);
}

/**
 * INFO: Test HegemonicMath Lerp Matrix
 */
TEST(HegemonicMath, LerpMatrix)
{
    Hegemonic::Matrix33d m;
    m.setRow({0.0, 180.0, 270.0}, 0);
    m.setRow({0.0, 180.0, 270.0}, 1);
    m.setRow({0.0, 180.0, 270.0}, 2);

    Hegemonic::Matrix33d d;
    d.setAll(360.0);

    Hegemonic::Matrix33d v = lerp(m, d, 0.5);
    
    Hegemonic::Matrix33d c;
    c.setRow({180.0, 270.0, 315.0}, 0);
    c.setRow({180.0, 270.0, 315.0}, 1);
    c.setRow({180.0, 270.0, 315.0}, 2);

    ERROR e;
    EXPECT_TRUE_MATRIX_APPROX(v, c, e.DOUBLE);
}

/**
 * INFO: Test HegemonicMath NLerp Vector
 */
TEST(HegemonicMath, NLerpVector)
{
    Hegemonic::Vector3d v = {1.0, 2.0, 3.0};
    Hegemonic::Vector3d c = {4.0, 5.0, 6.0};
    Hegemonic::Vector3d b = {0.401609664451249, 0.562253530231749, 0.722897396012249};
    Hegemonic::Vector3d a = Hegemonic::nlerp(v, c, 0.5);

    ERROR e;
    EXPECT_TRUE_VECTOR_APPROX(a, b, e.DOUBLE);
}

/**
 * INFO: Test HegemonicMath NLerp Matrix
 */
TEST(HegemonicMath, NLerpMatrix)
{
    Hegemonic::Matrix33d m;
    m.setRow({1.0, 2.0, 3.0}, 0);
    m.setRow({1.0, 2.0, 3.0}, 1);
    m.setRow({1.0, 2.0, 3.0}, 2);

    Hegemonic::Matrix33d d;
    d.setRow({4.0, 5.0, 6.0}, 0);
    d.setRow({4.0, 5.0, 6.0}, 1);
    d.setRow({4.0, 5.0, 6.0}, 2);

    Hegemonic::Matrix33d v = nlerp(m, d, 0.5);
    
    Hegemonic::Matrix33d c;
    c.setRow({0.401609664451249, 0.562253530231749, 0.722897396012249}, 0);
    c.setRow({0.401609664451249, 0.562253530231749, 0.722897396012249}, 1);
    c.setRow({0.401609664451249, 0.562253530231749, 0.722897396012249}, 2);

    ERROR e;
    EXPECT_TRUE_MATRIX_APPROX(v, c, e.DOUBLE);
}