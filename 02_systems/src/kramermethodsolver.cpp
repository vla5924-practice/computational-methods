#include "kramermethodsolver.h"

Column KramerMethodSolver::solve(const Matrix& A, const Column& b, const Column&, double)
{
    size_t size = A.size();
    Column dets, result;
    double det = determinant(A);
    if (det == 0)
        throw std::runtime_error("Matrix determinant equals to zero.");
    for (size_t i = 0; i < size; i++)
    {
        Matrix A_ = A;
        for (size_t j = 0; j < size; j++)
            A_[j][i] = b[j];
        dets.push_back(determinant(A_));
    }
    for (double d : dets)
      result.push_back(d / det);
    return result;
}

bool KramerMethodSolver::needApproximation()
{
    return false;
}
