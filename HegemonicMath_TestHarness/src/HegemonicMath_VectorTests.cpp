#include <gtest/gtest.h>
#include <Vector.h>
#include "HegemonicMath_GTestSupport.h"

/**
 * INFO: Vector test to test initialization to zero
 */
TEST(Vector, VectorInitialization)
{
    Hegemonic::Vector3d v = Hegemonic::Vector3d();
    bool t = EXPECT_TRUE_ARRAY<double, 3>(v.get(), 0);
    EXPECT_TRUE(t);
}

/**
 * INFO: Vector test to test initialization to something other than zero using std::array
 */
TEST(Vector, VectorInitializationNonZero)
{
    std::array<double, 3> a = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    bool t = EXPECT_TRUE_ARRAY<double, 3>(v.get(), a);
    EXPECT_TRUE(t);
}

/**
 * INFO: Vector test to test initialization to something other than zero using c-style array
 */
TEST(Vector, VectorInitializationNonZeroCArray)
{
    double a[3] = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    bool t = EXPECT_TRUE_ARRAY<double, 3>(v.get(), {1,2,3});
    EXPECT_TRUE(t);
}

/**
 * INFO: Vector test to test getting size of vector
 */
TEST(Vector, VectorGetSize)
{
    std::array<double, 3> a = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    EXPECT_TRUE(v.getSize() == 3);
}

/**
 * INFO: Vector test to test getting underyling std::array
 */
TEST(Vector, VectorGetArray)
{
    std::array<double, 3> a = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    std::array<double, 3> b = v.get();
    for (int i = 0; i < 3; i++)
    {
        EXPECT_TRUE(b.at(i) == a.at(i));
    }
}

/**
 * INFO: Vector test to test getting an element
 */
TEST(Vector, VectorGetElement)
{
    std::array<double, 3> a = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    for (int i = 0; i < 3; i++)
    {
        EXPECT_TRUE(v.getElement(i) == a.at(i));
    }
}

/**
 * INFO: Vector test to test setting an element
 */
TEST(Vector, VectorSetElement)
{
    std::array<double, 3> a = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    v.setElement(10.0, 2);
    EXPECT_TRUE(v.getElement(2) == 10.0);
}

/**
 * INFO: Vector test to test getting magnitude
 */
TEST(Vector, VectorGetMagnitude)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v = Hegemonic::Vector4d(a);
    EXPECT_TRUE(v.getMagnitude() == 4.0);
}

/**
 * INFO: Vector test to test getting element out of range
 */
TEST(Vector, VectorGetElementOutOfRange)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v = Hegemonic::Vector4d(a);
    EXPECT_THROW(v.getElement(10), std::out_of_range);
}

/**
 * INFO: Vector test to test setting element out of range
 */
TEST(Vector, VectorSetElementOutOfRange)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v = Hegemonic::Vector4d(a);
    EXPECT_THROW(v.setElement(10.0, 10), std::out_of_range);
}