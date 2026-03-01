#pragma once

#include <array>
#include <memory>
#include <assert.h>
#include <algorithm>

namespace Hegemonic
{
    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    class Matrix
    {
        public:
            Matrix()
            {
                for (int i = 0; i < getNumberRows(); i++)
                {
                    std::memset(mMatrix[i].data(), 0, sizeof(mMatrix[i]));
                }
            };
            Matrix(std::array<std::array<T, COLUMNS>, ROWS> aMatrix)
            {
                mMatrix = aMatrix;
            }
            ~Matrix() = default;

            // checkers/validators/verifiers
            bool isSquare() const { return mMatrix.size() == mMatrix[0].size(); };
            // bool isInvertable() const { return getDeterminant() != 0 ? true : false; }; // floating point error?

            // // getters
            T getElement(std::size_t aRow, std::size_t aColumn) const 
            { 
                return mMatrix.at(aRow).at(aColumn);
            };
            std::size_t getNumberRows() const { return mMatrix.size(); };
            std::size_t getNumberColumns() const { return mMatrix.at(0).size(); };
            std::array<std::array<T, COLUMNS>, ROWS> get() const { return mMatrix; };
            std::array<T, COLUMNS> getRow(std::size_t aIndex) const
            {
                return mMatrix.at(aIndex);
            }
            std::array<T, ROWS> getColumn(std::size_t aIndex) const
            {
                std::array<T, ROWS> returnArray;
                memset(returnArray.data(), 0, sizeof(returnArray));
                for (int i = 0; i < ROWS; i++)
                {
                    returnArray.at(i) = mMatrix.at(i).at(aIndex);
                }
                return returnArray;
            }
            // getColumns
            // getRows

            template<std::size_t ROW_COUNT, std::size_t COLUMN_COUNT>
            Matrix<T, ROW_COUNT, COLUMN_COUNT> getSubMatrix(std::array<std::size_t, ROW_COUNT> aRows, std::array<std::size_t, COLUMN_COUNT> aColumns) const
            {
                Matrix<T, ROW_COUNT, COLUMN_COUNT> subMatrix = Matrix<T, ROW_COUNT, COLUMN_COUNT>();
                for (int i = 0; i < ROW_COUNT; i++)
                {
                    for (int j = 0; j < COLUMN_COUNT; j++)
                    {
                        subMatrix.setElement(mMatrix.at(aRows.at(i)).at(aColumns.at(j)), i, j);
                    }
                }
                return subMatrix;
            }

            template<std::size_t ROW_START, std::size_t ROW_COUNT, std::size_t COLUMN_START, std::size_t COLUMN_COUNT>
            Matrix<T, ROW_COUNT, COLUMN_COUNT> getSubMatrix() const
            {
                std::size_t numRows = getNumberRows();
                std::size_t numCol = getNumberColumns();

                Matrix<T, ROW_COUNT, COLUMN_COUNT> subMatrix = Matrix<T, ROW_COUNT, COLUMN_COUNT>();
                for (int i = 0; i < ROW_COUNT; i++)
                {
                    for (int j = 0; j < COLUMN_COUNT; j++)
                    {
                        subMatrix.setElement(getElement(i+ROW_START, j+COLUMN_START), i, j);
                    }
                }
                
                return subMatrix;
            }

            Matrix<T, ROWS-1, COLUMNS-1> getSubMatrix(std::size_t aRemoveRowIndex, std::size_t aRemoveColumnIndex) const
            {
                Matrix<T, ROWS-1, COLUMNS-1> returnMatrix = Matrix<T, ROWS-1, COLUMNS-1>();

                return returnMatrix;
            }

            // getCofactor

            // T getDeterminant() const
            // {
                
            // };

			// // T getTrace() const;
            // // Matrix2<T> getAdjoint() const;
			// // Matrix2<T> getInverse() const;
            // // static identity
            // // static rotation

            // // setters
            // // setTransposed
            void setElement(T aValue, std::size_t aRow, std::size_t aColumn)
            { 
                mMatrix.at(aRow).at(aColumn) = aValue;
            };
            // void setAll(T aValue)
            // {
            //     for (int i = 0; i < getNumberRows(); i++)
            //     {
            //         mMatrix[i].fill(aValue);
            //     }
            // }

            // // overload operators

        private:
            std::array<std::array<T, COLUMNS>, ROWS> mMatrix;
    };

    template<class T>
    using Matrix22 = Matrix<T, 2, 2>;

    template<class T> 
    using Matrix33 = Matrix<T, 3, 3>;

    template<class T>
    using Matrix44 = Matrix<T, 4, 4>;

    using Matrix33d = Matrix33<double>;
    using Matrix33i = Matrix33<int>;
    using Matrix22d = Matrix22<double>;
    using Matrix22i = Matrix22<int>;
    using Matrix44d = Matrix44<double>;
    using Matrix44i = Matrix44<int>;
}