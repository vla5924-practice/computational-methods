#include "kramermethodsolver.h"

Column KramerMethodSolver::solve(const Matrix& A, const Column& b, const Column&, double)
{
    size_t size = A.size();
    Column dets, result;
    double Adet = determinant(A);
    if (Adet != 0) {
    for (size_t i = 0; i < size; i++) {
        Matrix tmp;
        for (const std::vector<double>& v : A) {
            tmp.push_back(v);
        }
        for (size_t j = 0; j < tmp.size(); j++) {
          tmp[j][i] = b[j];
        }
          dets.push_back(determinant(tmp));
        }
        for (double d : dets) {
          result.push_back(d / Adet);
        }
    }
      else {
            // TODO
      }
    return result;
}

bool KramerMethodSolver::needApproximation()
{
    return false;
}
