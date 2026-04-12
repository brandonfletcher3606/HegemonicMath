#pragma once

#include <iomanip>
#include <sstream>
#include <string>
#include "Matrix.h"
#include "Vector.h"

void print()
{
    std::cout << " ";
}

void printEndLine()
{
    std::cout << std::endl;
}

void setPrecision(int aValue)
{
    std::cout << std::setprecision(aValue);
}

template<typename T>
void print(T aValue)
{
    std::cout << aValue;
    print();
}

template<typename T, typename... TYPES>
void print(T aValue, TYPES... aValues)
{
    print(aValue);
    print(aValues...);
}

template<typename T, std::size_t COUNT>
void printArray(std::array<T, COUNT> aArray)
{
    for (int i = 0; i < COUNT; i++)
    {
        print(aArray.at(i));
    }
    printEndLine();
}

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
void printMatrix(const Hegemonic::Matrix<T, ROWS, COLUMNS> aMatrix)
{
    for (int i = 0; i < ROWS; i++)
    {
        printArray(*aMatrix.getRow(i).get());
    }
};

template<typename T, std::size_t COUNT>
void printVector(const Hegemonic::Vector<T, COUNT> aVector)
{
    printArray(*aVector.get());
}