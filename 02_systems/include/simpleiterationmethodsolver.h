#ifndef SIMPLEITERATIONMETHODSOLVER_H
#define SIMPLEITERATIONMETHODSOLVER_H

#include "lesystemsolver.h"

class SimpleIterationMethodSolver : public LESystemSolver
{
public:
    SimpleIterationMethodSolver() = default;
    ~SimpleIterationMethodSolver() = default;

    Column solve(const Matrix& A,
                 const Column& b,
                 const Column& x = Column(),
                 double epsilon = 0) override;
    bool needApproximation() override;
};

#endif // SIMPLEITERATIONMETHODSOLVER_H
