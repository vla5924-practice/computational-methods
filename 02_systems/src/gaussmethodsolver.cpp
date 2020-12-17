#include "gaussmethodsolver.h"

Column GaussMethodSolver::solve(const Matrix& A, const Column& b, const Column&, double)
{
    if(hasZerosDiagonal(A))
        throw std::runtime_error("Matrix has at least 1 zero on diagonal, the permutation of rows can be used to deal with it but it is not implemented yet.");

    Matrix A_ = A;
    Column B_ = b;
    int i, j, k;
    int n = static_cast<int>(b.size());
    for (j = 0; j < n; j++)
    {
        double alfa = 0;
        for (i = j + 1; i < n; i++)
        {
            alfa = A_[i][j] / A_[j][j];
            for (k = j; k < n; k++)
            {
                A_[i][k] -= alfa * A_[j][k];
            }
            B_[i] -= alfa * B_[j];
        }

    }
    Column result(n, 0);
    result[n - 1] = B_[n - 1] / A_[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--)
    {
        double sum = 0;
        for (j = i + 1; j < n; j++)
        {
            sum += A_[i][j] * result[j];
        }
        result[i] = (B_[i] - sum) / A_[i][i];
    }
    return result;
}

bool GaussMethodSolver::needApproximation()
{
    return false;
}
