#include "jacobimethodsolver.h"

Column JacobiMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    size_t size = b.size();
    Column X_(size, 0);
    Column result = x;
    double norm;
    do {
       for (size_t i = 0; i < size; i++) {
           X_[i] = b[i];
           for (size_t g = 0; g < size; g++) {
               if (i != g)
                   X_[i] -= A[i][g] * X_[g];
           }
           X_[i] /= A[i][i];
       }
       norm = fabs(result[0] - X_[0]);
       for (size_t h = 0; h < size; h++) {
           if (fabs(result[h] - X_[h]) > norm)
               norm = fabs(x[h] - X_[h]);
          result[h] = X_[h];
       }
    } while (norm > epsilon);
    return result;
}

bool JacobiMethodSolver::needApproximation()
{
    return true;
}
