#include "lesystemsolver.h"

bool LESystemSolver::converge(const Column& xk, const Column& xkp, double epsilon)
{
    double norm = 0;
    size_t size = xk.size();
    for (size_t i = 0; i < size; i++)
        norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
    return sqrt(norm) < epsilon;
}

bool LESystemSolver::diagonalPredominant(const Matrix& A)
{
    size_t size = A.size();
    double sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum = 0;
        for (size_t j = 0; j < size; j++)
            sum += abs(A[i][j]);
        sum -= abs(A[i][i]);
        if (sum > A[i][i])
            return false;
    }
    return true;
}

bool LESystemSolver::hasZerosDiagonal(const Matrix& A)
{
    for(size_t i = 0; i < A.size(); i++)
        if(A[i][i] == 0)
            return true;
    return false;
}

double LESystemSolver::determinant(const Matrix& A)
{
    size_t size = A.size();
    if (size == 1)
        return A[0][0];
    if (size == 2)
        return  A[0][0] * A[1][1] - A[1][0] * A[0][1];
    double det = 0;
    for (size_t i = 0; i < size; i++)
    {
        Matrix A_ = A;
        A_.erase(A_.begin());
        for (size_t j = 0; j < A_.size(); j++)
            A_[j].erase(A_[j].begin() + i);
        det += pow(-1, static_cast<int>(i) + 2) * A[0][i] * determinant(A_);
    }
    return det;
}

double LESystemSolver::secondVectorNorm(const Column& v)
{
    double sum = 0;
    for (double el : v)
        sum += pow(el, 2);
    return sqrt(sum);
}
