#ifndef GAUSSMETHODSOLVER_H
#define GAUSSMETHODSOLVER_H

#include "lesystemsolver.h"

class GaussMethodSolver : public LESystemSolver
{
public:
    GaussMethodSolver() = default;
    ~GaussMethodSolver() = default;

    Column solve(const Matrix& A,
                 const Column& b,
                 const Column& = Column(),
                 double = 0) override;
    bool needApproximation() override;
};

#endif // GAUSSMETHODSOLVER_H
