#include "upperrelaxationmethodsolver.h"

Column UpperRelaxationMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    double coeff;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 2);
    coeff = dist(gen);

    Matrix alpha;
    Column beta;
    size_t size = A.size();

    for (size_t i = 0; i < size; i++) {
        beta.push_back(coeff * (b[i] / A[i][i]));
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
    Column result = x;
    if (converge(alpha)) {
        int iterCounter = 0;
        double currentEps = secondVectorNorm(b - (A * result));
        while (currentEps > epsilon) {
          result = (1 - coeff) * result + beta + mul_R(alpha, result, coeff);
          iterCounter++;
          currentEps = secondVectorNorm(b - (A * result));
        }
    } else {
        throw std::runtime_error("Matrix does not converge.");
    }
    return result;
}

bool UpperRelaxationMethodSolver::needApproximation()
{
    return true;
}
