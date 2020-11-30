#include "simpleiterationmethodsolver.h"

Column SimpleIterationMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    size_t size = b.size();
    std::vector<double> x0(size);
    int iterCounter = 0;
    Column result = x;
    double currentEps = secondVectorNorm(subtr(b, mul_Z(A, b)));
    while (currentEps > epsilon) {
        for (size_t i = 0; i < size; i++) {
            x0 = result;
            double tmpX = 0;
            for (size_t j = 0; j < size; j++) {
                if (j == i) continue;
                tmpX -= A[i][j] * x0[j];
            }
        result[i] = (tmpX + b[i]) / A[i][i];
        }
        currentEps = secondVectorNorm(subtr(b, mul_Z(A, result)));
        iterCounter++;
    }
    return result;
}

bool SimpleIterationMethodSolver::needApproximation()
{
    return true;
}
