#pragma once

#include <sstream>
#include <string>
#include "Matrix.h"
#include "Vector.h"

template<typename T, std::size_t ROWS, std::size_t COLUMNS>
void printMatrix(const Hegemonic::Matrix<T, ROWS, COLUMNS> aMatrix)
{
    std::stringstream ss;
    for (int i = 0; i < aMatrix.getNumberRows(); i++)
    {
        for (int j = 0; j < aMatrix.getNumberColumns(); j++)
        {
            ss << std::to_string(aMatrix.getElement(i, j)) << " ";
        }
        std::cout << ss.str() << std::endl;
        ss.clear();
        ss.str("");
    }
};

template<typename T, std::size_t COUNT>
void printVector(const Hegemonic::Vector<T, COUNT> aVector)
{
    for (int i = 0; i < aVector.getSize(); i++)
    {
        std::cout << aVector.getElement(i) << " " << std::endl;
    }
}