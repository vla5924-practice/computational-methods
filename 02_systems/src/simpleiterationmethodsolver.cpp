#include "simpleiterationmethodsolver.h"

Column SimpleIterationMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    if(hasZerosDiagonal(A))
        throw std::runtime_error("Matrix has at least 1 zero on diagonal.");
    size_t size = b.size();
    Column result = x, x_;
    if (diagonal(A)) {
        do {
            x_ = result;
            for (size_t i = 0; i < size; i++)
            {
                double var = 0;
                for (size_t j = 0; j < i; j++) {
                        var += (A[i][j] * x_[j]);
                }
                for (size_t j = i + 1; j < size; j++) {
                        var += (A[i][j] * x_[j]);
                }
                result[i] = (b[i] - var) / A[i][i];
            }
        } while (!converge(result, x, epsilon));
    } else {
        throw std::runtime_error("Matrix does not converges.");
    }
    return result;
}

bool SimpleIterationMethodSolver::needApproximation()
{
    return true;
}
