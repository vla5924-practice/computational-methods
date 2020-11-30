#ifndef JACOBIMETHODSOLVER_H
#define JACOBIMETHODSOLVER_H

#include "lesystemsolver.h"

class JacobiMethodSolver : public LESystemSolver
{
public:
    JacobiMethodSolver() = default;
    ~JacobiMethodSolver() = default;

    Column solve(const Matrix& A,
                 const Column& b,
                 const Column& x = Column(),
                 double epsilon = 0) override;
    bool needApproximation() override;
};

#endif // JACOBIMETHODSOLVER_H
