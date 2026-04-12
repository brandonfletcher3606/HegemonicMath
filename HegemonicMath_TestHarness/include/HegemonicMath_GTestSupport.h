#pragma once

#include <gtest/gtest.h>
#include <array>

#include "Matrix.h"
#include "Vector.h"

typedef struct ERROR
{
    double DOUBLE = 1.192092896e-14;
    float FLOAT = 1.192092896e-07f;
} ERROR;

template<typename T>
void EXPECT_TRUE_APPROX(T aValue1, T aValue2, T aError)
{
    if (abs(aValue1 - aValue2) > aError)
    {
        EXPECT_TRUE(false);
    }
    EXPECT_TRUE(true);
}

template<typename T, std::size_t COUNT>
void EXPECT_TRUE_ARRAY_APPROX(std::array<T, COUNT>& aArray, T aValue, T aError)
{
    for (int i = 0; i < COUNT; i++)
    {
        EXPECT_TRUE_APPROX(aArray.at(i), aValue, aError);
    }
}

template<typename T, std::size_t COUNT>
void EXPECT_TRUE_ARRAY_APPROX(std::array<T, COUNT>& aArray1, std::array<T, COUNT>& aArray2, T aError)
{
    for (int i = 0; i < COUNT; i++)
    {
        EXPECT_TRUE_APPROX(aArray1.at(i), aArray2.at(i), aError);
    }
}

template<typename T, std::size_t ROW, std::size_t COLUMN>
void EXPECT_TRUE_MATRIX_APPROX(Hegemonic::Matrix<T, ROW, COLUMN>& aMatrix1, Hegemonic::Matrix<T, ROW, COLUMN>& aMatrix2, T aError)
{
    for (int i = 0; i < ROW; i++)
    {
        EXPECT_TRUE_ARRAY_APPROX(*aMatrix1.getRow(i).get(), *aMatrix2.getRow(i).get(), aError);
    }
}

template<typename T, std::size_t COUNT>
void EXPECT_TRUE_VECTOR_APPROX(Hegemonic::Vector<T, COUNT>& aVector1, Hegemonic::Vector<T, COUNT>& aVector2, T aError)
{
    EXPECT_TRUE_ARRAY_APPROX(*aVector1.get(), *aVector2.get(), aError);
}