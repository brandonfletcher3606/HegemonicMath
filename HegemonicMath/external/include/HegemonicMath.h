#pragma once

#include "HegemonicVector.h"
#include "HegemonicMatrix.h"
#include <utility>

namespace Hegemonic
{
    // wrap
    // clamp
    // lerp
    // slerp
    // cross
    // dot
    // angle between vectors
    // normalize vector 
    // normalized vector
    // project
    // reject
    // reflect 
    // linspace
    // repmat
    // zeros
    // ones

    template<typename T>
    T minimum(T aValue1, T aValue2)
    {
        return (aValue1 < aValue2) ? aValue1 : aValue2;
    }

    template<typename T>
    T maximum(T aValue1, T aValue2)
    {
        return (aValue1 < aValue2) ? aValue2 : aValue1;
    }

    template<typename T, std::size_t COUNT>
    std::pair<T, std::size_t> minimum(Hegemonic::Vector<T, COUNT> &aVector)
    {
        std::pair<T, std::size_t> returnValue(aVector.getElement(0), 0);
        for (int i = 1; i < COUNT; i++)
        {
            returnValue.first = minimum(returnValue.first, aVector.getElement(i));
            returnValue.second = returnValue.first == aVector.getElement(i) ? i : returnValue.second;
        }
        return returnValue;
    }

    template<typename T, std::size_t COUNT>
    std::pair<T, std::size_t> maximum(Hegemonic::Vector<T, COUNT> &aVector)
    {
        std::pair<T, std::size_t> returnValue(aVector.getElement(0), 0);
        for (int i = 1; i < COUNT; i++)
        {
            returnValue.first = maximum(returnValue.first, aVector.getElement(i));
            returnValue.second = returnValue.first == aVector.getElement(i) ? i : returnValue.second;
        }
        return returnValue;
    }

    template<typename T, std::size_t ROWS, std::size_t COLUMNS>
    Hegemonic::Vector<std::pair<T, std::size_t>, COLUMNS> minimum(Hegemonic::Matrix<T, ROWS, COLUMNS> &aMatrix)
    {
        Hegemonic::Vector<std::pair<T, std::size_t>, COLUMNS> returnVector = Hegemonic::Vector<std::pair<T, std::size_t>, COLUMNS>();
        std::size_t count = 0;
        for (auto& e : aMatrix)
        {
            returnVector[count] = minimum(e);
            count++;
        }
        return returnVector;
    }

    template<typename T, std::size_t ROWS, std::size_t COLUMNS>
    Hegemonic::Vector<std::pair<T, std::size_t>, COLUMNS> maximum(Hegemonic::Matrix<T, ROWS, COLUMNS> &aMatrix)
    {
        Hegemonic::Vector<std::pair<T, std::size_t>, COLUMNS> returnVector = Hegemonic::Vector<std::pair<T, std::size_t>, COLUMNS>();
        std::size_t count = 0;
        for (auto& e : aMatrix)
        {
            returnVector[count] = maximum(e);
            count++;
        }
        return returnVector;
    }

    template<typename T>
    T clamp(T aMinValue, T aMaxValue, T aValue)
    {
        return (aValue < aMinValue) ? aMinValue : (aValue > aMaxValue) ? aMaxValue : aValue;
    }

    // template<typename T, std::size_t COUNT>
    // Hegemonic::Vector<T, COUNT> clamp(T aMinValue, T aMaxValue, Hegemonic::Vector<T, COUNT> aValue)
    // {
    //     Hegemonic::Vector<T, COUNT> returnVector = Hegemonic::Vector<T, COUNT>();
    //     for (Hegemonic::Vector<T, COUNT>::iterator<T> it = aValue.begin(); it != aValue.end(); ++it)
    //     {
            
    //     }
    //     return returnVector;
    // }
}