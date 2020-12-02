#include "ludecompositionmethodsolver.h"

Column LUDecompositionMethodSolver::solve(const Matrix& A, const Column& b, const Column&, double)
{
    size_t size = A.size();
    Matrix L(size), U(size);

    for (size_t i = 0; i < size; i++) {
        L[i].resize(size);
        U[i].resize(size);
        U[0][i] = A[0][i];
        L[i][0] = A[i][0] / U[0][0];
    }

    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = i; j < size; j++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < i; k++)
            {
                sum += L[i][k] * U[k][j];
            }

            U[i][j] = A[i][j] - sum;
        }

        for (size_t j = i; j < size; j++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < i; k++)
            {
                sum += L[j][k] * U[k][i];
            }

            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }

    Column y(size, 0);
    for (size_t i = 0; i < size; i++)
    {
        double sum = 0.0;
        for (size_t j = 0; j < i; j++)
        {
            sum += L[i][j] * y[j];
        }

        y[i] = b[i] - sum;
    }

    Column result(size, 0);
    for (int i = size - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (size_t j = i + 1; j < size; j++)
        {
            sum += U[i][j] * result[j];
        }

        result[i] = (y[i] - sum) / U[i][i];
    }

    return result;
}

bool LUDecompositionMethodSolver::needApproximation()
{
    return false;
}
