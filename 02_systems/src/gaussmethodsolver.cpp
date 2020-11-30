#include "gaussmethodsolver.h"

Column GaussMethodSolver::solve(const Matrix& A, const Column& b, const Column&, double)
{
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
