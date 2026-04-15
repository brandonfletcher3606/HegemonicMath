#pragma once

#include <array>
#include <memory>
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include "HegemonicVector.h"

namespace Hegemonic
{
    // These functions are created for the getDeterminant method, because the method uses a recursive method of calculation
    // the compiler can't evaluate a recursive algorithm that sets an std::array dimensions to zero zero, at the moment,
    // I don't know how to solve this other than hard coding it with functions that check for sizes of 2, 3, and 4
    // This will be solved once the getDeterminant algorithm gets upgraded to using gaussian elimination
    // template<class T>
    // T getDeterminant(std::array<std::array<T, 4>, 4> aInputArray);

    // template<class T>
    // T getDeterminant(std::array<std::array<T, 3>, 3> aInputArray);

    // template<class T>
    // T getDeterminant(std::array<std::array<T, 2>, 2> aInputArray);

    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    class Matrix
    {
        using Value           = T;
        using Pointer         = T*;
        using ConstPointer    = const T*;
        using Reference       = T&;
        using ConstReference  = const T&;

        public:
            // constructors/deconstructors
            Matrix()
            {
                for (int i = 0; i < getNumberRows(); ++i)
                {
                    mMatrix[i] = Hegemonic::Vector<T, COLUMNS>();
                }
            };
            Matrix(Hegemonic::Vector<Hegemonic::Vector<T, COLUMNS>, ROWS> aMatrix) : mMatrix(aMatrix) {};
            Matrix(std::initializer_list<std::array<T, COLUMNS>> aList)
            {
                if (aList.size() != ROWS) { throw std::logic_error("Matrix: constructor: initializer list not correct length"); };
                std::size_t count = 0;
                for (auto element : aList)
                {
                    setRow(element, count);
                    count++;
                }
            }
            Matrix(std::initializer_list<T> aList)
            {
                if (aList.size() != ROWS*COLUMNS) { throw std::logic_error("Matrix: constructor: initializer list not correct length"); };
                std::size_t rowCount = 0;
                std::size_t columnCount = 0;
                for (auto element : aList)
                {
                    setElement(element, rowCount, columnCount);
                    
                    columnCount++;
                    if (columnCount == COLUMNS)
                    {
                        columnCount = 0;
                        rowCount++;
                        if (rowCount == ROWS)
                        {
                            rowCount = 0;
                        }
                    }
                }
            }
            // Matrix(stuff, std::allocator)
            ~Matrix() = default;

            // issers
            bool isSquare() const 
            { 
                return mMatrix.getSize() == mMatrix[0].getSize(); 
            };
            bool isInvertable() const 
            { 
                return getDeterminant() == (T)0 ? false : true; 
            }; // floating point error?

            // getters
            ConstReference getElement(std::size_t aRow, std::size_t aColumn) const 
            { 
                return mMatrix[aRow][aColumn];
            };
            Reference getElement(std::size_t aRow, std::size_t aColumn) 
            { 
                return mMatrix[aRow][aColumn];
            };
            std::size_t getNumberRows() const { return mMatrix.getSize(); };
            std::size_t getNumberColumns() const { return mMatrix[0].getSize(); };
            Vector<Vector<T, COLUMNS>, ROWS>* get() { return &mMatrix; };
            const Vector<Vector<T, COLUMNS>, ROWS>* get() const { return &mMatrix; };
            Vector<T, COLUMNS> getRow(std::size_t aIndex) const
            {
                return mMatrix[aIndex];
            }
            Vector<T, ROWS> getColumn(std::size_t aIndex) const
            {
                Hegemonic::Vector<T, ROWS> returnArray = Hegemonic::Vector<T, ROWS>();
                for (int i = 0; i < ROWS; i++)
                {
                    returnArray.setElement(mMatrix[i][aIndex], i);
                }
                return returnArray;
            }
            Matrix<T, ROWS-1, COLUMNS-1> getSubMatrix(std::size_t aRemoveRowIndex, std::size_t aRemoveColumnIndex) const
            {
                Matrix<T, ROWS-1, COLUMNS-1> returnMatrix = Matrix<T, ROWS-1, COLUMNS-1>();
                std::size_t r = aRemoveRowIndex > 0 ? 0 : 1;
                for (int i = 0; i < ROWS; i++)
                {
                    if (i != aRemoveRowIndex)
                    {
                        std::size_t c = aRemoveColumnIndex > 0 ? 0 : 1;
                        for (int j = 0; j < COLUMNS; j++)
                        {
                            if (j != aRemoveColumnIndex)
                            {
                                returnMatrix.setElement(mMatrix[i][j], r, c);
                                c += 1;
                            }
                        }
                        r += 1;
                    }
                }
                return returnMatrix;
            }
            Matrix<T, ROWS-1, COLUMNS-1> getCofactor(std::size_t aRemoveRowIndex, std::size_t aRemoveColumnIndex) const
            {
                return getSubMatrix(aRemoveRowIndex, aRemoveColumnIndex);
            }
            Matrix<T, COLUMNS, ROWS> getTranspose() const
            {
                Matrix<T, COLUMNS, ROWS> returnMatrix = Matrix<T, COLUMNS, ROWS>(mMatrix);
                returnMatrix.setTransposed();
                return returnMatrix;
            }
            Value getTrace() const
            {
                if (!isSquare()) { throw std::logic_error("MATRIX: getTrace: must be a square matrix"); };

                T returnValue;
                memset(&returnValue, 0, sizeof(T));
                for (int i = 0; i < ROWS; i++)
                {
                    returnValue += mMatrix[i][i];
                }
                return returnValue;
            };
            Value getDeterminant() const
            {
                if (!isSquare()) { throw std::logic_error("MATRIX: getDeterminant: must be a square matrix"); };

                T returnValue;
                memset(&returnValue, 0, sizeof(T));
                
                if (mMatrix.getSize() == 1)
                {
                    returnValue = mMatrix[0][0];
                    return returnValue;
                }

                if (mMatrix.getSize() == 2)
                {
                    returnValue = mMatrix[0][0] * mMatrix[1][1] - mMatrix[0][1] * mMatrix[1][0];
                    return returnValue;
                }

                if (mMatrix.getSize() == 3)
                {
                    T a = mMatrix[0][0];
                    T b = mMatrix[0][1];
                    T c = mMatrix[0][2];
                    T d = mMatrix[1][0];
                    T e = mMatrix[1][1];
                    T f = mMatrix[1][2];
                    T g = mMatrix[2][0];
                    T h = mMatrix[2][1];
                    T i = mMatrix[2][2];

                    returnValue = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

                    return returnValue;
                }

                if (mMatrix.getSize() == 4)
                {
                    T a = mMatrix[0][0];
                    T b = mMatrix[0][1];
                    T c = mMatrix[0][2];
                    T d = mMatrix[0][3];
                    T e = mMatrix[1][0];
                    T f = mMatrix[1][1];
                    T g = mMatrix[1][2];
                    T h = mMatrix[1][3];
                    T i = mMatrix[2][0];
                    T j = mMatrix[2][1];
                    T k = mMatrix[2][2];
                    T l = mMatrix[2][3];
                    T m = mMatrix[3][0];
                    T n = mMatrix[3][1];
                    T o = mMatrix[3][2];
                    T p = mMatrix[3][3];

                    returnValue = (i * b) * (g * p - o * h) +
                                    (-(k * b)) * (e * p - m * h) +
                                    (l * b) * (e * o - m * g) +
                                    (a * f) * (k * p - o * l) +
                                    (-(i * f)) * (c * p - o * d) +
                                    (m * f) * (c * l - k * d) +
                                    (-(a * j)) * (g * p - o * h) +
                                    (c * j) * (e * p - m * h) +
                                    (-(d * j)) * (e * o - m * g) +
                                    (a * n) * (g * l - k * h) +
                                    (-(e * n)) * (c * l - k * d) +
                                    (i * n) * (c * h - g * d);

                    return returnValue;
                }

                // error out otherwise until gausian elimination is used
                throw std::logic_error("MATRIX: getDeterminant: must be a matrix of less than size of 5, algorythm update required");

                // this does not work
                // for (int i = 0; i < getNumberRows(); i++)
                // {
                //     T pnMult;
                //     memset(&pnMult, pow(-1, 1+i), sizeof(T));
                //     Matrix<T, ROWS-1, COLUMNS-1> cf = getCofactor(1, i);
                //     T cv = mMatrix.at(1).at(i);
                //     T dt = cf.getDeterminant();
                //     returnValue += pnMult * cv * dt;             
                // }

                return returnValue;
            };
            
            // getter templates
            template<std::size_t ROW_COUNT>
            Matrix<T, ROW_COUNT, COLUMNS> getRows(Vector<std::size_t, ROW_COUNT> aRows) const
            {
                Vector<Vector<T, COLUMNS>, ROW_COUNT> returnRows;
                for (int i = 0; i < ROW_COUNT; i++)
                {
                    returnRows[i] = getRow(aRows[i]);
                }
                return Matrix<T, ROW_COUNT, COLUMNS>(returnRows);
            };

            template<std::size_t COLUMN_COUNT>
            Matrix<T, COLUMN_COUNT, ROWS> getColumns(Vector<std::size_t, COLUMN_COUNT> aColumns) const
            {
                Vector<Vector<T, ROWS>, COLUMN_COUNT> returnColumns;
                for (int i = 0; i < COLUMN_COUNT; i++)
                {
                    returnColumns[i] = getColumn(aColumns[i]);
                }
                return Matrix<T, COLUMN_COUNT, ROWS>(returnColumns);
            };

            template<std::size_t ROW_COUNT, std::size_t COLUMN_COUNT>
            Matrix<T, ROW_COUNT, COLUMN_COUNT> getSubMatrix(Vector<std::size_t, ROW_COUNT> aRows, Vector<std::size_t, COLUMN_COUNT> aColumns) const
            {
                Matrix<T, ROW_COUNT, COLUMN_COUNT> subMatrix = Matrix<T, ROW_COUNT, COLUMN_COUNT>();
                for (int i = 0; i < ROW_COUNT; i++)
                {
                    for (int j = 0; j < COLUMN_COUNT; j++)
                    {
                        subMatrix.setElement(mMatrix[aRows[i]][aColumns[j]], i, j);
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

            // static
            // // Matrix2<T> getAdjoint() const;
			// // Matrix2<T> getInverse() const;
            static Matrix<T, ROWS, COLUMNS> identity()
            {
                Matrix<T, ROWS, COLUMNS> returnMatrix = Matrix<T, ROWS, COLUMNS>();
                if (!returnMatrix.isSquare()) { throw std::logic_error("MATRIX: identity: must be a square matrix"); };
                for (int i = 0; i < ROWS; i++)
                {
                    returnMatrix.setElement((T)1.0, i, i);
                }
                return returnMatrix;
            }

            // setters
            void setTransposed()
            {
                if (!isSquare()) { throw std::logic_error("MATRIX: getDeterminant: must be a square matrix"); };

                T switchValue;
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < (i+1); j++)
                    {
                        switchValue = mMatrix[i][j];
                        mMatrix[i][j] = mMatrix[j][i];
                        mMatrix[j][i] = switchValue;
                    }
                }
            }
            void setElement(T aValue, std::size_t aRow, std::size_t aColumn)
            {
                mMatrix.getElement(aRow).setElement(aValue, aColumn);
                //mMatrix.at(aRow).at(aColumn) = aValue;
            };
            void setRow(Vector<T, COLUMNS> aRow, std::size_t aIndex)
            {
                if (aIndex >= ROWS) { throw std::logic_error("VECTOR: setRow: index out of range"); };
                for (int i = 0; i < COLUMNS; i++)
                {
                    setElement(aRow.getElement(i), aIndex, i);
                }
            }
            void setRow(std::initializer_list<T> aRow, std::size_t aIndex)
            {
                if (aIndex >= ROWS) { throw std::logic_error("VECTOR: setRow: index out of range"); };
                if (aRow.size() != COLUMNS) { throw std::logic_error("VECTOR: setRow: initializer list not correct length"); };
                int count = 0;
                for (auto element : aRow)
                {
                    setElement(element, aIndex, count);
                    count += 1;
                }
            }
            void setColumn(Vector<T, ROWS> aColumn, std::size_t aIndex)
            {
                if (aIndex >= COLUMNS) { throw std::logic_error("VECTOR: setRow: index out of range"); };
                for (int i = 0; i < ROWS; i++)
                {
                    setElement(aColumn.getElement(i), aIndex, i);
                }
            }
            void setColumn(std::initializer_list<T> aColumn, std::size_t aIndex)
            {
                if (aIndex >= COLUMNS) { throw std::logic_error("VECTOR: setRow: index out of range"); };
                if (aColumn.size() != ROWS) { throw std::logic_error("VECTOR: setColumn: initializer list not correct length"); };
                int count = 0;
                for (auto element : aColumn)
                {
                    setElement(element, aIndex, count);
                    count += 1;
                }
            }
            void setAll(T aValue)
            {
                for (int i = 0; i < getNumberRows(); i++)
                {
                    mMatrix[i].get()->fill(aValue);
                }
            }

            // overload operators
            Pointer operator()(std::size_t aRow, std::size_t aColumn)
            {
                if (aRow >= ROWS) { throw std::out_of_range("MATRIX::operator() index out of range"); };
                if (aColumn >= COLUMNS) { throw std::out_of_range("MATRIX::operator() index out of range"); };
                return &mMatrix[aRow][aColumn];
            }
            ConstPointer operator()(std::size_t aRow, std::size_t aColumn) const
            {
                if (aRow >= ROWS) { throw std::out_of_range("MATRIX::operator() index out of range"); };
                if (aColumn >= COLUMNS) { throw std::out_of_range("MATRIX::operator() index out of range"); };
                return &mMatrix[aRow][aColumn];
            }
            Hegemonic::Vector<Value, COLUMNS>& operator[](std::size_t aIndex)
            {
                if (aIndex >= ROWS) { throw std::out_of_range("MATRIX::operator[] index out of range"); };
                return mMatrix[aIndex];
            }
            const Hegemonic::Vector<Value, COLUMNS>& operator[](std::size_t aIndex) const
            {
                if (aIndex >= ROWS) { throw std::out_of_range("MATRIX::operator[] index out of range"); };
                return getRow(aIndex);
            }

            // iterator functions
            template<class T>
            struct iterator
            {
                // Properties of iterator
                using Category   = std::forward_iterator_tag;
                using Distance   = std::ptrdiff_t;

                // Shorthands
                using Value      = Hegemonic::Vector<T, COLUMNS>;
                using Pointer    = Hegemonic::Vector<T, COLUMNS>*;
                using Reference  = Hegemonic::Vector<T, COLUMNS>&;

                iterator(Pointer aPtr) : mPtr(aPtr) {}

                // overload operators
                Pointer operator->()
                {
                    return mPtr;
                }
                Reference operator*() const
                {
                    return *mPtr;
                }
                iterator<T> operator++() 
                { 
                    ++mPtr; 
                    return *this;
                };
                iterator<T> operator++(int) 
                {
                    iterator<T> tmp = *this;
                    ++(*this);
                    return tmp;
                };
                iterator<T> operator--() 
                { 
                    --mPtr; 
                    return *this;
                };
                iterator<T> operator--(int) 
                {
                    iterator<T> tmp = *this;
                    --(*this);
                    return tmp;
                };
                friend bool operator==(const iterator<T> &aValue1, const iterator<T> &aValue2)
                {
                    return aValue1.mPtr == aValue2.mPtr;
                }
                friend bool operator!=(const iterator<T> &aValue1, const iterator<T> &aValue2)
                {
                    return aValue1.mPtr != aValue2.mPtr;
                }

                private:
                    Pointer mPtr;
            };

            // Iterators functions
            iterator<T> begin()
            {
                return iterator<T>(&mMatrix.get()->data()[0]);
            };
            iterator<T> end()
            {
                return iterator<T>(&mMatrix.get()->data()[mMatrix.getSize()]);
            };
        private:
            Hegemonic::Vector<Hegemonic::Vector<T, COLUMNS>, ROWS> mMatrix;
    };

    template<class T>
    using Matrix22 = Matrix<T, 2, 2>;

    template<class T> 
    using Matrix33 = Matrix<T, 3, 3>;

    template<class T>
    using Matrix44 = Matrix<T, 4, 4>;

    using Matrix22d = Matrix22<double>;
    using Matrix22f = Matrix22<float>;
    using Matrix22i = Matrix22<int>;
    using Matrix33d = Matrix33<double>;
    using Matrix33f = Matrix33<float>;
    using Matrix33i = Matrix33<int>;
    using Matrix44d = Matrix44<double>;
    using Matrix44f = Matrix44<float>;
    using Matrix44i = Matrix44<int>;

    template<class T, std::size_t ROWS, std::size_t INTERSECTION, std::size_t COLUMNS>
    Matrix<T, ROWS, COLUMNS> operator*(const Matrix<T, ROWS, INTERSECTION> &aLeftMatrix, const Matrix<T, INTERSECTION, COLUMNS> &aRightMatrix)
    {
        Matrix<T, ROWS, COLUMNS> returnMatrix = Matrix<T, ROWS, INTERSECTION>();

        for (int i = 0; i < COLUMNS; i++)
        {
            for (int j = 0; j < ROWS; j++)
            {
                T value = (T)0;
                for (int k = 0; k < INTERSECTION; k++)
                {
                    value += aLeftMatrix.getElement(j, k) * aRightMatrix.getElement(k, i);
                }
                returnMatrix.setElement(value, j, i);
            }
        }
        return returnMatrix;
    }

    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    Matrix<T, ROWS, COLUMNS> operator+(const Matrix<T, ROWS, COLUMNS> &aLeftMatrix, const Matrix<T, ROWS, COLUMNS> &aRightMatrix)
    {
        Matrix<T, ROWS, COLUMNS> returnMatrix = Matrix<T, ROWS, COLUMNS>();

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                returnMatrix.setElement(aLeftMatrix.getElement(i, j) + aRightMatrix.getElement(i, j), i, j);
            }
        }
        return returnMatrix;
    }

    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    Matrix<T, ROWS, COLUMNS> operator-(const Matrix<T, ROWS, COLUMNS> &aLeftMatrix, const Matrix<T, ROWS, COLUMNS> &aRightMatrix)
    {
        Matrix<T, ROWS, COLUMNS> returnMatrix = Matrix<T, ROWS, COLUMNS>();

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                returnMatrix.setElement(aLeftMatrix.getElement(i, j) - aRightMatrix.getElement(i, j), i, j);
            }
        }
        return returnMatrix;
    }

    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    Matrix<T, ROWS, COLUMNS> operator*(const Matrix<T, ROWS, COLUMNS> &aMatrix, const T aValue)
    {
        Matrix<T, ROWS, COLUMNS> returnMatrix = Matrix<T, ROWS, COLUMNS>();

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                returnMatrix.setElement(aMatrix.getElement(i, j) * aValue, i, j);
            }
        }
        return returnMatrix;
    }

    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    Matrix<T, ROWS, COLUMNS> operator*(const T aValue, const Matrix<T, ROWS, COLUMNS> &aMatrix)
    {
        Matrix<T, ROWS, COLUMNS> returnMatrix = Matrix<T, ROWS, COLUMNS>();

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                returnMatrix.setElement(aMatrix.getElement(i, j) * aValue, i, j);
            }
        }
        return returnMatrix;
    }

    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    Hegemonic::Vector<T, COLUMNS> operator*(const Matrix<T, ROWS, COLUMNS> &aMatrix, const Vector<T, COLUMNS> &aVector)
    {
        Hegemonic::Vector<T, ROWS> returnVector = Hegemonic::Vector<T, ROWS>();

        for (int i = 0; i < ROWS; i++)
        {
            T value = (T)0;
            for (int j = 0; j < COLUMNS; j++)
            {
                value += aVector.getElement(j) * aMatrix.getElement(i, j);
            }
            returnVector.setElement(value, i);
        }
        return returnVector;
    }

    template<class T, std::size_t ROWS, std::size_t COLUMNS>
    Hegemonic::Vector<T, ROWS> operator*(const Vector<T, ROWS> &aVector, const Matrix<T, ROWS, COLUMNS> &aMatrix)
    {
        Hegemonic::Vector<T, ROWS> returnVector = Hegemonic::Vector<T, ROWS>();

        for (int i = 0; i < COLUMNS; i++)
        {
            T value = (T)0;
            for (int j = 0; j < ROWS; j++)
            {
                value += aVector.getElement(j) * aMatrix.getElement(j, i);
            }
            returnVector.setElement(value, i);
        }
        return returnVector;
    }

    template<class T>
    Matrix22<T> rotation(T aAngle)
    {
        // https://en.wikipedia.org/wiki/Rotation_matrix
        Hegemonic::Vector<Hegemonic::Vector<double, 2>, 2> a = {{ {cos(aAngle), sin(aAngle)}, {-sin(aAngle), cos(aAngle)} }};
        Matrix22<T> returnMatrix = Matrix22<T>(a);
        return returnMatrix;
    }

    template<class T>
    Matrix33<T> rotationX(T aAngle)
    {
        // https://en.wikipedia.org/wiki/Rotation_matrix
        Matrix33<T> returnMatrix = Matrix33<T>();
        
        returnMatrix.setElement((T)1.0, 0, 0);
        returnMatrix.setElement(cos(aAngle), 1, 1);
        returnMatrix.setElement(-sin(aAngle), 1, 2);
        returnMatrix.setElement(sin(aAngle), 2, 1);
        returnMatrix.setElement(cos(aAngle), 2, 2);

        return returnMatrix;
    }

    template<class T>
    Matrix33<T> rotationY(T aAngle)
    {
        // https://en.wikipedia.org/wiki/Rotation_matrix
        Matrix33<T> returnMatrix = Matrix33<T>();
        
        returnMatrix.setElement((T)1.0, 1, 1);
        returnMatrix.setElement(cos(aAngle), 0, 0);
        returnMatrix.setElement(-sin(aAngle), 2, 0);
        returnMatrix.setElement(sin(aAngle), 0, 2);
        returnMatrix.setElement(cos(aAngle), 2, 2);

        return returnMatrix;
    }

    template<class T>
    Matrix33<T> rotationZ(T aAngle)
    {
        // https://en.wikipedia.org/wiki/Rotation_matrix
        Matrix33<T> returnMatrix = Matrix33<T>();
        
        returnMatrix.setElement((T)1.0, 2, 2);
        returnMatrix.setElement(cos(aAngle), 0, 0);
        returnMatrix.setElement(-sin(aAngle), 0, 1);
        returnMatrix.setElement(sin(aAngle), 1, 0);
        returnMatrix.setElement(cos(aAngle), 1, 1);

        return returnMatrix;
    }
};