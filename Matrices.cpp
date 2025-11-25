#include "Matrices.h"
//#include <iostream>
#include <vector>
//#include <iomanip>

using namespace std;

namespace Matrices
{
    ///Construct a matrix of the specified size.
    ///Initialize each element to 0.
    Matrix::Matrix(int _rows, int _cols)
    {
        this->rows = _rows;
        this->cols = _cols;
        //resize & initialize
        this->a.resize(_rows);
        for (int i = 0; i < _rows; i++)
        {
            this->a.at(i).resize(_cols, 0.0);
        }
    }


    ///Add each corresponding element.
    ///usage:  c = a + b;
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix ans = Matrix(a.getRows(), a.getCols());
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                ans(i, j) = a(i, j) + b(i, j);
            }
        }

        return ans;
    }

    ///Matrix multiply.
    ///usage:  c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix ans = Matrix(a.getRows(), b.getCols());
        for (int k = 0; k < b.getCols(); k++)
        {
            for (int i = 0; i < a.getRows(); i++)
            {
                //common dimension
                for (int j = 0; j < a.getCols(); j++)
                {
                    ans(i, k) += a(i, j) * b(j, k);
                }
            }
        }

        return ans;
    }

    ///Matrix comparison.
    ///usage:  a == b
    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows()) return false;

        double tor = 0.001;
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if (abs(a(i, j) - b(i, j)) > tor) return false;
            }
        }
        return true;
    }

    ///Matrix comparison.
    ///usage:  a != b
    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(10) << a(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }

    //== Inherited Matrix Classes ==

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {

    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {

    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {

    }

}