#include <gtest/gtest.h>
#include "HegemonicVector.h"
#include <algorithm>
#include "HegemonicMath_GTestSupport.h"

/**
 * INFO: Vector test to test initialization to zero
 */
TEST(Vector, VectorInitialization)
{
    Hegemonic::Vector3d v = Hegemonic::Vector3d();
    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(*v.get(), 0, ce.DOUBLE);
}

/**
 * INFO: Vector test to test initialization to something other than zero using std::array
 */
TEST(Vector, VectorInitializationNonZero)
{
    std::array<double, 3> a = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(*v.get(), a, ce.DOUBLE);
}

/**
 * INFO: Vector test to test initialization to something other than zero using c-style array
 */
TEST(Vector, VectorInitializationNonZeroCArray)
{
    double a[3] = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);
    std::array<double, 3> b = std::array<double, 3>({1.0, 2.0, 3.0});
    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(*v.get(), b, ce.DOUBLE);
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
    std::array<double, 3> b = *v.get();
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

TEST(Vector, VectorGetElementSetting)
{
    std::array<double, 3> a = {1, 2, 3};
    Hegemonic::Vector3d v = Hegemonic::Vector3d(a);

    v.getElement(0) = 100.0;
    a[0] = 100;

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

/**
 * INFO: Vector test to test overload operator+
 */
TEST(VectorOverloadOperators, AddVector2Vector)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v1 = Hegemonic::Vector4d(a);

    std::array<double, 4> b = {3, 3, 3, 3};
    Hegemonic::Vector4d v2 = Hegemonic::Vector4d(b);
    
    std::array<double, 4> c = {5, 5, 5, 5};
    Hegemonic::Vector4d v3 = Hegemonic::Vector4d(c);

    Hegemonic::Vector4d v4 = v1 + v2;
    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(v4, v3, er.DOUBLE);
}

/**
 * INFO: Vector test to test overload operator+
 */
TEST(VectorOverloadOperators, VectorBracketOverloadOperator)
{
    std::array<double, 4> a = {1,2,3,4};
    Hegemonic::Vector4d v1 = Hegemonic::Vector4d({1,2,3,4});

    for (int i = 0; i < 4; i++)
    {
        EXPECT_TRUE(a.at(i) == v1[i]);
    }
}

/**
 * INFO: Vector test to test overload operator-
 */
TEST(VectorOverloadOperators, SubtractVector2Vector)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v1 = Hegemonic::Vector4d(a);

    std::array<double, 4> b = {3, 3, 3, 3};
    Hegemonic::Vector4d v2 = Hegemonic::Vector4d(b);
    
    std::array<double, 4> c = {-1, -1, -1, -1};
    Hegemonic::Vector4d v3 = Hegemonic::Vector4d(c);

    Hegemonic::Vector4d v4 = v1 - v2;
    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(v4, v3, er.DOUBLE);
}

/**
 * INFO: Vector test to test overload operator-
 */
TEST(VectorOverloadOperators, SubtractVector2Value)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v1 = Hegemonic::Vector4d(a);

    double value = 3;
    
    std::array<double, 4> c = {-1, -1, -1, -1};
    Hegemonic::Vector4d v3 = Hegemonic::Vector4d(c);

    Hegemonic::Vector4d v4 = v1 - value;
    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(v4, v3, er.DOUBLE);
}

/**
 * INFO: Vector test to test overload operator-
 */
TEST(VectorOverloadOperators, SubtractValue2Vector)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v1 = Hegemonic::Vector4d(a);

    double value = 3;
    
    std::array<double, 4> c = {-1, -1, -1, -1};
    Hegemonic::Vector4d v3 = Hegemonic::Vector4d(c);

    Hegemonic::Vector4d v4 = value - v1;
    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(v4, v3, er.DOUBLE);
}

/**
 * INFO: Vector test to test overload operator+
 */
TEST(VectorOverloadOperators, AddVector2Value)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v1 = Hegemonic::Vector4d(a);

    double value = 3;
    
    std::array<double, 4> c = {5, 5, 5, 5};
    Hegemonic::Vector4d v3 = Hegemonic::Vector4d(c);

    Hegemonic::Vector4d v4 = v1 + value;
    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(v4, v3, er.DOUBLE);
}

/**
 * INFO: Vector test to test overload operator+
 */
TEST(VectorOverloadOperators, AddValue2Vector)
{
    std::array<double, 4> a = {2, 2, 2, 2};
    Hegemonic::Vector4d v1 = Hegemonic::Vector4d(a);

    double value = 3;
    
    std::array<double, 4> c = {5, 5, 5, 5};
    Hegemonic::Vector4d v3 = Hegemonic::Vector4d(c);

    Hegemonic::Vector4d v4 = value + v1;
    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(v4, v3, er.DOUBLE);
}

/**
 * INFO: Vector test to test initializer list constructor
 */
TEST(Vector, ConstructorInitializerList)
{
    std::array<double, 4> c = {3, 2, 1, 0};
    Hegemonic::Vector4d v = Hegemonic::Vector4d({3, 2, 1, 0});
    std::size_t count = 0;
    for (const auto& e : v)
    {
        EXPECT_TRUE(c.at(count) == e);
        count++;
    }
}

/**
 * INFO: Vector test to test iterators
 */
TEST(VectorIterator, IteratorLoop)
{
    std::array<double, 4> c = {3, 2, 1, 0};
    Hegemonic::Vector4d v = Hegemonic::Vector4d(c);

    // ranged for loop
    std::size_t count = 0;
    for (const auto& e : v)
    {
        EXPECT_TRUE(c.at(count) == e);
        count++;
    }

    // c++98 Style
    count = 0;
    for (Hegemonic::Vector4d::iterator<double> it = v.begin(); it != v.end(); ++it)
    {
        EXPECT_TRUE(c.at(count) == *it);
        count++;
    }
}

/**
 * INFO: Vector test to test getNormalized
 */
TEST(Vector, GetNormalized)
{
    Hegemonic::Vector3d v = {3.0, 4.0, 5.0};
    Hegemonic::Vector3d a = v.getNormalized();
    Hegemonic::Vector3d b = {0.424264068711929, 0.565685424949238, 0.707106781186547};

    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(a, b, er.DOUBLE);
}

/**
 * INFO: Vector test to test setNormalized
 */
TEST(Vector, SetNormalized)
{
    Hegemonic::Vector3d v = {3.0, 4.0, 5.0};
    v.setNormalized();
    Hegemonic::Vector3d b = {0.424264068711929, 0.565685424949238, 0.707106781186547};

    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(v, b, er.DOUBLE);
}