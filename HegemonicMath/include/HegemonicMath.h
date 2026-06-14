#pragma once

#include "HegemonicMathDefines.h"
#include "HegemonicMathTypes.h"
#include "HegemonicMathVersion.h"
#include "HegemonicMatrix.h"
#include "HegemonicVector.h"
#include <utility>
#include <cmath>

namespace Hegemonic
{
    // lerp
    // slerp
    // cross
    // dot
    // angle between vectors
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

    template<typename T, std::size_t COUNT>
    void clamp(T aMinValue, T aMaxValue, Hegemonic::Vector<T, COUNT>& aValue)
    {
        for (auto& num : aValue)
        {
            num = clamp(aMinValue, aMaxValue, num);
        }
    }

    template<typename T, std::size_t ROWS, std::size_t COLUMNS>
    void clamp(T aMinValue, T aMaxValue, Hegemonic::Matrix<T, ROWS, COLUMNS> &aMatrix)
    {
        for (auto& num : aMatrix)
        {
            clamp(aMinValue, aMaxValue, num);
        }
    }

    template<typename T>
    T wrap(T aMinValue, T aMaxValue, T aValue)
    {
        T range = aMaxValue - aMinValue;
        return aMinValue + std::fmod(std::fmod(aValue - aMinValue, range) + range, range);
    }

    template<typename T, std::size_t COUNT>
    void wrap(T aMinValue, T aMaxValue, Hegemonic::Vector<T, COUNT>& aValue)
    {
        for (auto& num : aValue)
        {
            num = wrap(aMinValue, aMaxValue, num);
        }
    }

    template<typename T, std::size_t ROWS, std::size_t COLUMNS>
    void wrap(T aMinValue, T aMaxValue, Hegemonic::Matrix<T, ROWS, COLUMNS> &aMatrix)
    {
        for (auto& num : aMatrix)
        {
            wrap(aMinValue, aMaxValue, num);
        }
    }

    template<typename T>
    T lerp(T aStart, T aEnd, T aRatio)
    {
        return aStart + (aEnd - aStart) * aRatio;
    }

    template<typename T, std::size_t COUNT>
    Hegemonic::Vector<T, COUNT> lerp(Hegemonic::Vector<T, COUNT>& aStart, Hegemonic::Vector<T, COUNT>& aEnd, T aRatio)
    {
        Hegemonic::Vector<T, COUNT> returnVector;
        for (int i = 0; i < aStart.getSize(); ++i)
        {
            returnVector.setElement(lerp(aStart[i], aEnd[i], aRatio), i);
        }
        return returnVector;
    }

    template<typename T, std::size_t ROWS, std::size_t COLUMNS>
    Hegemonic::Matrix<T, ROWS, COLUMNS> lerp(Hegemonic::Matrix<T, ROWS, COLUMNS>& aStart, Hegemonic::Matrix<T, ROWS, COLUMNS>& aEnd, T aRatio)
    {
        Hegemonic::Matrix<T, ROWS, COLUMNS> returnMatrix;
        for (int i = 0; i < aStart.getNumberRows(); ++i)
        {
            returnMatrix.setRow(lerp(aStart[i], aEnd[i], aRatio), i);
        }
        return returnMatrix;
    }

    template<typename T, std::size_t COUNT>
    Hegemonic::Vector<T, COUNT> nlerp(Hegemonic::Vector<T, COUNT>& aStart, Hegemonic::Vector<T, COUNT>& aEnd, T aRatio)
    {
        Hegemonic::Vector<T, COUNT> linear = lerp(aStart, aEnd, aRatio);
        linear.setNormalized();
        return linear;
    }

    template<typename T, std::size_t ROWS, std::size_t COLUMNS>
    Hegemonic::Matrix<T, ROWS, COLUMNS> nlerp(Hegemonic::Matrix<T, ROWS, COLUMNS>& aStart, Hegemonic::Matrix<T, ROWS, COLUMNS>& aEnd, T aRatio)
    {
        Hegemonic::Matrix<T, ROWS, COLUMNS> returnMatrix;
        for (int i = 0; i < aStart.getNumberRows(); ++i)
        {
            returnMatrix.setRow(nlerp(aStart[i], aEnd[i], aRatio), i);
        }
        return returnMatrix;
    }


    
    // template<typename T, std::size_t COUNT>
    // Hegemonic::Vector<T, COUNT> slerp(Hegemonic::Vector<T, COUNT>& aStart, Hegemonic::Vector<T, COUNT>& aEnd, T aRatio)
    // {
    //     if (aRatio < 0.01)
    //     {
    //         return lerp(aStart, aEnd, aRatio);
    //     }

    //     Hegemonic::Vector<T, COUNT> from = aStart.getNormalized();
    //     Hegemonic::Vector<T, COUNT> to = aEnd.getNormalized();

    //     T theta = angle(from, to);
    //     T sinTheta = sin(theta);

    //     T a = sin((1 - aRatio) * theta) / sinTheta;
    //     T b = sin(aRatio * theta) / sinTheta;

    //     return from * a + to * b;
    // }
}