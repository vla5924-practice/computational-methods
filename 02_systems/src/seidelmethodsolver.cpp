#include "seidelmethodsolver.h"

Column SeidelMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    Matrix alpha;
    Column beta, result = x;
    size_t size = A.size();
    for (size_t i = 0; i < size; i++) {
        beta.push_back(b[i] / A[i][i]);
      }

      for (const std::vector<double>& v : A) {
        alpha.push_back(v);
      }
      for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
          if (i != j) alpha[i][j] = -(A[i][j] / A[i][i]);
          else alpha[i][j] = 0;
        }
      }

      if (converge(alpha)) {
        int iterCounter = 0;
        double currentEps = secondVectorNorm(b - (A * result));
        while (currentEps > epsilon) {
          result = beta + (alpha * result);
          iterCounter++;
          currentEps = secondVectorNorm(b - (A * result));
        }
      }
      else
          throw std::runtime_error("Matrix does not converges.");
      return result;
}

bool SeidelMethodSolver::needApproximation()
{
    return true;
}
