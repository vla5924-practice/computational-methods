#include "lesystemsolver.h"

double LESystemSolver::determinant(const Matrix& A) {
    size_t size = A.size();
    double det = 0;
    if (size == 2) {
        det = A[0][0] * A[1][1] - A[1][0] * A[0][1];
        return  det;
    }
    for (size_t i = 0; i < size; i++) {
        Matrix tmp = A;
        tmp.erase(tmp.begin());
        for (size_t j = 0; j < tmp.size(); j++) {
            tmp[j].erase(tmp[j].begin() + i);
        }
          det += pow(-1, static_cast<int>(i) + 2) * A[0][i] * determinant(tmp);
        }
    return det;
}

Column LESystemSolver::subtr(const Column& v1, const Column& v2) {
    Column result(v1.size());
  if (v1.size() != v2.size()) {
    // TODO
  }
  else {
    size_t size = v1.size();
    for (size_t i = 0; i < size; i++) {
      result[i] = v1[i] - v2[i];
    }
  }
  return result;
}

Column LESystemSolver::mul_Z(Matrix A, Column v) {
  size_t size = v.size();
  Column res(size);
  for (size_t i = 0; i < size; i++) {
    double sum = 0;
    for (size_t j = 0; j < size; j++) {
      sum += A[i][j] * v[j];
    }
    res[i] = sum;
  }
  return res;
}

Column LESystemSolver::mul_R(Matrix A, Column v, const double& coeff) {
  size_t size = v.size();
  Column res(size);
  for (size_t i = 0; i < size; i++) {
    double sum = 0;
    for (size_t j = 0; j < size; j++) {
      sum += A[i][j] * v[j];
    }
    res[i] = coeff * sum;
  }
  return res;
}

Column LESystemSolver::sum(Column v1, Column v2) {
  size_t size = v1.size();
  Column res(size);
  if (v1.size() != v2.size()) {
    return res;
  }
  for (size_t i = 0; i < size; i++) {
    res[i] = v1[i] + v2[i];
  }
  return res;
}

double LESystemSolver::secondVectorNorm(const Column& v) {
  double tmpSum = 0;
  for (double val : v) {
    tmpSum += pow(val, 2);
  }
  return sqrt(tmpSum);
}

bool LESystemSolver::converge(const Matrix& A) {
    double sum = 0;
    for (std::vector<double> v : A) {
        for (double val : v) {
        sum += pow(val, 2);
        }
    }
    double eNorm = sqrt(sum);
  return (eNorm < 1);
}
