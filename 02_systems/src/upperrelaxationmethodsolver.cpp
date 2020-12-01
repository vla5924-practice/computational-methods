#include "upperrelaxationmethodsolver.h"

Column UpperRelaxationMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    if(hasZerosDiagonal(A))
        throw std::runtime_error("Matrix has at least 1 zero on diagonal.");
    double coeff;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 2);
    coeff = dist(gen);

    Matrix alpha;
    Column beta;
    size_t size = A.size();

    Column result = x, x_;
    if (diagonal(A)) {
        do {
            x_ = result;
            for (size_t i = 0; i < size; i++)
            {
                double var = 0;
                for (size_t j = 0; j < i; j++)
                    var += (A[i][j] * result[j]);
                for (size_t j = i + 1; j < size; j++)
                    var += (A[i][j] * x_[j]);
                result[i] = (b[i] - var) * coeff / A[i][i];
            }
        } while (!converge(result, x, epsilon));
    } else {
        throw std::runtime_error("Matrix does not converges.");
    }
    return result;
}

bool UpperRelaxationMethodSolver::convergeMatrix(const Matrix& A)
{
    double sum = 0;
    for (std::vector<double> v : A) {
        for (double val : v) {
        sum += pow(val, 2);
        }
    }
    double eNorm = sqrt(sum);
  return (eNorm < 1);
}

bool UpperRelaxationMethodSolver::needApproximation()
{
    return true;
}
