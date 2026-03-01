#include <gtest/gtest.h>
#include <Matrix.h>
#include "HegemonicMath_PrinterSupport.h"

/**
 * INFO: Matrix test to test initialization to zero
 */
TEST(Matrix, MatrixInitialization)
{
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(m.getElement(i, j) == 0.0);
        }
    }
}

/**
 * INFO: Matrix test to test initialization to other than zero using array of arrays
 */
TEST(Matrix, MatrixInitializationNonZero)
{
    std::array<std::array<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(m.getElement(i, j) == a.at(i).at(j));
        }
    }
}

/**
 * INFO: Matrix test to test if matrix is a square matrix
 */
TEST(Matrix, MatrixIsSquare)
{
    std::array<std::array<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    EXPECT_TRUE(m.isSquare());
}

/**
 * INFO: Matrix test to test getting correct element, note same as initialzation non zero test
 */
TEST(Matrix, MatrixGetElement)
{
    std::array<std::array<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(m.getElement(i, j) == a.at(i).at(j));
        }
    }
}

/**
 * INFO: Matrix test to test out of range for get element on both rows and columns
 */
TEST(Matrix, MatrixGetElementOutOfRange)
{
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>();
    EXPECT_THROW(m.getElement(10, 1), std::out_of_range); // rows
    EXPECT_THROW(m.getElement(1, 10), std::out_of_range); // columns
}

/**
 * INFO: Matrix test to test if matrix get rows returns correct number of rows
 */
TEST(Matrix, MatrixGetRows)
{
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>();
    EXPECT_TRUE(m.getNumberRows() == 3);
}

/**
 * INFO: Matrix test to test if matrix get rows returns correct number of columns
 */
TEST(Matrix, MatrixGetColumns)
{
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>();
    EXPECT_TRUE(m.getNumberColumns() == 4);
}

/**
 * INFO: Matrix test to test getting array of array
 */
TEST(Matrix, MatrixGet)
{
    std::array<std::array<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    std::array<std::array<double, 3>, 3> b = m.get();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(b.at(i).at(j) == a.at(i).at(j));
        }
    }
}

/**
 * INFO: Matrix test to test getting a row
 */
TEST(Matrix, MatrixGetRow)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    std::array<double, 4> b = m.getRow(0);
    for (int i = 0; i < m.getNumberColumns(); i++)
    {
        EXPECT_TRUE(m.getElement(0, i) == b.at(i));
    }
}

/**
 * INFO: Matrix test to test getting a column
 */
TEST(Matrix, MatrixGetColumn)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    std::array<double, 3> b = m.getColumn(1);
    for (int i = 0; i < m.getNumberRows(); i++)
    {
        EXPECT_TRUE(m.getElement(i, 1) == b.at(i));
    }
}

/**
 * INFO: Matrix test to test setting an element
 */
TEST(Matrix, MatrixSetElement)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    m.setElement(500.0, 1, 2);
    EXPECT_TRUE(m.getElement(1, 2) == 500.0);
}

/**
 * INFO: Matrix test to test setting an element out of range
 */
TEST(Matrix, MatrixSetElementOutOfRange)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    m.setElement(500.0, 1, 2);
    EXPECT_THROW(m.setElement(500.0, 25, 2), std::out_of_range); // row
    EXPECT_THROW(m.setElement(500.0, 1, 25), std::out_of_range); // column
}

/**
 * INFO: Matrix test to test getting submatrix using row and column indexs
 */
TEST(Matrix, MatrixGetSubMatrixRowColumnIndexs)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    std::array<std::size_t, 2> rowIndexs = {0, 1};
    std::array<std::size_t, 2> columnIndexs = {1, 3};
    Hegemonic::Matrix<double, 2, 2> subMatrix = m.getSubMatrix<2, 2>(rowIndexs, columnIndexs);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            EXPECT_TRUE(m.getElement(rowIndexs.at(i), columnIndexs.at(j)) == subMatrix.getElement(i, j));
        }
    }
}

/**
 * INFO: Matrix test to test getting submatrix using row and column indexs out of range
 */
TEST(Matrix, MatrixGetSubMatrixRowColumnIndexsOutOfRange)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    std::array<std::size_t, 2> rowIndexs = {50, 1};
    std::array<std::size_t, 2> columnIndexs = {1, 3};
    EXPECT_THROW((m.getSubMatrix<2, 2>(rowIndexs, columnIndexs)), std::out_of_range);

    rowIndexs = {0, 1};
    columnIndexs = {1, 50};
    EXPECT_THROW((m.getSubMatrix<2, 2>(rowIndexs, columnIndexs)), std::out_of_range);
}

/**
 * INFO: Matrix test to test getting submatrix using start and delta for rows and columns
 */
TEST(Matrix, MatrixGetSubMatrix)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Matrix<double, 2, 2> subMatrix = m.getSubMatrix<0, 2, 1, 2>();

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            EXPECT_TRUE(m.getElement(i+0, j+1) == subMatrix.getElement(i, j));
        }
    }
}

/**
 * INFO: Matrix test to test getting submatrix using start and delta for rows and columns out of range
 */
TEST(Matrix, MatrixGetSubMatrixOutOfRange)
{
    std::array<std::array<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Matrix<double, 2, 2> subMatrix = m.getSubMatrix<0, 2, 1, 2>();
    EXPECT_THROW((m.getSubMatrix<50, 2, 1, 2>()), std::out_of_range);
    EXPECT_THROW((m.getSubMatrix<0, 50, 1, 2>()), std::out_of_range);
    EXPECT_THROW((m.getSubMatrix<0, 2, 50, 2>()), std::out_of_range);
    EXPECT_THROW((m.getSubMatrix<0, 2, 1, 50>()), std::out_of_range);
}