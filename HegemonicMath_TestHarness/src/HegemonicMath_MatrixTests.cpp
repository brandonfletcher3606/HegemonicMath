#include <gtest/gtest.h>
#include "HegemonicMath_GTestSupport.h"

/**
 * INFO: Test rotation function
 */
TEST(Matrix_Rotation, Rotation)
{
    Hegemonic::Matrix22d m = Hegemonic::rotation(0.0);
    std::array<std::array<double, 2>, 2> a = {{ {1.0, 0.0}, {0.0, 1.0} }};
    Hegemonic::Vector<Hegemonic::Vector<double, 2>, 2> b = *m.get();

    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 2>(a.at(0), *b[0].get(), 0.00000001);
    EXPECT_TRUE_ARRAY_APPROX<double, 2>(a.at(1), *b[1].get(), 0.00000001);
}

/**
 * INFO: Test rotationX function
 */
TEST(Matrix_Rotation, RotationX)
{
    Hegemonic::Matrix33d m = Hegemonic::rotationX(0.0);
    std::array<std::array<double, 3>, 3> a = {{ {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} }};
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> b = *m.get();

    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(0), *b[0].get(), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(1), *b[1].get(), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(2), *b[2].get(), ce.DOUBLE);
}

/**
 * INFO: Test RotationY function
 */
TEST(Matrix_Rotation, RotationY)
{
    Hegemonic::Matrix33d m = Hegemonic::rotationY(0.0);
    std::array<std::array<double, 3>, 3> a = {{ {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} }};
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> b = *m.get();

    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(0), *b[0].get(), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(1), *b[1].get(), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(2), *b[2].get(), ce.DOUBLE);
}

/**
 * INFO: Test RotationZ function
 */
TEST(Matrix_Rotation, RotationZ)
{
    Hegemonic::Matrix33d m = Hegemonic::rotationZ(0.0);
    std::array<std::array<double, 3>, 3> a = {{ {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} }};
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> b = *m.get();

    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(0), *b[0].get(), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(1), *b[1].get(), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(a.at(2), *b[2].get(), ce.DOUBLE);
}

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
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(m.getElement(i, j) == a[i][j]);
        }
    }
}

/**
 * INFO: Matrix test to test if matrix is a square matrix
 */
TEST(Matrix, MatrixIsSquare)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    EXPECT_TRUE(m.isSquare());
}

/**
 * INFO: Matrix test to test getting correct element, note same as initialzation non zero test
 */
TEST(Matrix, MatrixGetElement)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(m.getElement(i, j) == a[i][j]);
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
TEST(Matrix, MatrixGetNumberRows)
{
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>();
    EXPECT_TRUE(m.getNumberRows() == 3);
}

/**
 * INFO: Matrix test to test if matrix get rows returns correct number of columns
 */
TEST(Matrix, MatrixGetNumberColumns)
{
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>();
    EXPECT_TRUE(m.getNumberColumns() == 4);
}

/**
 * INFO: Matrix test to test getting array of array
 */
TEST(Matrix, MatrixGet)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> b = *m.get();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(b[i][j] == a[i][j]);
        }
    }
}

/**
 * INFO: Matrix test to test getting a row
 */
TEST(Matrix, MatrixGetRow)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Vector<double, 4> b = m.getRow(0);
    for (int i = 0; i < m.getNumberColumns(); i++)
    {
        EXPECT_TRUE(m.getElement(0, i) == b.getElement(i));
    }
}

/**
 * INFO: Matrix test to test getting rows
 */
TEST(Matrix, MatrixGetRows)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Matrix<double, 2, 4> bm = m.getRows<2>({0, 1});
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 2> b = *bm.get();
    Hegemonic::Matrix<double, 2, 4> c = m.getSubMatrix<2, 4>({0, 1}, {0, 1, 2, 3});

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            EXPECT_TRUE(c.getElement(i, j) == b[i][j]);
        }
    }
}

/**
 * INFO: Matrix test to test getting a column
 */
TEST(Matrix, MatrixGetColumn)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Vector<double, 3> b = m.getColumn(1);
    for (int i = 0; i < m.getNumberRows(); i++)
    {
        EXPECT_TRUE(m.getElement(i, 1) == b.getElement(i));
    }
}

/**
 * INFO: Matrix test to test getting columns
 */
TEST(Matrix, MatrixGetColumns)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Matrix<double, 2, 3> bm = m.getColumns<2>({0, 3});
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 2> b = *bm.get();
    Hegemonic::Matrix<double, 3, 2> c = m.getSubMatrix<3, 2>({0, 1, 2}, {0, 3});

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            EXPECT_TRUE(c.getElement(i, j) == b[j][i]);
        }
    }
}

/**
 * INFO: Matrix test to test setting an element
 */
TEST(Matrix, MatrixSetElement)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    m.setElement(500.0, 1, 2);
    EXPECT_TRUE(m.getElement(1, 2) == 500.0);
}

/**
 * INFO: Matrix test to test setting an element out of range
 */
TEST(Matrix, MatrixSetElementOutOfRange)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
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
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Vector<std::size_t, 2> rowIndexs = {0, 1};
    Hegemonic::Vector<std::size_t, 2> columnIndexs = {1, 3};
    Hegemonic::Matrix<double, 2, 2> subMatrix = m.getSubMatrix<2, 2>(rowIndexs, columnIndexs);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            EXPECT_TRUE(m.getElement(rowIndexs[i], columnIndexs[j]) == subMatrix.getElement(i, j));
        }
    }
}

/**
 * INFO: Matrix test to test getting submatrix using row and column indexs out of range
 */
TEST(Matrix, MatrixGetSubMatrixRowColumnIndexsOutOfRange)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Vector<std::size_t, 2> rowIndexs = {50, 1};
    Hegemonic::Vector<std::size_t, 2> columnIndexs = {1, 3};
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
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
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
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Matrix<double, 2, 2> subMatrix = m.getSubMatrix<0, 2, 1, 2>();
    EXPECT_THROW((m.getSubMatrix<50, 2, 1, 2>()), std::out_of_range);
    EXPECT_THROW((m.getSubMatrix<0, 50, 1, 2>()), std::out_of_range);
    EXPECT_THROW((m.getSubMatrix<0, 2, 50, 2>()), std::out_of_range);
    EXPECT_THROW((m.getSubMatrix<0, 2, 1, 50>()), std::out_of_range);
}

/**
 * INFO: Matrix test to test getting submatrix using a row and column index to get rid of
 */
TEST(Matrix, MatrixGetSubMatrixGetCofactor)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Matrix<double, 2, 3> subMatrix = m.getSubMatrix(1, 3);
    std::size_t r = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i != 1)
        {
            std::size_t c = 0;
            for (int j = 0; j < 4; j++)
            {
                if (j != 3)
                {
                    EXPECT_TRUE(m.getElement(i, j) == subMatrix.getElement(r, c));
                    c += 1;
                }
            }
            r += 1;
        }
    }
}

/**
 * INFO: Matrix test to test getting submatrix using a row and column index to get rid of, out of range
 */
TEST(Matrix, MatrixGetSubMatrixGetCofactorOutOfRange)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    EXPECT_THROW(m.getSubMatrix(10, 3), std::out_of_range);
    EXPECT_THROW(m.getSubMatrix(1, 30), std::out_of_range);
}

/**
 * INFO: Matrix test to test getting cofactor
 */
TEST(Matrix, MatrixGetCofactor)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    Hegemonic::Matrix<double, 2, 3> subMatrix = m.getCofactor(1, 3);
    std::size_t r = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i != 1)
        {
            std::size_t c = 0;
            for (int j = 0; j < 4; j++)
            {
                if (j != 3)
                {
                    EXPECT_TRUE(m.getElement(i, j) == subMatrix.getElement(r, c));
                    c += 1;
                }
            }
            r += 1;
        }
    }
}

/**
 * INFO: Matrix test to test getting trace
 */
TEST(Matrix, MatrixGetTrace)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    EXPECT_TRUE(m.getTrace() == 15.0);
}

/**
 * INFO: Matrix test to test getting trace, non square matrix
 */
TEST(Matrix, MatrixGetTraceNonSquare)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 3> a = {{ {1.0, 2.0, 3.0, 10.0}, {4.0, 5.0, 6.0, 11.0}, {7.0, 8.0, 9.0, 12.0} }};
    Hegemonic::Matrix<double, 3, 4> m = Hegemonic::Matrix<double, 3, 4>(a);
    EXPECT_THROW(m.getTrace(), std::logic_error);
}

/**
 * INFO: Matrix test to test getting determinat of 4x4 matrix
 */
TEST(Matrix, MatrixGetDeterminantMatrix44)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 4>, 4> a = {{ {12, 4, 6, 7}, {1, 2, 1, 12}, {4, 7, 17, 2}, {1, 21, 4, 9} }};
    Hegemonic::Matrix<double, 4, 4> m = Hegemonic::Matrix<double, 4, 4>(a);
    double determinant = m.getDeterminant();
    EXPECT_TRUE(determinant = -37532);
}

/**
 * INFO: Matrix test to test getting determinat of 3x3 matrix
 */
TEST(Matrix, MatrixGetDeterminantMatrix33)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {12, 4, 19}, {0, 0, 1}, {37, 2, 5} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    double determinant = m.getDeterminant();
    EXPECT_TRUE(determinant == 124);
}

/**
 * INFO: Matrix test to test getting determinat of 2x2 matrix
 */
TEST(Matrix, MatrixGetDeterminantMatrix22)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 2>, 2> a = {{ {12, 4}, {37, 2} }};
    Hegemonic::Matrix<double, 2, 2> m = Hegemonic::Matrix<double, 2, 2>(a);
    double determinant = m.getDeterminant();
    EXPECT_TRUE(determinant == -124);
}

/**
 * INFO: Matrix test to test setAll 
 */
TEST(Matrix, MatrixSetAll)
{
    Hegemonic::Matrix<double, 2, 2> m = Hegemonic::Matrix<double, 2, 2>();
    m.setAll(3.0);
    Hegemonic::Vector<Hegemonic::Vector<double, 2>, 2> data = *m.get();

    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 2>(*data[0].get(), 3.0, ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 2>(*data[1].get(), 3.0, ce.DOUBLE);
}

/**
 * INFO: Matrix test to test setTransposed 
 */
TEST(Matrix, MatrixSetTransposed)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 2>, 2> a = {{ {12, 4}, {37, 2} }};
    Hegemonic::Matrix<double, 2, 2> m = Hegemonic::Matrix<double, 2, 2>(a);
    m.setTransposed();
    std::array<std::array<double, 2>, 2> comparison = {{ {12, 37}, {4, 2} }};
    Hegemonic::Vector<Hegemonic::Vector<double, 2>, 2> data = *m.get();

    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 2>(*data[0].get(), comparison.at(0), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 2>(*data[1].get(), comparison.at(1), ce.DOUBLE);
}

/**
 * INFO: Matrix test to test setTransposed 
 */
TEST(Matrix, MatrixSetTransposedNonSquare)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 2> a = {{ {12, 4, 5}, {37, 2, 5} }};
    Hegemonic::Matrix<double, 2, 3> m = Hegemonic::Matrix<double, 2, 3>(a);
    EXPECT_THROW(m.setTransposed(), std::logic_error);
}

/**
 * INFO: Matrix test to test static function identity 
 */
TEST(Matrix, MatrixStaticIdentity)
{
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d::identity();
    std::array<std::array<double, 3>, 3> a = {{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }};
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> raw = *m.get();

    ERROR ce;
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(*raw[0].get(), a.at(0), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(*raw[1].get(), a.at(1), ce.DOUBLE);
    EXPECT_TRUE_ARRAY_APPROX<double, 3>(*raw[2].get(), a.at(2), ce.DOUBLE);
}

/**
 * INFO: Matrix test to test isInvertable 
 */
TEST(Matrix, MatrixIsInvertable)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 12.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    EXPECT_TRUE(m.isInvertable());
}

/**
 * INFO: Matrix test to test overload operator()
 */
TEST(Matrix, MatrixOverloadOperatorGetElement)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>(a);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            EXPECT_TRUE(*m(i, j) == a[i][j]);
        }
    }
}

/**
 * INFO: Matrix test to test overload operator() out of range
 */
TEST(Matrix, MatrixOverloadOperatorGetElementOutOfRange)
{
    Hegemonic::Matrix<double, 3, 3> m = Hegemonic::Matrix<double, 3, 3>();
    EXPECT_THROW(m(10, 1), std::out_of_range); // rows
    EXPECT_THROW(m(1, 10), std::out_of_range); // columns
}

/**
 * INFO: Matrix test to test overload operator()*
 */
TEST(MatrixOverloadOperators, MultMatrix2Matrix)
{
    Hegemonic::Matrix33d m1 = Hegemonic::rotationX<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m2 = Hegemonic::rotationY<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m3 = m1 * m2;

    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ { 0.707388269167200, 0.00000000000000,  0.706825181105366}, 
                                                              { 0.499601836644633, 0.70738826916720, -0.499999841465917}, 
                                                              {-0.499999841465917, 0.706825181105366, 0.500398163355367} }};

    Hegemonic::Matrix33d comparisionMatrix = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(m3, comparisionMatrix, er.DOUBLE);
}

/**
 * INFO: Matrix test to test overload operator()+
 */
TEST(MatrixOverloadOperators, AddMatrix2Matrix)
{
    Hegemonic::Matrix33d m1 = Hegemonic::Matrix33d();
    m1.setAll(1.0);
    Hegemonic::Matrix33d m2 = Hegemonic::Matrix33d();
    m2.setAll(1.0);
    Hegemonic::Matrix33d m3 = m1 + m2;

    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {2.0, 2.0, 2.0}, 
                                                              {2.0, 2.0, 2.0}, 
                                                              {2.0, 2.0, 2.0} }};

    Hegemonic::Matrix33d comparisionMatrix = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(m3, comparisionMatrix, er.DOUBLE);
}

/**
 * INFO: Matrix test to test overload operator()-
 */
TEST(MatrixOverloadOperators, SubtrackMatrix2Matrix)
{
    Hegemonic::Matrix33d m1 = Hegemonic::Matrix33d();
    m1.setAll(1.0);
    Hegemonic::Matrix33d m2 = Hegemonic::Matrix33d();
    m2.setAll(1.0);
    Hegemonic::Matrix33d m3 = m1 - m2;

    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {0.0, 0.0, 0.0}, 
                                                              {0.0, 0.0, 0.0}, 
                                                              {0.0, 0.0, 0.0} }};

    Hegemonic::Matrix33d comparisionMatrix = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(m3, comparisionMatrix, er.DOUBLE);
}

/**
 * INFO: Matrix test to test overload operator()*
 */
TEST(MatrixOverloadOperators, MultiplyMatrix2Scale)
{
    Hegemonic::Matrix33d m1 = Hegemonic::Matrix33d();
    m1.setAll(1.0);
    Hegemonic::Matrix33d m3 = m1 * 2.0;

    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {2.0, 2.0, 2.0}, 
                                                              {2.0, 2.0, 2.0}, 
                                                              {2.0, 2.0, 2.0} }};

    Hegemonic::Matrix33d comparisionMatrix = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(m3, comparisionMatrix, er.DOUBLE);
}

/**
 * INFO: Matrix test to test overload operator()*
 */
TEST(MatrixOverloadOperators, MultiplyScale2Matrix)
{
    Hegemonic::Matrix33d m1 = Hegemonic::Matrix33d();
    m1.setAll(1.0);
    Hegemonic::Matrix33d m3 = 2.0 * m1;

    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {2.0, 2.0, 2.0}, 
                                                              {2.0, 2.0, 2.0}, 
                                                              {2.0, 2.0, 2.0} }};

    Hegemonic::Matrix33d comparisionMatrix = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(m3, comparisionMatrix, er.DOUBLE);
}

/**
 * INFO: Matrix test to test overload operator()*
 */
TEST(MatrixOverloadOperators, MultiplyMatrix2Vector)
{
    Hegemonic::Matrix33d m1 = Hegemonic::rotationX<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m2 = Hegemonic::rotationY<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m3 = Hegemonic::rotationZ<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m4 = m3 * m2 * m1;

    Hegemonic::Vector3d vIn = Hegemonic::Vector3d({1.0, 1.0, 1.0});
    Hegemonic::Vector3d vOut = m4 * vIn;

    Hegemonic::Vector3d vTest = Hegemonic::Vector3d({1.20710665946933, 1.20694180051908, 0.293572823715918});

    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(vOut, vTest, er.DOUBLE);
}

/**
 * INFO: Matrix test to test overload operator()*
 */
TEST(MatrixOverloadOperators, MultiplyVector2Matrix)
{
    Hegemonic::Matrix33d m1 = Hegemonic::rotationX<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m2 = Hegemonic::rotationY<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m3 = Hegemonic::rotationZ<double>(45.0 * 3.14/180.0);
    Hegemonic::Matrix33d m4 = m3 * m2 * m1;

    Hegemonic::Vector3d vIn = Hegemonic::Vector3d({1.0, 1.0, 1.0});
    Hegemonic::Vector3d vOut = vIn * m4;

    Hegemonic::Vector3d vTest = Hegemonic::Vector3d({0.293572823715918, 1.20694180051908, 1.20710665946933});

    ERROR er;
    EXPECT_TRUE_VECTOR_APPROX(vOut, vTest, er.DOUBLE);
}

/**
 * INFO: Matrix test to test setRow(std::array)
 */
TEST(Matrix, MatrixSetRowArray)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d();
    m.setRow(*a[0].get(), 0);
    m.setRow(*a[1].get(), 1);
    m.setRow(*a[2].get(), 2);

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Matrix test to test setRow(Vector)
 */
TEST(Matrix, MatrixSetRowVector)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d();
    m.setRow(a[0], 0);
    m.setRow(a[1], 1);
    m.setRow(a[2], 2);

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Matrix test to test setRow(InitializerList)
 */
TEST(Matrix, MatrixSetRowInitializerList)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d();
    m.setRow({1.0, 2.0, 3.0}, 0);
    m.setRow({4.0, 5.0, 6.0}, 1);
    m.setRow({7.0, 8.0, 9.0}, 2);

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Matrix test to test setColumn(std::array)
 */
TEST(Matrix, MatrixSetColumnArray)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d();
    m.setColumn(*a[0].get(), 0);
    m.setColumn(*a[1].get(), 1);
    m.setColumn(*a[2].get(), 2);
    m.setTransposed();

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);
    c.setTransposed();

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Matrix test to test setColumn(Vector)
 */
TEST(Matrix, MatrixSetColumnVector)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d();
    m.setRow(a[0], 0);
    m.setRow(a[1], 1);
    m.setRow(a[2], 2);
    m.setTransposed();

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);
    c.setTransposed();

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Matrix test to test setColumn(InitializerList)
 */
TEST(Matrix, MatrixSetColumnInitializerList)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d();
    m.setRow({1.0, 2.0, 3.0}, 0);
    m.setRow({4.0, 5.0, 6.0}, 1);
    m.setRow({7.0, 8.0, 9.0}, 2);
    m.setTransposed();

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);
    c.setTransposed();

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Matrix contructor initializer list
 */
TEST(Matrix, MatrixInitializationInitializerListArray)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}, {1.0, 2.0, 3.0} }};
    Hegemonic::Vector<double, 3> b = {1.0, 2.0, 3.0};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d({b, b, b});

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Matrix contructor initializer list
 */
TEST(Matrix, MatrixInitializationInitializerListValue)
{
    Hegemonic::Vector<Hegemonic::Vector<double, 3>, 3> a = {{ {1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}, {1.0, 2.0, 3.0} }};
    std::array<double, 3> b = {1.0, 2.0, 3.0};
    Hegemonic::Matrix33d m = Hegemonic::Matrix33d({1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0});

    Hegemonic::Matrix33d c = Hegemonic::Matrix33d(a);

    ERROR er;
    EXPECT_TRUE_MATRIX_APPROX(c, m, er.DOUBLE);
}

/**
 * INFO: Vector test to test iterators
 */
TEST(MatrixIterator, RowIteratorLoop)
{
    Hegemonic::Matrix33d m = Hegemonic::rotationX(0.0);

    // ranged for loop
    std::size_t count = 0;
    ERROR er;
    for (auto& e : m)
    {
        EXPECT_TRUE_VECTOR_APPROX(e, m[count], er.DOUBLE);
        count++;
    }

    count = 0;
    for (Hegemonic::Matrix<double, 3, 3>::iterator<double> it = m.begin(); it != m.end(); ++it)
    {
        EXPECT_TRUE_VECTOR_APPROX(*it, m[count], er.DOUBLE);
        count++;
    }
}