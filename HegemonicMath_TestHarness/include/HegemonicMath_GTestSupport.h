#pragma once

#include <gtest/gtest.h>
#include <array>

template<typename T, std::size_t COUNT>
bool EXPECT_TRUE_ARRAY(std::array<T, COUNT> aArray, T aValue)
{
    for (int i = 0; i < COUNT; i++)
    {
        if (aArray.at(i) != aValue)
        {
            return false;
        }
    }
    return true;
}

template<typename T, std::size_t COUNT>
bool EXPECT_TRUE_ARRAY(std::array<T, COUNT> aArray1, std::array<T, COUNT> aArray2)
{
    for (int i = 0; i < COUNT; i++)
    {
        if (aArray1.at(i) != aArray2.at(i))
        {
            return false;
        }
    }
    return true;
}