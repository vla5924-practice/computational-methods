#include "upperrelaxationmethodsolver.h"

Column UpperRelaxationMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    if(hasZerosDiagonal(A))
        throw std::runtime_error("Matrix has at least 1 zero on diagonal.");
    if (!diagonalPredominant(A))
        throw std::runtime_error("Matrix is not diagonal-predominant.");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 2);
    double coef = dist(gen);
    Matrix alpha;
    Column beta;
    size_t size = A.size();
    Column x_curr = x;
    Column x_prev;
    do
    {
        x_prev = x_curr;
        for (size_t i = 0; i < size; i++)
        {
            double var = 0;
            for (size_t j = 0; j < i; j++)
                var += A[i][j] * x_curr[j];
            for (size_t j = i + 1; j < size; j++)
                var += A[i][j] * x_prev[j];
            x_curr[i] = (b[i] - var) * coef / A[i][i];
        }
    } while (!converge(x_curr, x_prev, epsilon));
    return x_curr;
}

bool UpperRelaxationMethodSolver::convergeMatrix(const Matrix& A)
{
    double sum = 0;
    for (const auto& row : A)
        for (double el : row)
            sum += pow(el, 2);
    return sqrt(sum) < 1;
}

bool UpperRelaxationMethodSolver::needApproximation()
{
    return true;
}
