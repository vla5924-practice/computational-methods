#ifndef LESYSTEMSOLVER_H
#define LESYSTEMSOLVER_H

#include "matrix.h"

class LESystemSolver
{
public:
    LESystemSolver() = default;
    virtual ~LESystemSolver() = default;

    virtual Column solve(const Matrix& A,
                         const Column& b,
                         const Column& x = Column(),
                         double epsilon = 0) = 0;
    virtual bool needApproximation() = 0;

    static bool converge(const Column& xk, const Column& xkp, double epsilon);
    static bool diagonalPredominant(const Matrix& A);
    static bool hasZerosDiagonal(const Matrix& A);
    static double determinant(const Matrix& A);
    static double secondVectorNorm(const Column& v);
};

#endif // LESYSTEMSOLVER_H
